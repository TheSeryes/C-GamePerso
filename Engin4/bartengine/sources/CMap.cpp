/// -------------------------------------------------------------------------------------------------------------------
/// BartEngine
/// File: Map.cpp
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
/// Reference: https://doc.mapeditor.org/en/stable/reference/tmx-map-format/#map
/// -------------------------------------------------------------------------------------------------------------------

#include <CMap.h>
#include <Engine.h>
#include <tinyxml2.h>
#include <StringHelper.h>

using namespace tinyxml2;

// --------------------------------------------------------------------------------------------------------------------
//   _                        _ 
//  | |                      | |
//  | |      ___    __ _   __| |
//  | |     / _ \  / _` | / _` |
//  | |____| (_) || (_| || (_| |
//  |______|\___/  \__,_| \__,_|
//                              
//                              
//  
bool bart::tiled::Map::Load(const string& aTmxFile)
{
    XMLDocument tDocument;
    if (tDocument.LoadFile(aTmxFile.c_str()) == XML_SUCCESS)
    {
        m_filename = aTmxFile;
        m_filepath = StringHelper::GetPath(aTmxFile);

        XMLNode* tNode = tDocument.FirstChild();
        while (tNode != nullptr)
        {
            std::string tNodeValue = tNode->Value();
            if (tNodeValue == "map")
            {
                XMLElement* tMapElement = tNode->ToElement();

                //
                // The TMX format version. Was "1.0" so far, and will be incremented to match minor Tiled releases.
                //
                const char* tVersionPtr = tMapElement->Attribute("version");
                if (tVersionPtr != nullptr)
                {
                    m_version = tVersionPtr;

                    if(m_version != "1.2")
                    {
                        Engine::Instance().GetLogger().Log("ERROR: Unsupported Tiled version");
                    }
                }

                //
                // The Tiled version used to save the file (since Tiled 1.0.1). May be a date (for snapshot builds).
                const char* tTiledVersionPtr = tMapElement->Attribute("tiledversion");
                if (tTiledVersionPtr != nullptr)
                {
                    m_tiledVersion = tTiledVersionPtr;
                }

                //
                // Map orientation. Tiled supports “orthogonal”, “isometric”, “staggered” and “hexagonal” (since 0.11).
                // The staggered orientation refers to an isometric map using staggered axes.
                //
                const char* tOrientationPtr = tMapElement->Attribute("orientation");
                m_orientation = ParseOrientation(tOrientationPtr);

                //
                // The order in which tiles on tile layers are rendered. Valid values are right-down (the default), right-up,
                // left-down and left-up. In all cases, the map is drawn row-by-row. (only supported for orthogonal maps at
                // the moment)
                //
                const char* tRenderOrderPtr = tMapElement->Attribute("renderorder");
                m_renderOrder = ParseRenderOrder(tRenderOrderPtr);

                //
                // The map width in tiles.
                //
                m_width = tMapElement->IntAttribute("width", 0);

                //
                // The map height in tiles.
                //
                m_height = tMapElement->IntAttribute("height", 0);

                //
                // The width of a tile. The tilewidth properties determine the general grid size of the map. The individual tiles
                // may have different sizes. Larger tiles will extend at the top and right (anchored to the bottom left).
                //
                m_tilewidth = tMapElement->IntAttribute("tilewidth", 0);

                //
                // The height of a tile. The tileheight properties determine the general grid size of the map. The individual tiles
                // may have different sizes. Larger tiles will extend at the top and right (anchored to the bottom left).
                //
                m_tileheight = tMapElement->IntAttribute("tileheight", 0);

                //
                // Only for hexagonal maps. Determines the width or height (depending on the staggered axis) of the tile’s edge,
                // in pixels.
                //
                m_hexSideLength = tMapElement->IntAttribute("hexsidelength", 0);

                //
                // For staggered and hexagonal maps, determines which axis (“x” or “y”) is staggered. (since 0.11)
                //
                const char* tStaggerAxisPtr = tMapElement->Attribute("staggeraxis");
                m_staggerAxis = ParseStaggerAxis(tStaggerAxisPtr);

                //
                // For staggered and hexagonal maps, determines whether the “even” or “odd” indexes along the staggered axis are
                // shifted. (since 0.11)
                //
                const char* tStaggerIndexPtr = tMapElement->Attribute("staggerindex");
                m_staggerIndex = ParseStaggerIndex(tStaggerIndexPtr);

                //
                // The background color of the map. (optional, may include alpha value since 0.15 in the form #AARRGGBB)
                //
                const char* tBackgroundColor = tMapElement->Attribute("backgroundcolor");
                m_backgroundColor = ParseBgColor(tBackgroundColor);

                //
                // Stores the next available ID for new layers. This number is stored to prevent reuse of the same ID after layers
                // have been removed. (since 1.2)
                //
                m_nextLayerId = tMapElement->IntAttribute("nextlayerid");

                //
                // Stores the next available ID for new objects. This number is stored to prevent reuse of the same ID after objects
                // have been removed. (since 0.11)
                //
                m_nextObjectId = tMapElement->IntAttribute("nextobjectid");

                //
                // Can contain: <properties>, <tileset>, <layer>, <objectgroup>, <imagelayer>, <group> (since 1.0)
                //
                XMLNode* tMapChild = tNode->FirstChild();
                while (tMapChild != nullptr)
                {
                    std::string tChildValue = tMapChild->Value();
                    if (tChildValue == "properties")
                    {
                        // TODO: load map properties
                    }
                    else if (tChildValue == "tileset")
                    {
                        m_tileSet.Load(tMapChild, m_filepath);
                    }
                    else if (tChildValue == "layer")
                    {
                        TileLayer* tTileLayer = new TileLayer(&m_tileSet);
                        if(tTileLayer && tTileLayer->Load(tMapChild))
                        {
                            string tName = tTileLayer->GetName();
                            if(m_layers.count(tName) == 0)
                            {
                                m_layers[tName] = tTileLayer;
                                m_layerDepth.push_back(tTileLayer);
                            }
                        }
                    }
                    else if (tChildValue == "objectgroup")
                    {
                        // TODO: set factory to object layer
                        ObjectLayer* tObjectLayer = new ObjectLayer();
                        if (tObjectLayer && tObjectLayer->Load(tMapChild))
                        {
                            string tName = tObjectLayer->GetName();
                            if (m_layers.count(tName) == 0)
                            {
                                m_layers[tName] = tObjectLayer;
                                m_layerDepth.push_back(tObjectLayer);
                            }
                        }
                    }
                    else if (tChildValue == "imagelayer")
                    {
                        ImageLayer* tImageLayer = new ImageLayer(m_filepath);
                        if (tImageLayer && tImageLayer->Load(tMapChild))
                        {
                            string tName = tImageLayer->GetName();
                            if (m_layers.count(tName) == 0)
                            {
                                m_layers[tName] = tImageLayer;
                                m_layerDepth.push_back(tImageLayer);
                            }
                        }
                    }
                    else if (tChildValue == "group")
                    {
                        // TODO: load groups (what are groups?)
                    }
                    else
                    {
                        Engine::Instance().GetLogger().Log("Warning: (%s) is not supported\n", tChildValue.c_str());
                    }

                    tMapChild = tMapChild->NextSibling();
                }
            }

            tNode = tNode->NextSibling();
        }

        return true;
    }

    Engine::Instance().GetLogger().Log("%s\n", tDocument.ErrorStr());
    return false;
}

// --------------------------------------------------------------------------------------------------------------------
//    _____  _                     
//   / ____|| |                    
//  | |     | |  ___   __ _  _ __  
//  | |     | | / _ \ / _` || '_ \ 
//  | |____ | ||  __/| (_| || | | |
//   \_____||_| \___| \__,_||_| |_|
//                                 
//                                 
//  
void bart::tiled::Map::Clean()
{
    for (TLayerMap::iterator tItr = m_layers.begin(); tItr != m_layers.end(); ++tItr)
    {
        if (tItr->second != nullptr)
        {
            tItr->second->Clean();
            delete tItr->second;
        }
    }

    m_layers.clear();

    m_tileSet.Clean();
}

// --------------------------------------------------------------------------------------------------------------------
//   _____                        
//  |  __ \                       
//  | |  | | _ __  __ _ __      __
//  | |  | || '__|/ _` |\ \ /\ / /
//  | |__| || |  | (_| | \ V  V / 
//  |_____/ |_|   \__,_|  \_/\_/  
//                                
//                                
//  
void bart::tiled::Map::Draw(const Rectangle& aViewport)
{
    for (size_t i = 0; i < m_layerDepth.size(); i++)
    {
        m_layerDepth[i]->Draw(aViewport);
    }
}

// --------------------------------------------------------------------------------------------------------------------
//   _____                          ____         _               _          _    _               
//  |  __ \                        / __ \       (_)             | |        | |  (_)              
//  | |__) |__ _  _ __  ___   ___ | |  | | _ __  _   ___  _ __  | |_  __ _ | |_  _   ___   _ __  
//  |  ___// _` || '__|/ __| / _ \| |  | || '__|| | / _ \| '_ \ | __|/ _` || __|| | / _ \ | '_ \ 
//  | |   | (_| || |   \__ \|  __/| |__| || |   | ||  __/| | | || |_| (_| || |_ | || (_) || | | |
//  |_|    \__,_||_|   |___/ \___| \____/ |_|   |_| \___||_| |_| \__|\__,_| \__||_| \___/ |_| |_|
//                                                                                               
//                                                                                               
//  
bart::tiled::MapOrientation bart::tiled::Map::ParseOrientation(const char* aValue) const
{
    if (aValue)
    {
        if (strcmp(aValue, "orthogonal") == 0)
        {
            return MO_ORTHOGONAL;
        }
        if (strcmp(aValue, "isometric") == 0)
        {
            return MO_ISOMETRIC;
        }
        if (strcmp(aValue, "staggered") == 0)
        {
            return MO_STAGGERED;
        }
        if (strcmp(aValue, "hexagonal") == 0)
        {
            return MO_HEXAGONAL;
        }
    }

    return MO_ORTHOGONAL;
}

// --------------------------------------------------------------------------------------------------------------------
//   _____                         _____                   _               ____            _             
//  |  __ \                       |  __ \                 | |             / __ \          | |            
//  | |__) |__ _  _ __  ___   ___ | |__) | ___  _ __    __| |  ___  _ __ | |  | | _ __  __| |  ___  _ __ 
//  |  ___// _` || '__|/ __| / _ \|  _  / / _ \| '_ \  / _` | / _ \| '__|| |  | || '__|/ _` | / _ \| '__|
//  | |   | (_| || |   \__ \|  __/| | \ \|  __/| | | || (_| ||  __/| |   | |__| || |  | (_| ||  __/| |   
//  |_|    \__,_||_|   |___/ \___||_|  \_\\___||_| |_| \__,_| \___||_|    \____/ |_|   \__,_| \___||_|   
//                                                                                                       
//                                                                                                       
//  
bart::tiled::MapRenderOrder bart::tiled::Map::ParseRenderOrder(const char* aValue) const
{
    if (aValue)
    {
        if (strcmp(aValue, "right-down") == 0)
        {
            return RO_RIGHT_DOWN;
        }

        if (strcmp(aValue, "right-up") == 0)
        {
            return RO_RIGHT_UP;
        }

        if (strcmp(aValue, "left-down") == 0)
        {
            return RO_LEFT_DOWN;
        }

        if (strcmp(aValue, "left-up") == 0)
        {
            return RO_LEFT_UP;
        }
    }

    return RO_RIGHT_DOWN;
}

// --------------------------------------------------------------------------------------------------------------------
//   _____                          _____  _                                                  _      
//  |  __ \                        / ____|| |                                    /\          (_)     
//  | |__) |__ _  _ __  ___   ___ | (___  | |_  __ _   __ _   __ _   ___  _ __  /  \   __  __ _  ___ 
//  |  ___// _` || '__|/ __| / _ \ \___ \ | __|/ _` | / _` | / _` | / _ \| '__|/ /\ \  \ \/ /| |/ __|
//  | |   | (_| || |   \__ \|  __/ ____) || |_| (_| || (_| || (_| ||  __/| |  / ____ \  >  < | |\__ \
//  |_|    \__,_||_|   |___/ \___||_____/  \__|\__,_| \__, | \__, | \___||_| /_/    \_\/_/\_\|_||___/
//                                                     __/ |  __/ |                                  
//                                                    |___/  |___/                                   
//
bart::tiled::MapStaggerAxis bart::tiled::Map::ParseStaggerAxis(const char* aValue) const
{
    if (aValue)
    {
        if (strcmp(aValue, "x") == 0)
        {
            return SA_X;
        }
        if (strcmp(aValue, "y") == 0)
        {
            return SA_X;
        }
        return SA_NONE;
    }

    return SA_NONE;
}

// --------------------------------------------------------------------------------------------------------------------
//   _____                          _____  _                                  _____             _             
//  |  __ \                        / ____|| |                                |_   _|           | |            
//  | |__) |__ _  _ __  ___   ___ | (___  | |_  __ _   __ _   __ _   ___  _ __ | |   _ __    __| |  ___ __  __
//  |  ___// _` || '__|/ __| / _ \ \___ \ | __|/ _` | / _` | / _` | / _ \| '__|| |  | '_ \  / _` | / _ \\ \/ /
//  | |   | (_| || |   \__ \|  __/ ____) || |_| (_| || (_| || (_| ||  __/| |  _| |_ | | | || (_| ||  __/ >  < 
//  |_|    \__,_||_|   |___/ \___||_____/  \__|\__,_| \__, | \__, | \___||_| |_____||_| |_| \__,_| \___|/_/\_\
//                                                     __/ |  __/ |                                           
//                                                    |___/  |___/                                            
//  
bart::tiled::MapStaggerIndex bart::tiled::Map::ParseStaggerIndex(const char* aValue) const
{
    if (aValue)
    {
        if (strcmp(aValue, "even") == 0)
        {
            return SI_EVEN;
        }
        if (strcmp(aValue, "odd") == 0)
        {
            return SI_ODD;
        }
        return SI_NONE;
    }

    return SI_NONE;
}

// --------------------------------------------------------------------------------------------------------------------
//   _____                         ____           _____        _              
//  |  __ \                       |  _ \         / ____|      | |             
//  | |__) |__ _  _ __  ___   ___ | |_) |  __ _ | |      ___  | |  ___   _ __ 
//  |  ___// _` || '__|/ __| / _ \|  _ <  / _` || |     / _ \ | | / _ \ | '__|
//  | |   | (_| || |   \__ \|  __/| |_) || (_| || |____| (_) || || (_) || |   
//  |_|    \__,_||_|   |___/ \___||____/  \__, | \_____|\___/ |_| \___/ |_|   
//                                         __/ |                              
//                                        |___/                               
//  
bart::Color bart::tiled::Map::ParseBgColor(const char* aValue) const
{
    if (aValue != nullptr)
    {
        unsigned char tR, tG, tB, tA;
        StringHelper::GetColorComponents(aValue, &tR, &tG, &tB, &tA);
        return {tR, tG, tB, tA};
    }

    return {137, 137, 137, 255};
}
