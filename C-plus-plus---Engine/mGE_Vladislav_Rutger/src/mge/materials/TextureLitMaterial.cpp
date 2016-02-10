#include <glm.hpp>

#include "mge/materials/TextureLitMaterial.hpp"
#include "mge/core/Texture.hpp"
#include "mge/core/Camera.hpp"
#include "mge/core/World.hpp"
#include "mge/core/Mesh.hpp"
#include "Light.h"
#include "DirectionalLight.h"
#include "PointLight.h"
#include "mge/config.hpp"

ShaderProgram* TextureLitMaterial::_shader = NULL;

TextureLitMaterial::TextureLitMaterial(Texture * pDiffuseTexture,glm::vec3 pSpecular, float pShininess):
    _diffuseTexture(pDiffuseTexture),_specular(pSpecular),_shininess(pShininess)
{
    _lazyInitializeShader();
}

TextureLitMaterial::~TextureLitMaterial() {}

void TextureLitMaterial::_lazyInitializeShader() {
    if (!_shader) {
        _shader = new ShaderProgram();
        _shader->addShader(GL_VERTEX_SHADER, config::MGE_SHADER_PATH+"TextureLit.vs");
        _shader->addShader(GL_FRAGMENT_SHADER, config::MGE_SHADER_PATH+"TextureLit.fs");
        _shader->finalize();
    }
}

void TextureLitMaterial::setDiffuseTexture (Texture* pDiffuseTexture) {
    _diffuseTexture = pDiffuseTexture;
}

void TextureLitMaterial::render(World* pWorld, GameObject* pGameObject, Camera* pCamera) {
    if (!_diffuseTexture) return;

    _shader->use();

    //setup texture slot 0
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, _diffuseTexture->getId());


    //set material uniforms
    glUniform1i (_shader->getUniformLocation("matDiffuse"), 0);
    glUniform3fv (_shader->getUniformLocation("material.specular"),1, glm::value_ptr(_specular));
    glUniform1f (_shader->getUniformLocation("material.shininess"), _shininess);
    glUniform3fv(_shader->getUniformLocation("cameraPosition"),1, glm::value_ptr( pCamera->getWorldPosition()));
    int pointCount = 0;
    int spotCount = 0;
    for (int i =0; i < pWorld->getLightCount(); i++)
    {
            Light* temp = pWorld->getLightAt(i);
        switch(temp->type){
            case Light::LightType::Directional:

                break;
            case Light::LightType::Point:
                {

                }
                break;
            case Light::LightType::Spot:
                {

                }
                break;
        }
    }


    //pass in all MVP matrices separately
    glUniformMatrix4fv ( _shader->getUniformLocation("mat_Proj"),   1, GL_FALSE, glm::value_ptr(pCamera->getProjection()));
    glUniformMatrix4fv ( _shader->getUniformLocation("mat_View"),         1, GL_FALSE, glm::value_ptr(glm::inverse(pCamera->getWorldTransform())));
    glUniformMatrix4fv ( _shader->getUniformLocation("mat_Model"),        1, GL_FALSE, glm::value_ptr(pGameObject->getWorldTransform() ) );

    //now inform mesh of where to stream its data
    pGameObject->getMesh()->streamToOpenGL(
        _shader->getAttribLocation("vertex"),
        _shader->getAttribLocation("normal"),
        _shader->getAttribLocation("uv")
    );
}

