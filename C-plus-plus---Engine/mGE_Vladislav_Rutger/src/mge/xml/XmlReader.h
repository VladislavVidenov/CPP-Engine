#ifndef XMLREADER_H
#define XMLREADER_H

#include "pugixml.hpp"
#include <vector>
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

            template<typename T>
            T StringToNumber(const std::string& numberAsString);
        protected:
        private:
            pugi::xml_document doc;
            std::vector<pugi::xml_node> mainNodes;
            std::vector<pugi::xml_node> _objectProperties;

            std::vector<std::string> _objectNames;
            std::vector<std::string> _objectTags;
            std::vector<std::string> _objectTextures;
            std::vector<std::string> _normalTextures;
            std::vector<std::string> _colliderNames;

            std::vector<glm::vec3> _objectPositions;
            std::vector<glm::vec3> _colliderOffset;
            std::vector<glm::vec3> _colliderSize;
};

#endif // XMLREADER_H
