/// -------------------------------------------------------------------------------------------------------------------
/// BartEngine
/// File: Tileset.h
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
/// Reference: https://doc.mapeditor.org/en/stable/reference/tmx-map-format/#tileset
/// -------------------------------------------------------------------------------------------------------------------

#include <CTileset.h>
#include <tinyxml2.h>
#include <Engine.h>

// --------------------------------------------------------------------------------------------------------------------
//   _                     _ 
//  | |                   | |
//  | |     ___   __ _  __| |
//  | |    / _ \ / _` |/ _` |
//  | |___| (_) | (_| | (_| |
//  |______\___/ \__,_|\__,_|
//
// \brief Loads the defaults value of all layers.
// \param aNodePtr: an XMLNode used to load the tileset information.
// \param aPath: path to the assets folder
// \return true if the tiles are loaded successfully.
//
bool bart::tiled::Tileset::Load(XMLNode* aNodePtr, const std::string& aPath)
{
    XMLDocument tDoc;
    XMLElement* tTileElement = nullptr;
    XMLNode* tImageNode = aNodePtr->FirstChild();

    ///
    /// The first global tile ID of this tile-set (this global ID maps to the first tile in this tile-set).
    ///
    m_firstGid = aNodePtr->ToElement()->IntAttribute("firstgid");

    ///
    /// If this tile-set is stored in an external TSX (Tile Set XML) file, this attribute refers to that file.
    /// That TSX file has the same structure as the <tileset> element described here. (There is the firstgid 
    /// attribute missing and this source attribute is also not there. These two attributes are kept in the 
    /// TMX map, since they are map specific.)
    ///
    const char* tSourcePtr = aNodePtr->ToElement()->Attribute("source");

    if (tImageNode != nullptr)
    {
        tTileElement = aNodePtr->ToElement();
    }
    else
    {
        m_source = tSourcePtr;

        const std::string tFileName = aPath + m_source;
        if (tDoc.LoadFile(tFileName.c_str()) == XML_SUCCESS)
        {
            tTileElement = tDoc.FirstChild()->NextSibling()->ToElement();
        }
    }

    if (tTileElement != nullptr)
    {
        ///
        /// The name of this tile-set.
        ///
        const char* tNamePtr = tTileElement->Attribute("name");
        if (tNamePtr != nullptr)
        {
            m_name = tNamePtr;
        }

        ///
        /// The (maximum) width of the tiles in this tile-set.
        ///
        m_tileWidth = tTileElement->IntAttribute("tilewidth");

        ///
        /// The (maximum) height of the tiles in this tile-set.
        ///
        m_tileHeight = tTileElement->IntAttribute("tileheight");

        ///
        /// The spacing in pixels between the tiles in this tile-set (applies to the tile-set image).
        ///
        m_spacing = tTileElement->IntAttribute("spacing");

        ///
        /// The margin around the tiles in this tile-set (applies to the tile-set image).
        ///
        m_margin = tTileElement->IntAttribute("margin");

        ///
        /// The number of tiles in this tile-set (since 0.13)
        ///
        m_tileCount = tTileElement->IntAttribute("tilecount");

        ///
        /// The number of tile columns in the tile-set. For image collection tile-set it is editable and
        /// is used when displaying the tile-set. (since 0.15)
        ///
        m_columns = tTileElement->IntAttribute("columns");

        ///
        /// Can contain: <tileoffset>, <grid> (since 1.0), <properties>, <image>, <terraintypes>, <tile>,
        /// <wangsets> (since 1.1)
        ///
        XMLNode* tNext = tTileElement->FirstChild();
        while (tNext != nullptr)
        {
            std::string tNextValue = tNext->Value();
            if (tNextValue == "image")
            {
                XMLElement* tAtlasElement = tNext->ToElement();

                const char* tFilepath = tAtlasElement->Attribute("source");
                if (tFilepath == nullptr)
                {
                    Engine::Instance().GetLogger().Log("Cannot load tileset image\n");
                    return false;
                }

                PrepareTileSources(aPath + std::string(tFilepath));
            }
            else if (tNextValue == "tileoffset")
            {
                // TODO: support tile offset
            }
            else if (tNextValue == "grid")
            {
                // TODO: support grid
            }
            else if (tNextValue == "properties")
            {
                // TODO: load properties
            }
            else if (tNextValue == "terraintypes")
            {
                // TODO: load terrain types
            }
            else if (tNextValue == "tile")
            {
                // TODO: load tile
            }
            else if (tNextValue == "wangsets")
            {
                // TODO: load wangsets
            }

            tNext = tNext->NextSibling();
        }

        return true;
    }

    Engine::Instance().GetLogger().Log("Couldn't load tileset (%s)\n", m_name.c_str());
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
//  \brief Clean the tile info loaded for the set
//
void bart::tiled::Tileset::Clean()
{
    for (TTileMap::iterator i = m_tileSource.begin(); i != m_tileSource.end(); ++i)
    {
        delete i->second;
    }

    m_tileSource.clear();

    for (size_t i = 0; i < m_textureIds.size(); i++)
    {
        Engine::Instance().GetGraphic().UnloadTexture(m_textureIds[i]);
    }
}

// -------------------------------------------------------------------------------------------------------------------- 
//    _____        _  _______  _  _         _____  _           
//   / ____|      | ||__   __|(_)| |       / ____|(_)          
//  | |  __   ___ | |_  | |    _ | |  ___ | (___   _  ____ ___ 
//  | | |_ | / _ \| __| | |   | || | / _ \ \___ \ | ||_  // _ \
//  | |__| ||  __/| |_  | |   | || ||  __/ ____) || | / /|  __/
//   \_____| \___| \__| |_|   |_||_| \___||_____/ |_|/___|\___|
//
//  \brief Gets the size of the tiles in the tileset
//  \param aWidth the tile's width
//  \param aHeight the tile's height
//  NOTE: The size is not necessarily the same as the tile size on the map.
//
void bart::tiled::Tileset::GetTileSize(int* aWidth, int* aHeight) const
{
    *aWidth = m_tileWidth;
    *aHeight = m_tileHeight;
}

// -------------------------------------------------------------------------------------------------------------------- 
//    _____        _  _______  _  _       
//   / ____|      | ||__   __|(_)| |      
//  | |  __   ___ | |_  | |    _ | |  ___ 
//  | | |_ | / _ \| __| | |   | || | / _ \
//  | |__| ||  __/| |_  | |   | || ||  __/
//   \_____| \___| \__| |_|   |_||_| \___|
//
//  \brief Gets a tile information at the given index
//  \param aIndex the tile's index
//  \return a tile's struct with the information needed to draw it inside
//  NOTE: will return a nullptr if the index was not found
//
bart::tiled::Tile* bart::tiled::Tileset::GetTile(const int aIndex)
{
    if (m_tileSource.count(aIndex) > 0)
    {
        return m_tileSource[aIndex];
    }

    return nullptr;
}

// -------------------------------------------------------------------------------------------------------------------- 
//   _____                                   _______  _  _         _____                                    
//  |  __ \                                 |__   __|(_)| |       / ____|                                   
//  | |__) |_ __  ___  _ __    __ _  _ __  ___ | |    _ | |  ___ | (___    ___   _   _  _ __  ___  ___  ___ 
//  |  ___/| '__|/ _ \| '_ \  / _` || '__|/ _ \| |   | || | / _ \ \___ \  / _ \ | | | || '__|/ __|/ _ \/ __|
//  | |    | |  |  __/| |_) || (_| || |  |  __/| |   | || ||  __/ ____) || (_) || |_| || |  | (__|  __/\__ \
//  |_|    |_|   \___|| .__/  \__,_||_|   \___||_|   |_||_| \___||_____/  \___/  \__,_||_|   \___|\___||___/
//                    | |                                                                                   
//                    |_|                                                                                   
//  
//  \brief Prepares the source rectangle for the rendering of the tiles
//  \param aFilename the texture with the tiles in it
//  BUG: this doesn't support the tileset with multiple images
void bart::tiled::Tileset::PrepareTileSources(const string& aFilename)
{
    const size_t tTextureId = Engine::Instance().GetGraphic().LoadTexture(aFilename);

    if (tTextureId > 0)
    {
        m_textureIds.push_back(tTextureId);

        int tTileNumber = m_firstGid;
        int tY = 0;
        int tX = 0;

        for (int i = 0; i < m_tileCount; i++, tTileNumber++)
        {
            tY = i / m_columns;
            tX = i - tY * m_columns;

            m_tileSource[tTileNumber] = new Tile();
            m_tileSource[tTileNumber]->Texture = tTextureId;
            m_tileSource[tTileNumber]->Bounds = {tX * m_tileWidth, tY * m_tileHeight, m_tileWidth, m_tileHeight};
        }
    }
}
