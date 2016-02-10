#include "PointLight.h"

PointLight::PointLight(std::string pName, glm::vec3 pPosition,glm::vec3 pAmbient,glm::vec3 pDiffuse, glm::vec3 pSpecular):
            Light(pName,pPosition,pAmbient,pDiffuse,pSpecular)
{
    type = LightType::Point;
}

PointLight::~PointLight()
{
    //dtor
}
