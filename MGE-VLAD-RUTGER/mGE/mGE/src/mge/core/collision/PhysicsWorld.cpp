#include "PhysicsWorld.h"

#include "mge/core/collision/RigidbodyGameObject.h"
#include "mge/core/collision/StaticGameObject.h"


PhysicsWorld::PhysicsWorld(int pStaticGameObjectsCount, int pRigidbodyGameObjectsCount)
{
	//store needed data for the physics simulator and on creation give the data to it.
	neSimulatorSizeInfo simulatorSize;

	//store it in physics engine type of data.
	s32 rbCount = pRigidbodyGameObjectsCount;
	s32 stCount = pStaticGameObjectsCount;
	
	simulatorSize.rigidBodiesCount = rbCount;
	simulatorSize.animatedBodiesCount = stCount;

	s32 totalCount = rbCount + stCount;
	simulatorSize.geometriesCount = totalCount;

	simulatorSize.overlappedPairsCount = totalCount * (totalCount - 1) / 2;


	//Not used
	simulatorSize.rigidParticleCount = 0;
	simulatorSize.constraintsCount = 0;
	simulatorSize.terrainNodesStartCount = 0;

	//Generate gravity
	neV3 gravity;
	gravity.Set(.0f, -5.0f, .0f);

	//start the physics simulation
	_physicsSimulator = neSimulator::CreateSimulator(simulatorSize, NULL, &gravity);
}

PhysicsWorld::~PhysicsWorld()
{
    //dtor
}


void PhysicsWorld::update(float pStep, const glm::mat4& pParentTransform)
{
	World::update(pStep, pParentTransform);
//	std::cout << "Update physiiics" << std::endl;

	for (int i = 0; i < _staticGameObjects.size(); i++)
	{
		_staticGameObjects[i]->updateStaticBody();
	}
	_physicsSimulator->Advance(pStep);

	for (int i  = 0; i < _rigidbodyGameObjects.size(); i++)
	{
		_rigidbodyGameObjects[i]->updateRigidBody();
	}
	
}


neRigidBody* PhysicsWorld::addRigidBodyObject(RigidbodyGameObject * pRbGameObject)
{
	_rigidbodyGameObjects.push_back(pRbGameObject);
	return _physicsSimulator->CreateRigidBody();
}

neAnimatedBody* PhysicsWorld::addStaticGameObject(StaticGameObject * pStaticGameobject)
{
	_staticGameObjects.push_back(pStaticGameobject);
	return _physicsSimulator->CreateAnimatedBody();
}

void PhysicsWorld::freeMemory(neRigidBody* pNeRb)
{

}
void PhysicsWorld::freeMemory(neAnimatedBody* pAnimbody)
{

}