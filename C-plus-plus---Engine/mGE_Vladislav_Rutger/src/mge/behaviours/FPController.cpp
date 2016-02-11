#include <glm.hpp>
#include "mge/behaviours/FPController.h"
#include "mge/core/GameObject.hpp"
#include <SFML/Graphics.hpp>
GameObject* _camera;
FPController::FPController(float pMoveSpeed, float pTurnSpeed, GameObject * pCamera, InputType pInputType)
{
    _moveSpeed = pMoveSpeed;
    _turnSpeed = pTurnSpeed;
    _camera = pCamera;
    _inputType = pInputType;

}

FPController::~FPController()
{

}
bool _grounded = true;
void FPController::update(float pStep){

    glm::vec3 translate;
    float rotate = 0.0f;
    switch (_inputType)
    {
    case InputType::ArrowKeys:
        if ( sf::Keyboard::isKeyPressed( sf::Keyboard::Up ) ) translate += _camera->getForward() * 0.1f * _moveSpeed;
        if ( sf::Keyboard::isKeyPressed( sf::Keyboard::Down ) ) translate -= _camera->getForward() * 0.1f* _moveSpeed;
        if ( sf::Keyboard::isKeyPressed( sf::Keyboard::Left ) ) translate -= _camera->getRight() * 0.1f * _moveSpeed;
        if ( sf::Keyboard::isKeyPressed( sf::Keyboard::Right ) )translate += _camera->getRight() * 0.1f* _moveSpeed;
        break;
    case InputType::WASD:
        if ( sf::Keyboard::isKeyPressed( sf::Keyboard::W ) ) translate += _camera->getForward() * 0.1f* _moveSpeed;
        if ( sf::Keyboard::isKeyPressed( sf::Keyboard::S ) ) translate -= _camera->getForward() * 0.1f* _moveSpeed;
        if ( sf::Keyboard::isKeyPressed( sf::Keyboard::A ) ) translate -= _camera->getRight() * 0.1f* _moveSpeed ;
        if ( sf::Keyboard::isKeyPressed( sf::Keyboard::D ) ) translate += _camera->getRight() * 0.1f* _moveSpeed;

        if ( sf::Keyboard::isKeyPressed( sf::Keyboard::Space ) && _grounded) {translate.y += 4; _grounded = false;}

        break;
    }

    _owner->translate(translate); // - >> Move character on input.
    _owner->translate(glm::vec3(0,-0.5f,0)); // -> small gravity;
    glm::vec3 ownerLocPos  = _owner->getLocalPosition();
    if(ownerLocPos.y > 1 && ownerLocPos.y < 1.5f) _grounded = true;
    if(ownerLocPos.y <= 1) _owner->setLocalPosition(glm::vec3(ownerLocPos.x,1,ownerLocPos.z));

}
