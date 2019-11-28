/// -------------------------------------------------------------------------------------------------------------------
/// BartEngine
/// File: Properties.h
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
/// Reference: https://doc.mapeditor.org/en/stable/reference/tmx-map-format/#properties
/// -------------------------------------------------------------------------------------------------------------------

#ifndef BART_TILED_PROPERTIES_H
#define BART_TILED_PROPERTIES_H

#include <string>
#include <map>
#include <Color.h>

namespace tinyxml2
{
    class XMLNode;
}

using namespace tinyxml2;

namespace bart
{
    namespace tiled
    {
        class Property;

        enum EPropertyType
        {
            PT_BOOL,
            PT_COLOR,
            PT_FLOAT,
            PT_INT,
            PT_STRING
        };

        class Properties
        {
        public:
            void Load(XMLNode* aNode);
            bool GetBool(const std::string& aName);
            Color GetColor(const std::string& aName);
            float GetFloat(const std::string& aName);
            std::string GetString(const std::string& aName);
            int GetInt(const std::string& aName);
            void Add(const std::string& aName, Property* aProperty);
            void Clear();

        private:
            typedef std::map<std::string, Property*> TPropertyMap;
            TPropertyMap m_PropertyMap;
        };

        ///
        /// Wraps any number of custom properties. Can be used as a child of the map, tileset,
        /// tile (when part of a tileset), terrain, layer, objectgroup, object, imagelayer and group elements.
        ///
        class Property
        {
        public:
            virtual ~Property() = default;
            EPropertyType GetType() const { return m_Type; }

        protected:
            EPropertyType m_Type{PT_STRING};
        };

        class BoolProperty final : public Property
        {
        public:
            BoolProperty();
            virtual ~BoolProperty() = default;
            bool Value{false};
        };

        class ColorProperty final : public Property
        {
        public:
            ColorProperty();
            virtual ~ColorProperty() = default;
            void SetFromHex(const std::string& aHexValue);
            Color Value{};
        };

        class FloatProperty final : public Property
        {
        public:
            FloatProperty();
            virtual ~FloatProperty() = default;
            float Value{0.0f};
        };

        class StringProperty final : public Property
        {
        public:
            StringProperty();
            virtual ~StringProperty() = default;
            std::string Value;
        };

        class IntProperty final : public Property
        {
        public:
            IntProperty();
            virtual ~IntProperty() = default;
            int Value{0};
        };
    }
}
#endif
