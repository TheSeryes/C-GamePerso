/// -------------------------------------------------------------------------------------------------------------------
/// BartEngine
/// File: Layer.h
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
/// -------------------------------------------------------------------------------------------------------------------

#ifndef BART_TILED_LAYER_H
#define BART_TILED_LAYER_H

#include <string>
#include <Color.h>
#include <CTileset.h>

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
        enum LayerDrawOrder
        {
            DO_INDEX,
            DO_TOPDOWN
        };

        struct TileInfo
        {
            int Index{0};
            bool HorizontalFlip{false};
            bool VerticalFlip{false};
            bool DiagonalFlip{false};
        };

        class Layer
        {
        public:
            virtual ~Layer() = default;
            virtual bool Load(XMLNode* aNodePtr);
            virtual void Clean() = 0;
            virtual void Draw(const Rectangle& aViewport) = 0;
            string GetName() const { return m_name; }

        protected:
            int m_id{0};
            string m_name;
            int m_x{0};
            int m_y{0};
            bool m_visible{true};
            unsigned char m_opacity{255};
            float m_offsetx{255};
            float m_offsety{255};
        };

        class TileLayer final : public Layer
        {
        public:
            TileLayer() = default;
            explicit TileLayer(Tileset* aTileset) { m_tilesetPtr = aTileset; }
            virtual ~TileLayer() = default;
            void ParseTileData(const char* aData);
            bool Load(XMLNode* aNode) override;
            void Clean() override;
            void Draw(const Rectangle& aViewport) override;

        private:
            typedef std::vector<std::vector<TileInfo*>> TTileMap;
            TTileMap mLayerData;
            int m_width{0};
            int m_height{0};
            Tileset* m_tilesetPtr{nullptr};
        };

        class ObjectLayer final : public Layer
        {
        public:
            virtual ~ObjectLayer() = default;
            bool Load(XMLNode* aNode) override;
            void Clean() override;
            void Draw(const Rectangle& aViewport) override;

        private:
            LayerDrawOrder ParseDrawOrder(const char* aValue) const;
            Color ParseColor(const char* aValue) const;

            Color m_color;
            int m_width{0};
            int m_height{0};
            LayerDrawOrder m_drawOrder{DO_TOPDOWN};
        };

        class ImageLayer final : public Layer
        {
        public:
            explicit ImageLayer(const string& aPath) { m_path = aPath; }
            virtual ~ImageLayer() = default;
            bool Load(XMLNode* aNodePtr) override;
            void Clean() override;
            void Draw(const Rectangle& aViewport) override;

        private:
            string m_path;
            Rectangle m_source;
            Rectangle m_destination;
            size_t m_textureId{0};
        };
    }
}

#endif
