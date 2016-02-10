#include <cassert>
#include <algorithm>
#include <iostream>
#include "mge/core/World.hpp"
#include "mge/core/Camera.hpp"
#include "mge/core/Mesh.hpp"
#include "Light.h"

using namespace std;

World::World():GameObject("root"), _mainCamera(0),_lights()
{
	//ctor
	GameObject::_world = this;
}

void World::setMainCamera (Camera* pCamera) {
    if (pCamera != NULL) _mainCamera = pCamera;
}

void World::AddLight(Light* pLight){
    _lights.push_back(pLight);
}
int World::getLightCount() {
    return _lights.size();
}

Light* World::getLightAt(int pIndex) {
    return _lights[pIndex];
}
Camera* World::getMainCamera () {
    return _mainCamera;
}

void World::renderDebugInfo() {
    //walk through all meshes and debug their normals
    GameObject* gameObject;
    for (int i = 0; i < getChildCount(); i++) {
        gameObject = getChildAt(i);
        //oo wise it would be better to do gameObject->renderDebugInfo, but since this is only for debugging
        //it's sort of pasted on
        if (gameObject->getMaterial() && gameObject->getMesh()) {
            gameObject->getMesh()->renderDebugInfo(gameObject->getWorldTransform(), this);
        }
    }
}

