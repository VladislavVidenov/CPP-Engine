//#include <glm.hpp>
#include <iostream>
#include <string>
using namespace std;
#include "mge/core/Renderer.hpp"
#include "XmlReader.h"
#include "mge/core/Mesh.hpp"
#include "mge/core/World.hpp"
#include "CollisionManager.h"
#include "mge/core/FPS.hpp"

#include "mge/core/Camera.hpp"

#include "mge/core/GameObject.hpp"
#include "Light.h"
#include "DirectionalLight.h"
#include "PointLight.h"
#include "SpotLight.h"
#include "mge/materials/AbstractMaterial.hpp"

#include "mge/materials/ColorMaterial.hpp"
#include "mge/materials/TerrainMaterial.hpp"
#include "mge/materials/TextureMaterial.hpp"
#include "mge/materials/VertexLitColorMaterial.hpp"
#include "mge/materials/FragLitColorMaterial.hpp"
#include "mge/materials/PointLightMaterial.hpp"
#include "mge/materials/PointLightAttenuationMaterial.hpp"
#include "mge/materials/TextureLitMaterial.hpp"
#include "mge/materials/WobblyMaterial.hpp"
#include "mge/materials/TextureNormalMaterial.hpp"
#include "mge/materials/SpotLightMaterial.hpp"



#include "mge/behaviours/RotatingBehaviour.hpp"
#include "mge/behaviours/KeysBehaviour.hpp"
#include "mge/behaviours/KeysBehaviour2.hpp"
#include "mge/behaviours/FPController.h"
#include "mge/behaviours/BoxBehaviour.h"
#include "mge/behaviours/DoorBehaviour.h"

#include "mge/behaviours/TriggerBehaviour.h"
#include "mge/behaviours/FPCamera.h"
#include "mge/behaviours/LookAt.hpp"
#include "mge/behaviours/Orbit.hpp"
#include "Color.h"

//collision
#include "Collider.h"
#include "BoxCollider.h"
#include "SphereCollider.h"
#include "Collision.h"

#include "mge/util/DebugHud.hpp"

#include "mge/config.hpp"
#include "mge/MGEDemo.hpp"


//construct the game class into _window, _renderer and hud (other parts are initialized by build)
MGEDemo::MGEDemo():AbstractGame ()
{
}

void MGEDemo::initialize() {
    //setup the core part
    AbstractGame::initialize();

    //setup the custom part
	cout << "Initializing HUD" << endl;
	_hud = new DebugHud(_window);
	cout << "HUD initialized." << endl << endl;
}

AbstractMaterial* pointLightMaterial;
AbstractMaterial* pointAttenuationMat;
PointLight* light2;
 GameObject* Player ;
 GameObject* room ;
GameObject* pilars ;
GameObject* roof ;
GameObject* spikes ;
 BoxCollider  * playerCol;
 BoxCollider  * boxCol;
 BoxCollider  * boxCol2;
GameObject* box;
//build the game _world
void MGEDemo::_initializeScene()
{
  //  _renderer->setClearColor(100,100,100);
    _renderer->setClearColor(0,0,0);

 //===============================  M E S H E S ====================================================================================================================================================//

    //load a bunch of meshes we will be using throughout this demo
    //each mesh only has to be loaded once, but can be used multiple times:
    //F is flat shaded, S is smooth shaded (normals aligned or not), check the models folder!
   Mesh* planeHighPoly = Mesh::load (config::MGE_MODEL_PATH+"plane_8192.obj");
    Mesh* planeQuad = Mesh::load (config::MGE_MODEL_PATH+"NormalPlane.obj");

    Mesh* cubeMeshF = Mesh::load (config::MGE_MODEL_PATH+"cube_flat.obj");
    Mesh* t_Model = Mesh::load (config::MGE_MODEL_PATH+"t_Model.obj");
   // Mesh* suzannaMeshF = Mesh::load (config::MGE_MODEL_PATH+"suzanna_flat.obj");
   // Mesh* sphereMesh = Mesh::load (config::MGE_MODEL_PATH+"sphere_smooth.obj");
    Mesh* teapotMeshS = Mesh::load (config::MGE_MODEL_PATH+"teapot_smooth.obj");
   // Mesh* handgunMesh = Mesh::load (config::MGE_MODEL_PATH+"handgun.obj");

   Mesh* roomMesh = Mesh::load (config::MGE_MODEL_PATH+"Room.obj");
    Mesh* pilarsMesh = Mesh::load (config::MGE_MODEL_PATH+"Pilars.obj");
    Mesh* roofMesh = Mesh::load (config::MGE_MODEL_PATH+"Roof.obj");
    Mesh* spikesMesh = Mesh::load (config::MGE_MODEL_PATH+"Spikes.obj");
    Mesh* CUPE = Mesh::load (config::MGE_MODEL_PATH+"CUPE.obj");
//=====================================================================================================================================================================================================//





   //===============================  M A T E R I A L S ====================================================================================================================================================//
    AbstractMaterial * spotLightMaterial = new SpotLightMaterial(Color::Red);

    //MATERIALS
    AbstractMaterial * wobbleMat = new WobblyMaterial(Texture::load(config::MGE_TEXTURE_PATH+"bricks.jpg"));

    //Wobbling material <--not wobbling .. is texturenormal now
  //  AbstractMaterial* wobblingMaterial = new TextureNormalMaterial(Texture::load (config::MGE_TEXTURE_PATH+"pistol.png"),glm::vec3(.3f),32.f,Texture::load(config::MGE_TEXTURE_PATH + "pistolNormal.png"));
 //   AbstractMaterial* wobblingMaterial2 = new TextureNormalMaterial(Texture::load (config::MGE_TEXTURE_PATH+"test.jpg"),glm::vec3(.3f),32.f,Texture::load(config::MGE_TEXTURE_PATH + "testNormal.jpg"));
 //   AbstractMaterial* wobblingMaterial3 = new TextureNormalMaterial(Texture::load (config::MGE_TEXTURE_PATH+"rocks.jpg"),glm::vec3(.3f),32.f,Texture::load(config::MGE_TEXTURE_PATH + "rocksnormal.png"));

  //  AbstractMaterial* pistolMat = new TextureLitMaterial(Texture::load (config::MGE_TEXTURE_PATH+"pistol.png"),glm::vec3(.3f),32.f);

    //Texture Material + Light !
    AbstractMaterial* wallMat = new TextureLitMaterial(Texture::load (config::MGE_TEXTURE_PATH+"test.jpg"),32.f);

    AbstractMaterial* pillarMat = new TextureLitMaterial(Texture::load (config::MGE_TEXTURE_PATH+"pillar.jpg"),32.f);
    //Simple Texture material - No light
    AbstractMaterial* textureMaterial = new TextureMaterial (Texture::load (config::MGE_TEXTURE_PATH+"land.jpg"));

    AbstractMaterial* terrainMaterial = new TerrainMaterial (Texture::load (config::MGE_TEXTURE_PATH+"diffuse1.jpg"),
                                                             Texture::load (config::MGE_TEXTURE_PATH+"water.jpg"),
                                                             Texture::load (config::MGE_TEXTURE_PATH+"diffuse3.jpg"),
                                                             Texture::load (config::MGE_TEXTURE_PATH+"diffuse4.jpg"),
                                                             Texture::load (config::MGE_TEXTURE_PATH+"splatmap.png"),
                                                             Texture::load (config::MGE_TEXTURE_PATH+"heightmap.png"));
    AbstractMaterial* textureMaterial2 = new TextureMaterial (Texture::load (config::MGE_TEXTURE_PATH+"bricks.jpg"));

    AbstractMaterial * blueMaterial = new ColorMaterial(glm::vec3(0,0,1));
    AbstractMaterial * redMaterial = new ColorMaterial(glm::vec3(1,0,0));
    AbstractMaterial * greenMaterial = new ColorMaterial(glm::vec3(0,1,0));
    AbstractMaterial * maroonMaterial = new ColorMaterial(Color::Maroon);


 //==========================================================================================================================================================================================================================//

    DoorBehaviour * doorBehaviour = new DoorBehaviour();





    Camera* camera = new Camera ("camera", glm::vec3(0,0,0));
    _world->add(camera);
    _world->setMainCamera(camera);

    Player = new GameObject ("plane2", glm::vec3(8,1,8));
    Player->setMesh(cubeMeshF);
    Player->setMaterial(maroonMaterial);
    Player->setBehaviour(new FPController(0.3f,1.0f,camera,FPController::InputType::WASD));
    //Player->scale(glm::vec3(1f));
    _world->add(Player);

    camera->setParent(Player);
    camera->setLocalPosition(glm::vec3(0,5,0));
    camera->rotate(glm::radians(-90.f),glm::vec3(1,0,0));
   // camera->setBehaviour(new FPCamera(1.0f,1.0f,Player,_window));

//    GameObject* cube = new GameObject ("cube", glm::vec3(0,0,0));
//    cube->setMesh (cubeMeshF);
//    cube->setMaterial(textureMaterial);
//    cube->scale(glm::vec3(1));
//    _world->add(cube);

    /** GameObject* plane2
            Multiple lights
*/
    room = new GameObject ("room", glm::vec3(0,0,0));
    room->setMesh(roomMesh);
    room->setMaterial(wallMat);
    _world->add(room);

     roof = new GameObject ("roof", glm::vec3(0,0,0));
    roof->setMesh(roofMesh);
    roof->setMaterial(textureMaterial2);
    _world->add(roof);

    spikes = new GameObject ("spikes", glm::vec3(0,0,0));
    spikes->setMesh(spikesMesh);
    spikes->setMaterial(textureMaterial2);
    _world->add(spikes);

       pilars = new GameObject ("pilars", glm::vec3(0,0,0));
    pilars->setMesh(pilarsMesh);
    pilars->setMaterial(pillarMat);
    _world->add(pilars);

//    GameObject* teapot = new GameObject ("teapot", glm::vec3(0,0,0));
//    teapot->setMesh (teapotMeshS);
//    teapot->setMaterial(textureLit);
//    teapot->setBehaviour (new KeysBehaviour());
//    _world->add(teapot);
//
    box = new GameObject ("box", glm::vec3(-2,0.25f,1));
    box->setMesh (cubeMeshF);
    box->setMaterial(redMaterial);
    box->setBehaviour(new BoxBehaviour(Player));
    _world->add(box);
    box->scale(glm::vec3(0.2f));

    GameObject* door = new GameObject ("door", glm::vec3(4,1,0));
    door ->setMesh (cubeMeshF);
    door ->setMaterial(greenMaterial);
    door->setBehaviour(doorBehaviour);
    doorBehaviour->InitializePositions(glm::vec3(0,2.0f,0));
    _world->add(door );
    door ->scale(glm::vec3(0.2f,1.0f,0.5f));

    GameObject* trigger = new GameObject ("trigger", glm::vec3(2,.25f,0));
    trigger ->setMesh (cubeMeshF);
    trigger ->setMaterial(blueMaterial);
    trigger->setBehaviour(new TriggerBehaviour(box, doorBehaviour));
    _world->add(trigger );
    trigger ->scale(glm::vec3(0.2f));




    //{ LIGHTS
    //Directional Light
    Light *dirLight = new DirectionalLight("Directional Light", glm::vec3(10,7,10),glm::vec3(1,0,1),glm::vec3(.5f,.5f,.5f),glm::vec3(1.f,1.f,1.f),glm::vec3(1,1,1));

    //Points lights

    Light *light = new PointLight("PointLight1", glm::vec3(2,2,0),glm::vec3(.1f),glm::vec3(Color::Green),glm::vec3(0.3f));
    AbstractMaterial* lightMaterial = new ColorMaterial(light->diffuse);
    light->setMesh(cubeMeshF);
    light->setMaterial(lightMaterial);
    _world->add(light);
    light->scale(glm::vec3(0.2f,0.2f,0.2f));
    //light->setBehaviour(new KeysBehaviour2());

    light2 = new PointLight("PointLight2", glm::vec3(-7,2,0),glm::vec3(.1f),glm::vec3(1),glm::vec3(0.3f));
//    AbstractMaterial* lightMaterial2 = new ColorMaterial(light2->diffuse);
//    light2->setMesh(cubeMeshF);
//    light2->setMaterial(lightMaterial2);
    _world->add(light2);
//    light2->scale(glm::vec3(0.2f,0.2f,0.2f));
   // light2->setBehaviour(new KeysBehaviour2());

    Light *light3 = new SpotLight("SpotLight",glm::vec3(0,-1,0),glm::vec3(.1f),glm::vec3(Color::Red),glm::vec3(.5f));
//    AbstractMaterial* lightMaterial3 = new ColorMaterial(light3->diffuse);
//    light3->setMesh(cubeMeshF);
//    light3->setMaterial(lightMaterial3);
    _world->add(light3);
//    light3->scale(glm::vec3(0.2f,0.2f,0.2f));
  //  light3->setBehaviour(new KeysBehaviour2());
    //}


    //ADD OBJECTS TO WORLD ! ================================================================



    //Add Lights
//    _world->AddLight(dirLight);
    _world->AddLight(light);
    _world->AddLight(light2);
    _world->AddLight(light3);
   // _world->AddLight(light4);
    //======================================================================================
    //PHYSICS TESTS



    for(int i = 0 ; i < 100 ; i++)
    {

        GameObject* colCube = new GameObject ("colCubeA ", glm::vec3(5 + i,1,5+i ));
        colCube ->setMesh (cubeMeshF);
        colCube ->setMaterial(blueMaterial);
        _world->add(colCube );



        glm::vec3 boxColSize(2,2,2);
        glm::vec3 halfSize = boxColSize * .5f;

        glm::vec3 offset = colCube->getLocalPosition();

        glm::vec3 minBounds(offset.x - halfSize.x,
                            offset.y - halfSize.y,
                            offset.z - halfSize.z);
        glm::vec3 maxBounds(offset.x + halfSize.x,
                            offset.y + halfSize.y,
                            offset.z + halfSize.z);


        boxCol = new BoxCollider(minBounds,maxBounds);
        colCube->setCollider(boxCol);

        _collisionManager->addObject(colCube);
    }













//-------Player collision -----------------------



    glm::vec3 boxColSize2(2,2,2);
    glm::vec3 halfSize2 = boxColSize2 * .5f;

    glm::vec3 offset2 = Player->getLocalPosition();


    glm::vec3 minBounds3(offset2.x - halfSize2.x,
                        offset2.y - halfSize2.y,
                        offset2.z - halfSize2.z);
    glm::vec3 maxBounds3(offset2.x + halfSize2.x,
                        offset2.y + halfSize2.y,
                        offset2.z + halfSize2.z);


    boxCol2 = new BoxCollider(minBounds3,maxBounds3);
    Player->setCollider(boxCol2);
//-------Player collision -----------------------


    _collisionManager->addRbObject(Player);



  //  boxCol->collide(sphereCol);

  //  sphereCol->collide(sphereCol);
    //sphereCol->collide(boxCol);

    XmlReader * xmlReader = new XmlReader();
    std::vector<GameObject * > xmlObjects;

    for (auto i = xmlReader->_objectPositions.begin(); i != xmlReader->_objectPositions.end(); ++i )
    {
            GameObject * obj = new GameObject ("CUPE", *i);
            obj->setMesh(CUPE);
            obj->setMaterial(textureMaterial2);
            cout << "loop" << endl;
          //  _world->add(obj);
            xmlObjects.push_back(obj);
    }

    for(int i = 0; i < xmlObjects.size(); ++i){
        GameObject * temp = xmlObjects[i];
        temp->scale(xmlReader->_colliderSize[i]);
    }

}

void MGEDemo::CreateLights(){


}
bool won = false;
void MGEDemo::_render() {
    //Collider * dummy = Player->getCollider();
    if(Player->getLocalPosition().x > 4.5f) won = true;
    if(won) {
        string winText =  " YOU WIN YAAY !";
        _hud->setWinTextInfo(winText);
    }

    AbstractGame::_render();
    _updateHud();
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::C)) system("cls");
   // std::cout<<Player->getLocalPosition()<<std::endl;

   // _world->renderDebugInfo();
}

void MGEDemo::_updateHud() {
    string debugInfo = "";
    debugInfo += string ("FPS:") + std::to_string(FPS::getFPS())+"\n";

    _hud->setDebugInfo(debugInfo);
    _hud->draw();
}


MGEDemo::~MGEDemo()
{
	//dtor
}
