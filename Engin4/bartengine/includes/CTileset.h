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
/// Reference: https://doc.mapeditor.org/en/stable/reference/tmx-map-format/#map
/// -------------------------------------------------------------------------------------------------------------------

#ifndef BART_TILED_TILESET_H
#define BART_TILED_TILESET_H

#include <string>
#include <Rectangle.h>
#include <vector>
#include <map>

using namespace std;

namespace tinyxml2
{
    class XMLNode;
}

using namespace tinyxml2;

namespace bart
{
    namespace tiled
    {
        struct Tile
        {
            size_t Texture;
            Rectangle Bounds;
        };

        class Tileset
        {
        public:
            bool Load(XMLNode* aNodePtr, const std::string& aPath);
            void Clean();
            void GetTileSize(int* aWidth, int* aHeight) const;
            Tile* GetTile(int aIndex);
            int GetTileCount() const { return m_tileCount; }

        private:
            void PrepareTileSources(const string& aFilename);

            typedef map<int, Tile*> TTileMap;
            TTileMap m_tileSource;
            vector<size_t> m_textureIds;

            int m_firstGid{0};
            string m_source;
            string m_name;
            int m_tileWidth{0};
            int m_tileHeight{0};
            int m_spacing{0};
            int m_margin{0};
            int m_tileCount{0};
            int m_columns{0};
        };
    }
}

#endif
