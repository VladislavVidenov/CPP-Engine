#include "BoxBehaviour.h"

#include <glm.hpp>
#include "mge/core/GameObject.hpp"
#include <SFML/Graphics.hpp>

BoxBehaviour::BoxBehaviour(GameObject * player)
{
    _player = player;
    //ctor
}

BoxBehaviour::~BoxBehaviour()
{
    //dtor
}

void BoxBehaviour::update(float pStep){
  if (glm::distance(_owner->getWorldPosition(), _player->getWorldPosition())<2.0f){
    if ( sf::Keyboard::isKeyPressed( sf::Keyboard::E ) ) {
             _owner->setParent(_player);
        _owner->setTransform(_player->getTransform());
        _owner->translate(_player->getForward() * 2.0f);
        //_owner->translate(_owner->)

    }

  }
}
