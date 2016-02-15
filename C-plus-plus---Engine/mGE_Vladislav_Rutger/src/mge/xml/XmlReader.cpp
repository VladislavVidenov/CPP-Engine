#include "XmlReader.h"

#include "mge/config.hpp"

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
    if(!_xmlFile.load_file("mge/xml/Cube.xml")) std::cout<<"Couldn't load the file"<<std::endl;

    pugi::xml_node root = _xmlFile.child("GameObjects");
   // std::cout<< "ROOT XML => " << root.name() << std::endl;

    _mainNodes = GetNodeChildren(root);
   // std :: cout << "SIZE OF ROOT CHILDREN = > " << _mainNodes.size() << std::endl;

    for(counter=0; counter!= _mainNodes.size();counter++)
    {
        std::cout<<"Read child"<<std::endl;
        //Add names to a list
        _names.push_back(_mainNodes[counter].attribute("name").value());
        //Read all object node children
        _objectProperties = GetNodeChildren(_mainNodes[counter]);
        //Store positions
        _positions.push_back(glm::vec3(StringToNumber<float>(_objectProperties[3].attribute("X").value()),
                                            StringToNumber<float>(_objectProperties[3].attribute("Y").value()),
                                            StringToNumber<float>(_objectProperties[3].attribute("Z").value())));
        //Store scales
        _scales.push_back(glm::vec3(StringToNumber<float>(_objectProperties[5].attribute("X").value()),
                                            StringToNumber<float>(_objectProperties[5].attribute("Y").value()),
                                            StringToNumber<float>(_objectProperties[5].attribute("Z").value())));
    }
}
void XmlReader::SetupObjects()
{
    for(int i = 0; i < _names.size(); i++)
    {
        GameObject * obj = new GameObject(_names[i],_positions[i]);
        obj->setMesh(Mesh::load(config::MGE_MODEL_PATH  + "Cubet.obj"));
        obj->setMaterial(new ColorMaterial());
       // obj->scale(_scales[i]);

        glm::vec3 boxColSize(_scales[i]);
        //boxColSize.x *= -1;
        glm::vec3 halfSize = boxColSize * .5f;

        glm::vec3 offset = obj->getLocalPosition();

        glm::vec3 minBounds(offset.x - halfSize.x,
                            offset.y - halfSize.y,
                            offset.z - halfSize.z);
        glm::vec3 maxBounds(offset.x + halfSize.x,
                            offset.y + halfSize.y,
                            offset.z + halfSize.z);


        obj->setCollider(new BoxCollider(minBounds,maxBounds));
        objects.push_back(obj);
        //_collisionManager->addObject(colCube);
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
