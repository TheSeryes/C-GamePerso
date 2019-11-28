/// -------------------------------------------------------------------------------------------------------------------
/// BartEngine
/// File: Map.h
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

#ifndef BART_TILED_MAP_H
#define BART_TILED_MAP_H

#include <string>
#include <Color.h>
#include <CTileset.h>
#include <CLayer.h>

using namespace std;

namespace bart
{
    namespace tiled
    {
        enum MapOrientation
        {
            MO_ORTHOGONAL,
            MO_ISOMETRIC,
            MO_STAGGERED,
            MO_HEXAGONAL
        };

        enum MapRenderOrder
        {
            RO_RIGHT_DOWN,
            RO_RIGHT_UP,
            RO_LEFT_DOWN,
            RO_LEFT_UP
        };

        enum MapStaggerAxis
        {
            SA_NONE,
            SA_X,
            SA_Y
        };

        enum MapStaggerIndex
        {
            SI_NONE,
            SI_EVEN,
            SI_ODD
        };

        class Map
        {
        public:
            bool Load(const string& aTmxFile);
            void Clean();
            void Draw(const Rectangle& aViewport);
            Color& GetBackgroundColor() { return m_backgroundColor; }
            Tileset* GetTileset() { return &m_tileSet; }

        private:
            typedef std::map<std::string, Layer*> TLayerMap;
            std::map<std::string, Layer*> m_layers;
            std::vector<Layer*> m_layerDepth;

            MapOrientation ParseOrientation(const char* aValue) const;
            MapRenderOrder ParseRenderOrder(const char* aValue) const;
            MapStaggerAxis ParseStaggerAxis(const char* aValue) const;
            MapStaggerIndex ParseStaggerIndex(const char* aValue) const;
            Color ParseBgColor(const char* aValue) const;

            string m_filename;
            string m_filepath;
            string m_version;
            string m_tiledVersion;
            MapOrientation m_orientation{MO_ORTHOGONAL};
            MapRenderOrder m_renderOrder{RO_RIGHT_DOWN};
            int m_width{0};
            int m_height{0};
            int m_tilewidth{0};
            int m_tileheight{0};
            int m_hexSideLength{0};
            MapStaggerAxis m_staggerAxis{SA_NONE};
            MapStaggerIndex m_staggerIndex{SI_NONE};
            Color m_backgroundColor;
            int m_nextLayerId{0};
            int m_nextObjectId{0};
            Tileset m_tileSet;
        };
    }
}
#endif
