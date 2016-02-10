#ifndef WORLD_H
#define WORLD_H

#include <vector>
#include "mge/core/GameObject.hpp"

class Light;
class Camera;

class World : public GameObject
{
	public:
        World();

		void setMainCamera (Camera* pCamera);
		Camera* getMainCamera();

        void renderDebugInfo();

        void AddLight(Light* pLight);
        const std::vector<Light*>& GetLights(){return _lights;};
        int getLightCount();
        Light* getLightAt(int pIndex);


    protected:
        std::vector<Light*> _lights;
	private:
	    Camera* _mainCamera;

};


#endif // WORLD_H
