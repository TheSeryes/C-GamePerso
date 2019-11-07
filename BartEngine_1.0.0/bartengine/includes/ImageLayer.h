#ifndef BART_TILED_IMAGE_LAYER
#define BART_TILED_IMAGE_LAYER

#include <Layer.h>
#include <string>
#include <Sprite.h>

namespace tinyxml2
{
    class XMLNode;
}

using namespace tinyxml2;

namespace bart
{
    class ImageLayer final : public Layer
    {
    public:
        virtual ~ImageLayer() = default;
        bool Load(XMLNode* aNode, const std::string& aAssetPath);
        void Draw(int aFromX, int aFromY, int aToX, int aToY, int aWidth, int aHeight) override;
        void Clean() override;

    private:
        unsigned m_TextureId{0};
        Rectangle m_Source;
        Rectangle m_Destination;
    };
}

#endif
