#ifndef XMLREADER_H
#define XMLREADER_H
#include "pugixml.hpp"
#include <vector>
#include <iostream>
#include "glm.hpp"
#include "mge/core/GameObject.hpp"


class XmlReader
{
    public:
            XmlReader();
            virtual ~XmlReader();
            void Read();
            std::vector<pugi::xml_node> GetNodeChildren(pugi::xml_node node);
            void LoadObjects();
        //    void setUpPhysics();
            std::vector<GameObject *> objects;

            std::vector<std::string> _objectNames;
            std::vector<std::string> _objectTags;
            std::vector<std::string> _objectTextures;
            std::vector<std::string> _normalTextures;
            std::vector<float> _colliderNames;

            std::vector<glm::vec3> _objectPositions;
            std::vector<glm::vec3> _colliderOffset;
            std::vector<glm::vec3> _colliderSize;

            template<typename T>
            T StringToNumber(const std::string& numberAsString);
        protected:
        private:

            pugi::xml_document _xmlFile;
            std::vector<pugi::xml_node> _mainNodes;
            std::vector<pugi::xml_node> _objectProperties;


};

#endif // XMLREADER_H
