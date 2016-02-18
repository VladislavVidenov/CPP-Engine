#include "RigidbodyGameObject.h"
#include "mge/core/collision/PhysicsWorld.h"
#include "SFML\Graphics.hpp"

RigidbodyGameObject::RigidbodyGameObject(std::string pName, glm::vec3 pPosition, PhysicsWorld* pWorld) :
	GameObject(pName,pPosition),
	_rigidbody (pWorld->addRigidBodyObject(this))
{

	

	neV3 position;
	position.Set(pPosition.x, pPosition.y, pPosition.z);
	_rigidbody->SetPos(position);
}


RigidbodyGameObject::~RigidbodyGameObject()
{

}

void RigidbodyGameObject::moveRb(glm::vec3 pPos)
{
	neV3 posToSet;
	posToSet.Set(pPos.x, pPos.y, pPos.z);
	_rigidbody->SetVelocity( posToSet);
}
void RigidbodyGameObject::updateRigidBody()
{
	if (_name == "Player")
	{
		glm::vec3 translate;
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) translate += getForward() ;
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) translate -= getForward() ;
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) translate -= getRight() ;
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) translate += getRight() ;
		std::cout << "translate " << translate << std::endl;
		//if (abs(translate.x) == 1 && abs(translate.z) == 1) translate *= 0.707f; else translate *= 1;
		if (glm::length(translate)> 0) moveRb(translate);
	}
	neV3 rbPos = _rigidbody->GetPos();

	glm::vec3 toGLMpos = glm::vec3(rbPos[0],rbPos[1],rbPos[2]);

	//neM3 rbRotationMatrix = _rigidbody->GetRotationM3();
	//
	////set gameobject transform
	//setTransform(glm::mat4x4(
	//	rbRotationMatrix[0][0], rbRotationMatrix[0][1], rbRotationMatrix[0][2], 0,
	//	rbRotationMatrix[1][0], rbRotationMatrix[1][1], rbRotationMatrix[1][2], 0,
	//	rbRotationMatrix[2][0], rbRotationMatrix[2][1], rbRotationMatrix[2][2], 0,
	//				toGLMpos.x,			    toGLMpos.y,				toGLMpos.z, 1
	//	));
	neV3 rbVel;
	rbVel.Set(_rigidbody->GetVelocity());
	glm::vec3 glmRbVel(rbVel[0], rbVel[1], rbVel[2]);

//	std::cout << "Rigid body velocity " << glm::length(glmRbVel) << std::endl;
	setWorldPosition(toGLMpos);
}

void RigidbodyGameObject::AddBoxCollider(float pW, float pH, float pD)
{
	neGeometry* geometry = _rigidbody->AddGeometry();
	neV3 box;
	box.Set(pW, pH, pD);
	geometry->SetBoxSize(box);
	_rigidbody->UpdateBoundingInfo();
}
