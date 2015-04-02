#ifndef OBJECT_ORIENTED
#define OBJECT_ORIENTED

#include <ofUtils.h>
#include <vector>
#include "GameObject.h"
#include "IGame.h"

using namespace std;

class ObjectOrientedGame : public IGame {
    vector<GameObject*> gameObjects;
    
    void makeGameObject(string name);
    ofPoint randomCoordinate();
    
    float cameraPanSpeed = 1500;
    ofRectangle cameraRect;
    ofVec2f cameraMovement;
    
    float worldSize;
    
public:
    
    void setup(float worldSize, int gameObjectCount);
    void tick(float dt);
    void render();
    void setCameraMovement(ofVec2f mov) { cameraMovement = mov; }
    
};

#endif