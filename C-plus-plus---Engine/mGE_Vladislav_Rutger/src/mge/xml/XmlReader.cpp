#include "XmlReader.h"
#include <iostream>
#include <string>
#include <sstream>
#include <mge/config.hpp>

XmlReader::XmlReader()
{
    Read();
}

XmlReader::~XmlReader()
{
    //dtor
}

void XmlReader::Read()
{
     int counter;
  //  pugi::xml_parse_result result = ;
    if(!_xmlFile.load_file("mge/xml/test.xml")) std::cout<<"Couldn't load the file"<<std::endl;

    pugi::xml_node root = _xmlFile.child("GameObjects");
   // std::cout<< "ROOT XML => " << root.name() << std::endl;

    _mainNodes = GetNodeChildren(root);
   // std :: cout << "SIZE OF ROOT CHILDREN = > " << _mainNodes.size() << std::endl;

    for(counter=0; counter!= _mainNodes.size();counter++)
    {
        std::cout<<"Read child"<<std::endl;
        _objectNames.push_back(_mainNodes[counter].attribute("name").value());

        _objectProperties = GetNodeChildren(_mainNodes[counter]);
     //   std::cout << " object node properties =>> " << _objectProperties.size() << std::endl;
        // std::cout<< _objectProperties[0].attribute("name").value() <<std::endl;


     //   _objectTextures.push_back(_objectProperties[0].attribute("name").value());

   //     _normalTextures.push_back(_objectProperties[1].attribute("name").value());

        _objectPositions.push_back(glm::vec3(StringToNumber<float>(_objectProperties[3].attribute("X").value()),
                                            StringToNumber<float>(_objectProperties[3].attribute("Y").value()),
                                            StringToNumber<float>(_objectProperties[3].attribute("Z").value())));
//
//        _colliderNames.push_back(StringToNumber<float>(_objectProperties[4].attribute("Type").value()));
//
//
//
//        _colliderOffset.push_back(glm::vec3(StringToNumber<float>(_objectProperties[5].attribute("x").value()),
//                                            StringToNumber<float>(_objectProperties[5].attribute("y").value()),
//                                            StringToNumber<float>(_objectProperties[5].attribute("z").value())));
//
        _colliderSize.push_back(glm::vec3(StringToNumber<float>(_objectProperties[6].attribute("X").value()),
                                            StringToNumber<float>(_objectProperties[6].attribute("Y").value()),
                                            StringToNumber<float>(_objectProperties[6].attribute("Z").value())));
    }


}

std::vector<pugi::xml_node> XmlReader::GetNodeChildren(pugi::xml_node node)
{
        std::vector<pugi::xml_node> values;

        for (node = node.first_child(); node; node = node.next_sibling()) {
            values.push_back(node);
        }

        return values;
}

template<typename T>
T XmlReader::StringToNumber(const std::string& numberAsString)
{
    T value;
    std::stringstream stream(numberAsString);
    stream >> value;
    return value;
}
