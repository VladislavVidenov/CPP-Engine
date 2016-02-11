//#include "XmlReader.h"
//
//XmlReader::XmlReader()
//{
//    //ctor
//}
//
//XmlReader::~XmlReader()
//{
//    //dtor
//}
//
//void XmlReader::Read()
//{
//     int counter;
//
//        if(!doc.load_file("Assets/SceneData.xml")) std::cout<<"Couldn't load the file"<<std::endl;
//        pugi::xml_node root = doc.child("GameObjects");
//
//        mainNodes = GetNodeChildren(root);
//
//        for(counter=0; counter!= mainNodes.size();counter++){
//            _objectNames.push_back(mainNodes[counter].attribute("name").value());
//            _objectProperties = GetNodeChildren(mainNodes[counter]);
//-
//
//
//            //_objectTags.push_back(_objectProperties[0].attribute("name").value());
//
//            _objectTextures.push_back(_objectProperties[0].attribute("name").value());
//
//            _normalTextures.push_back(_objectProperties[1].attribute("name").value());
//
//            _objectPositions.push_back(glm::vec3(StringToNumber<float>(_objectProperties[2].attribute("x").value()),
//                                                 StringToNumber<float>(_objectProperties[2].attribute("y").value()),
//                                                 StringToNumber<float>(_objectProperties[2].attribute("z").value())));
//
//            _colliderNames.push_back(_objectProperties[3].attribute("type").value());
//
//            _colliderSize.push_back(glm::vec3(StringToNumber<float>(_objectProperties[4].attribute("x").value()),
//                                              StringToNumber<float>(_objectProperties[4].attribute("y").value()),
//                                              StringToNumber<float>(_objectProperties[4].attribute("z").value())));
//
//            _colliderOffset.push_back(glm::vec3(StringToNumber<float>(_objectProperties[5].attribute("x").value()),
//                                                StringToNumber<float>(_objectProperties[5].attribute("y").value()),
//                                                StringToNumber<float>(_objectProperties[5].attribute("z").value())));
//        }
//
//}
