/// -------------------------------------------------------------------------------------------------------------------
/// BartEngine
/// File: Properties.cpp
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

#include <CProperties.h>
#include <Color.h>
#include <tinyxml2.h>
#include <StringHelper.h>

//  
//   ____              _ ____                            _         
//  | __ )  ___   ___ | |  _ \ _ __ ___  _ __   ___ _ __| |_ _   _ 
//  |  _ \ / _ \ / _ \| | |_) | '__/ _ \| '_ \ / _ \ '__| __| | | |
//  | |_) | (_) | (_) | |  __/| | | (_) | |_) |  __/ |  | |_| |_| |
//  |____/ \___/ \___/|_|_|   |_|  \___/| .__/ \___|_|   \__|\__, |
//                                      |_|                  |___/ 
//  
bart::tiled::BoolProperty::BoolProperty()
{
    m_Type = PT_BOOL;
}


bart::tiled::ColorProperty::ColorProperty()
{
    m_Type = PT_COLOR;
}

void bart::tiled::ColorProperty::SetFromHex(const std::string& aHexValue)
{
    unsigned char tR, tG, tB, tA;
    StringHelper::GetColorComponents(aHexValue, &tR, &tG, &tB, &tA);
    Value.Set(tR, tG, tB, tA);
}

bart::tiled::FloatProperty::FloatProperty()
{
    m_Type = PT_FLOAT;
}

bart::tiled::StringProperty::StringProperty()
{
    m_Type = PT_STRING;
}

bart::tiled::IntProperty::IntProperty()
{
    m_Type = PT_INT;
}

void bart::tiled::Properties::Load(XMLNode* aNode)
{
    XMLNode* tPropNode = aNode->FirstChild();
    while (tPropNode != nullptr)
    {
        XMLElement* tParamElement = tPropNode->ToElement();
        const char* tName = tParamElement->Attribute("name");
        const char* tType = tParamElement->Attribute("type");

        if (tName != nullptr)
        {
            std::string tKey = std::string(tName);
            std::string tTypeStr;

            if (tType == nullptr)
            {
                tTypeStr = "string";
            }
            else
            {
                tTypeStr = std::string(tType);
            }

            if (tTypeStr == "bool")
            {
                BoolProperty* tBoolProperty = new BoolProperty();
                tBoolProperty->Value = tParamElement->BoolAttribute("value");
                Add(tName, tBoolProperty);
            }
            else if (tTypeStr == "color")
            {
                const char* tColorHex = tParamElement->Attribute("value");

                if (tColorHex != nullptr)
                {
                    ColorProperty* tColorProperty = new ColorProperty();
                    tColorProperty->SetFromHex(std::string(tColorHex));
                    Add(tName, tColorProperty);
                }
            }
            else if (tTypeStr == "float")
            {
                FloatProperty* tFloatProperty = new FloatProperty();
                tFloatProperty->Value = tParamElement->FloatAttribute("value");
                Add(tName, tFloatProperty);
            }
            else if (tTypeStr == "file")
            {
                const char* tFileName = tParamElement->Attribute("value");

                if (tFileName != nullptr)
                {
                    StringProperty* tFileProperty = new StringProperty();
                    tFileProperty->Value = std::string(tFileName);
                    Add(tName, tFileProperty);
                }
            }
            else if (tTypeStr == "int")
            {
                IntProperty* tIntProperty = new IntProperty();
                tIntProperty->Value = tParamElement->BoolAttribute("value");
                Add(tName, tIntProperty);
            }
            else if (tTypeStr == "string")
            {
                const char* tString = tParamElement->Attribute("value");

                if (tString != nullptr)
                {
                    StringProperty* tStringProperty = new StringProperty();
                    tStringProperty->Value = std::string(tString);
                    Add(tName, tStringProperty);
                }
            }
        }

        tPropNode = tPropNode->NextSibling();
    }
}

bool bart::tiled::Properties::GetBool(const std::string& aName)
{
    if (m_PropertyMap.count(aName) > 0)
    {
        if (m_PropertyMap[aName]->GetType() == PT_BOOL)
        {
            return static_cast<BoolProperty*>(m_PropertyMap[aName])->Value;
        }
    }

    return "";
}

bart::Color bart::tiled::Properties::GetColor(const std::string& aName)
{
    if (m_PropertyMap.count(aName) > 0)
    {
        if (m_PropertyMap[aName]->GetType() == PT_COLOR)
        {
            return static_cast<ColorProperty*>(m_PropertyMap[aName])->Value;
        }
    }

    return Color::Black;
}

float bart::tiled::Properties::GetFloat(const std::string& aName)
{
    if (m_PropertyMap.count(aName) > 0)
    {
        if (m_PropertyMap[aName]->GetType() == PT_FLOAT)
        {
            return static_cast<FloatProperty*>(m_PropertyMap[aName])->Value;
        }
    }

    return 0.0f;
}

std::string bart::tiled::Properties::GetString(const std::string& aName)
{
    if (m_PropertyMap.count(aName) > 0)
    {
        if (m_PropertyMap[aName]->GetType() == PT_STRING)
        {
            return static_cast<StringProperty*>(m_PropertyMap[aName])->Value;
        }
    }

    return "";
}

int bart::tiled::Properties::GetInt(const std::string& aName)
{
    if (m_PropertyMap.count(aName) > 0)
    {
        if (m_PropertyMap[aName]->GetType() == PT_INT)
        {
            return static_cast<IntProperty*>(m_PropertyMap[aName])->Value;
        }
    }

    return 0;
}

void bart::tiled::Properties::Add(const std::string& aName, Property* aProperty)
{
    if (m_PropertyMap.count(aName) == 0)
    {
        m_PropertyMap[aName] = aProperty;
    }
}

void bart::tiled::Properties::Clear()
{
    for (TPropertyMap::iterator i = m_PropertyMap.begin(); i != m_PropertyMap.end(); ++i)
    {
        delete i->second;
    }

    m_PropertyMap.clear();
}
