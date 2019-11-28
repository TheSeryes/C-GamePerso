/// --------------------------------------------------------------------------------------------------------------------
/// BartEngine
/// File: Layer.cpp
///
/// Copyright (c) 2019-2020, David St-Cyr
/// All rights reserved.
///
/// This software is provided 'as-is', without any express or implied warranty. In no event will the authors be held
/// liable for any damages arising from the use of this software.
///
/// Permission is granted to anyone to use this software for any purpose, including commercial applications, and to
/// alter it and redistribute it freely, subject to the following restrictions:
///
/// 1. The origin of this software must not be misrepresented; you must not claim that you wrote the original software.
///    If you use this software in a product, an acknowledgment in the product documentation would be appreciated but
///    is not required.
///
/// 2. Altered source versions must be plainly marked as such, and must not be misrepresented as being the original
///    software.
///
/// 3. This notice may not be removed or altered from any source distribution.
///
/// Author: David St-Cyr
/// david.stcyr@bart.ca
/// 
/// Reference: https://doc.mapeditor.org/en/stable/reference/tmx-map-format/#layer
/// --------------------------------------------------------------------------------------------------------------------

#include <CLayer.h>
#include <tinyxml2.h>
#include <StringHelper.h>
#include <Engine.h>
#include <MathHelper.h>

/// Bits on the far end of the 32-bit global tile ID are used for tile flags
const unsigned FLIPPED_HORIZONTALLY_FLAG = 0x80000000;
const unsigned FLIPPED_VERTICALLY_FLAG = 0x40000000;
const unsigned FLIPPED_DIAGONALLY_FLAG = 0x20000000;

// --------------------------------------------------------------------------------------------------------------------
//   _                     _ 
//  | |                   | |
//  | |     ___   __ _  __| |
//  | |    / _ \ / _` |/ _` |
//  | |___| (_) | (_| | (_| |
//  |______\___/ \__,_|\__,_|
//
// \brief Loads the defaults value of all layers.
// \param aNodePtr: an XMLNode used to load the layer information.
// \return true if the layer is loaded successfully.
//
bool bart::tiled::Layer::Load(XMLNode* aNodePtr)
{
    XMLElement* tLayerElement = aNodePtr->ToElement();

    ///
    /// Unique ID of the layer. Each layer that added to a map gets a unique id. Even if a layer is deleted, no layer
    /// ever gets the same ID. Can not be changed in Tiled. (since Tiled 1.2)
    /// 
    m_id = tLayerElement->IntAttribute("id");

    ///
    /// The name of the layer.
    ///
    const char* tNamePtr = tLayerElement->Attribute("name");
    if (tNamePtr != nullptr)
    {
        m_name = tNamePtr;
    }

    ///
    /// The x coordinate of the layer in tiles. Defaults to 0 and can not be changed in Tiled.
    ///
    m_x = tLayerElement->IntAttribute("x");

    ///
    /// The y coordinate of the layer in tiles. Defaults to 0 and can not be changed in Tiled.
    ///
    m_y = tLayerElement->IntAttribute("y");

    ///
    /// Whether the layer is shown (true) or hidden (false). Defaults to true.
    ///
    m_visible = tLayerElement->BoolAttribute("visible", true);

    ///
    /// The opacity of the layer as a value from 0 to 1. Defaults to 1.
    ///
    const float tOpacity = tLayerElement->FloatAttribute("opacity", 1.0f);
    m_opacity = static_cast<unsigned char>(255.0f * tOpacity);

    ///
    /// Rendering offset for this layer in pixels. Defaults to 0. (since 0.14)
    ///
    m_offsetx = tLayerElement->FloatAttribute("offsetx", 0.0f);

    ///
    /// Rendering offset for this layer in pixels. Defaults to 0. (since 0.14)
    ///
    m_offsety = tLayerElement->FloatAttribute("offsety", 0.0f);

    return true;
}

// --------------------------------------------------------------------------------------------------------------------
//   _____                      _______  _  _        _____          _         
//  |  __ \                    |__   __|(_)| |      |  __ \        | |        
//  | |__) |__ _  _ __  ___   ___ | |    _ | |  ___ | |  | |  __ _ | |_  __ _ 
//  |  ___// _` || '__|/ __| / _ \| |   | || | / _ \| |  | | / _` || __|/ _` |
//  | |   | (_| || |   \__ \|  __/| |   | || ||  __/| |__| || (_| || |_| (_| |
//  |_|    \__,_||_|   |___/ \___||_|   |_||_| \___||_____/  \__,_| \__|\__,_|
//                                                                            
//  \brief This methods parses the list of tile number to prepare the rendering.
//  \param aData a list with the tiles number
//  
void bart::tiled::TileLayer::ParseTileData(const char* aData)
{
    std::string tCurrentToken;
    std::istringstream tInput(aData);

    int tX = 0;
    int tY = 0;

    mLayerData.push_back(std::vector<TileInfo*>(m_width));

    while (std::getline(tInput, tCurrentToken, ','))
    {
        if (!tCurrentToken.empty())
        {
            TileInfo* tInfo = new TileInfo();

            try
            {
                tInfo->Index = std::stoul(tCurrentToken);
                tInfo->HorizontalFlip = tInfo->Index & FLIPPED_HORIZONTALLY_FLAG;
                tInfo->VerticalFlip = tInfo->Index & FLIPPED_VERTICALLY_FLAG;
                tInfo->DiagonalFlip = tInfo->Index & FLIPPED_DIAGONALLY_FLAG;
                tInfo->Index &= ~(FLIPPED_HORIZONTALLY_FLAG | FLIPPED_VERTICALLY_FLAG | FLIPPED_DIAGONALLY_FLAG);
            }
            catch (const std::exception& exp)
            {
                Engine::Instance().GetLogger().Log("Corrupted map detected (layer: %s)\n", m_name.c_str());
                Engine::Instance().GetLogger().Log("Error: %s\n", exp.what());
            }

            mLayerData[tY][tX] = tInfo;
            tX++;

            if (tX >= m_width && tY < m_height - 1)
            {
                tX = 0;
                tY++;

                mLayerData.push_back(std::vector<TileInfo*>(m_width));
            }
        }
        else
        {
            Engine::Instance().GetLogger().Log("Invalid map detected (layer: %s)\n", m_name.c_str());
        }
    }
}

// --------------------------------------------------------------------------------------------------------------------
//   _                     _ 
//  | |                   | |
//  | |     ___   __ _  __| |
//  | |    / _ \ / _` |/ _` |
//  | |___| (_) | (_| | (_| |
//  |______\___/ \__,_|\__,_|
//
// \brief Loads a layer of tiles
// \param aNodePtr: an XMLNode used to load the layer information.
// \return true if the layer is loaded successfully.
//
bool bart::tiled::TileLayer::Load(XMLNode* aNode)
{
    if (Layer::Load(aNode))
    {
        XMLElement* tLayerElement = aNode->ToElement();

        ///
        /// The width of the layer in tiles. Always the same as the map width for fixed-size maps.
        ///
        m_width = tLayerElement->IntAttribute("width");

        ///
        /// The height of the layer in tiles. Always the same as the map height for fixed-size maps.
        ///
        m_height = tLayerElement->IntAttribute("height");

        ///
        /// Can contain: <properties>, <data>
        ///
        XMLNode* tNext = aNode->FirstChild();
        while (tNext != nullptr)
        {
            std::string tNextValue = tNext->Value();
            if (tNextValue == "data")
            {
                XMLElement* tDataElement = tNext->ToElement();
                const char* tEncoding = tDataElement->Attribute("encoding");

                if (tEncoding == nullptr || strcmp(tEncoding, "csv") != 0)
                {
                    Engine::Instance().GetLogger().Log("Only CSV encoding is supported\n");
                    return false;
                }

                const char* tData = tDataElement->GetText();
                ParseTileData(tData);
            }
            else if (tNextValue == "properties")
            {
                //TODO: Load properties
            }

            tNext = tNext->NextSibling();
        }

        return true;
    }

    return false;
}

// --------------------------------------------------------------------------------------------------------------------
//    _____ _                  
//   / ____| |                 
//  | |    | | ___  __ _ _ __  
//  | |    | |/ _ \/ _` | '_ \ 
//  | |____| |  __/ (_| | | | |
//   \_____|_|\___|\__,_|_| |_|
//                             
//  \brief Clears the data created for the tiles on this layer
//
void bart::tiled::TileLayer::Clean()
{
    for (TTileMap::iterator itr = mLayerData.begin(); itr != mLayerData.end(); ++itr)
    {
        for (TileInfo* tInfo : *itr)
        {
            delete tInfo;
        }
    }

    mLayerData.clear();
}

// --------------------------------------------------------------------------------------------------------------------
//   _____
//  |  __ \
//  | |  | |_ __ __ ___      __
//  | |  | | '__/ _` \ \ /\ / /
//  | |__| | | | (_| |\ V  V /
//  |_____/|_|  \__,_| \_/\_/
//
//  \brief Draws the tile with the tileset values.
//  \param aViewport the portion of the screen that can see this image layer
//
void bart::tiled::TileLayer::Draw(const Rectangle& aViewport)
{
    if (m_visible)
    {
        int tTileWidth, tTileHeight;
        m_tilesetPtr->GetTileSize(&tTileWidth, &tTileHeight);

        const int tFromX = MathHelper::Clamp(aViewport.X / tTileWidth, 0, m_width);
        const int tFromY = MathHelper::Clamp(aViewport.Y / tTileHeight, 0, m_height);
        const int tToX = MathHelper::Clamp((aViewport.X + aViewport.W) / tTileWidth, tFromX, m_width);
        const int tToY = MathHelper::Clamp((aViewport.Y + aViewport.H) / tTileHeight, tFromY, m_height);

        if (tFromX < tToX && tFromY < tToY)
        {
            IGraphic& tGraphic = Engine::Instance().GetGraphic();

            Rectangle tDest;

            const size_t tDataSize = mLayerData.size();
            if (tDataSize > 0)
            {
                for (int y = tFromY; y < tToY; y++)
                {
                    const int tY = y * tTileHeight;
                    for (int x = tFromX; x < tToX; x++)
                    {
                        tDest.X = x * tTileWidth + static_cast<int>(m_offsetx);
                        tDest.Y = tY + static_cast<int>(m_offsety);

                        const int tIndex = mLayerData[y][x]->Index;
                        bool tInvalidTile = false;

                        if (tIndex > 0)
                        {
                            Tile* tTile = m_tilesetPtr->GetTile(tIndex);

                            if (tTile != nullptr)
                            {
                                tDest.W = tTile->Bounds.W;
                                tDest.H = tTile->Bounds.H;

                                if (mLayerData[y][x]->DiagonalFlip)
                                {
                                    if (mLayerData[y][x]->HorizontalFlip && mLayerData[y][x]->VerticalFlip)
                                    {
                                        tGraphic.Draw(tTile->Texture, tTile->Bounds, tDest, -90.0f, false, true, m_opacity);
                                    }
                                    else if (mLayerData[y][x]->VerticalFlip)
                                    {
                                        tGraphic.Draw(tTile->Texture, tTile->Bounds, tDest, -90.0f, false, false, m_opacity);
                                    }
                                    else if (mLayerData[y][x]->HorizontalFlip)
                                    {
                                        tGraphic.Draw(tTile->Texture, tTile->Bounds, tDest, 90.0f, false, false, m_opacity);
                                    }
                                    else
                                    {
                                        tGraphic.Draw(tTile->Texture, tTile->Bounds, tDest, -90.0f, true, false, m_opacity);
                                    }
                                }
                                else
                                {
                                    tGraphic.Draw(tTile->Texture, tTile->Bounds, tDest, 0.0f, mLayerData[y][x]->HorizontalFlip, mLayerData[y][x]->VerticalFlip, m_opacity);
                                }
                            }
                            else
                            {
                                tInvalidTile = true;
                            }
                        }
                        else if (tIndex < 0)
                        {
                            tInvalidTile = true;
                        }

                        if (tInvalidTile)
                        {
                            /// Unsupported map is a red rectangle in game:
                            tGraphic.SetColor(255, 0, 0, 255);
                            tGraphic.Fill(tDest);
                        }
                    }
                }
            }
        }
    }
}

// --------------------------------------------------------------------------------------------------------------------
//   _                     _ 
//  | |                   | |
//  | |     ___   __ _  __| |
//  | |    / _ \ / _` |/ _` |
//  | |___| (_) | (_| | (_| |
//  |______\___/ \__,_|\__,_|
//
// \brief Loads a layer of custom objects
// \param aNodePtr: an XMLNode used to load the layer information.
// \return true if the layer is loaded successfully.
//
bool bart::tiled::ObjectLayer::Load(XMLNode* aNode)
{
    if (Layer::Load(aNode))
    {
        XMLElement* tLayerElement = aNode->ToElement();

        ///
        /// The width of the layer in tiles. Always the same as the map width for fixed-size maps.
        ///
        m_width = tLayerElement->IntAttribute("width");

        ///
        /// The height of the layer in tiles. Always the same as the map height for fixed-size maps.
        ///
        m_height = tLayerElement->IntAttribute("height");

        ///
        /// Whether the objects are drawn according to the order of appearance ("index") or sorted by
        /// their y-coordinate ("topdown"). Defaults to "topdown".
        ///
        const char* tDrawOrderPtr = tLayerElement->Attribute("draworder");
        m_drawOrder = ParseDrawOrder(tDrawOrderPtr);

        ///
        /// The color used to display the objects in this group.
        ///
        const char* tColorPtr = tLayerElement->Attribute("color");
        m_color = ParseColor(tColorPtr);

        ///
        /// Can contain: <properties>, <object>
        ///

        return true;
    }

    return false;
}

// --------------------------------------------------------------------------------------------------------------------
//    _____ _                  
//   / ____| |                 
//  | |    | | ___  __ _ _ __  
//  | |    | |/ _ \/ _` | '_ \ 
//  | |____| |  __/ (_| | | | |
//   \_____|_|\___|\__,_|_| |_|
//                             
//  \brief Clears the object created for that layer.
//  (Note: not the entities, which are managed by the Engine)
//
void bart::tiled::ObjectLayer::Clean()
{
    /// NOTE that for now, all the objects are managed by the Engine and we don't need to clean the entities here.
}

// --------------------------------------------------------------------------------------------------------------------
//   _____
//  |  __ \
//  | |  | |_ __ __ ___      __
//  | |  | | '__/ _` \ \ /\ / /
//  | |__| | | | (_| |\ V  V /
//  |_____/|_|  \__,_| \_/\_/
//
//  \brief Draws the objects on the layer
//  \param aViewport the portion of the screen that can see this image layer
//
void bart::tiled::ObjectLayer::Draw(const Rectangle& /*aViewport*/)
{
    /// NOTE: the objects are entities and the engine draws them automatically
}

// -------------------------------------------------------------------------------------------------------------------
//   _____                         _____                          ____            _             
//  |  __ \                       |  __ \                        / __ \          | |            
//  | |__) |__ _  _ __  ___   ___ | |  | | _ __  __ _ __      __| |  | | _ __  __| |  ___  _ __ 
//  |  ___// _` || '__|/ __| / _ \| |  | || '__|/ _` |\ \ /\ / /| |  | || '__|/ _` | / _ \| '__|
//  | |   | (_| || |   \__ \|  __/| |__| || |  | (_| | \ V  V / | |__| || |  | (_| ||  __/| |   
//  |_|    \__,_||_|   |___/ \___||_____/ |_|   \__,_|  \_/\_/   \____/ |_|   \__,_| \___||_|
//
//  \brief Parse the draw order setting
//  \param aValue the draw order value from the xml file
//  \return the draw order of a default value (TOPDOWN) if it wasn't present
//
bart::tiled::LayerDrawOrder bart::tiled::ObjectLayer::ParseDrawOrder(const char* aValue) const
{
    if (aValue)
    {
        if (strcmp(aValue, "orthogonal") == 0)
        {
            return DO_INDEX;
        }
        if (strcmp(aValue, "isometric") == 0)
        {
            return DO_TOPDOWN;
        }
    }

    return DO_TOPDOWN;
}

// -------------------------------------------------------------------------------------------------------------------
//   _____                          _____        _              
//  |  __ \                        / ____|      | |             
//  | |__) |__ _  _ __  ___   ___ | |      ___  | |  ___   _ __ 
//  |  ___// _` || '__|/ __| / _ \| |     / _ \ | | / _ \ | '__|
//  | |   | (_| || |   \__ \|  __/| |____| (_) || || (_) || |   
//  |_|    \__,_||_|   |___/ \___| \_____|\___/ |_| \___/ |_|
//
//  \brief Parses a color values from the map that the user can use to clear the screen if wanted.
//  \param aValue a color value as a string from the xml file
//  \return a Color
//
bart::Color bart::tiled::ObjectLayer::ParseColor(const char* aValue) const
{
    if (aValue != nullptr)
    {
        unsigned char tR, tG, tB, tA;
        StringHelper::GetColorComponents(aValue, &tR, &tG, &tB, &tA);
        return {tR, tG, tB, tA};
    }

    /// Approximately the background color in Tiled if none is set
    return {137, 137, 137, 255};
}

// -------------------------------------------------------------------------------------------------------------------
//  _                    _ 
// | |    ___   __ _  __| |
// | |   / _ \ / _` |/ _` |
// | |__| (_) | (_| | (_| |
// |_____\___/ \__,_|\__,_|
//
// \brief Loads a layer that consists of a single image.
// \param aNodePtr: an XMLNode used to load the image layer information.
// \return true if the layer is loaded successfully.
//
bool bart::tiled::ImageLayer::Load(XMLNode* aNodePtr)
{
    if (aNodePtr && Layer::Load(aNodePtr))
    {
        ///
        /// Can contain: <properties>, <image>
        ///
        XMLNode* tNext = aNodePtr->FirstChild();
        while (tNext != nullptr)
        {
            std::string tNextValue = tNext->Value();
            if (tNextValue == "image")
            {
                XMLElement* tSourceElement = tNext->ToElement();
                if (tSourceElement != nullptr)
                {
                    const char* tSource = tSourceElement->Attribute("source");
                    if (tSource != nullptr)
                    {
                        const std::string tFilename = m_path + std::string(tSource);
                        const int tWidth = tSourceElement->IntAttribute("width");
                        const int tHeight = tSourceElement->IntAttribute("height");

                        m_source.Set(0, 0, tWidth, tHeight);
                        m_destination.Set(static_cast<int>(m_offsetx), static_cast<int>(m_offsety), tWidth, tHeight);
                        m_textureId = Engine::Instance().GetGraphic().LoadTexture(tFilename);
                    }
                }
            }
            else if (tNextValue == "properties")
            {
                // TODO: Load image layer properties
            }

            tNext = tNext->NextSibling();
        }

        return true;
    }

    return false;
}

// --------------------------------------------------------------------------------------------------------------------
//    _____ _                  
//   / ____| |                 
//  | |    | | ___  __ _ _ __  
//  | |    | |/ _ \/ _` | '_ \ 
//  | |____| |  __/ (_| | | | |
//   \_____|_|\___|\__,_|_| |_|
//                             
//  \brief Clears the image layer resources.
//
void bart::tiled::ImageLayer::Clean()
{
    Engine::Instance().GetGraphic().UnloadTexture(m_textureId);
}

// -------------------------------------------------------------------------------------------------------------------
//   _____
//  |  __ \
//  | |  | |_ __ __ ___      __
//  | |  | | '__/ _` \ \ /\ / /
//  | |__| | | | (_| |\ V  V /
//  |_____/|_|  \__,_| \_/\_/
//
//  \brief Draw the image on the layer
//  \param aViewport the portion of the screen that can see this image layer
//
void bart::tiled::ImageLayer::Draw(const Rectangle& aViewport)
{
    if (m_visible && m_textureId > 0)
    {
        if (Engine::Instance().GetCollision().IsColliding(aViewport, m_destination))
        {
            Engine::Instance().GetGraphic().Draw(m_textureId, m_source, m_destination, 0.0f, false, false, m_opacity);
        }
    }
}
