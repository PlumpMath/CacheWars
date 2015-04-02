#pragma once

#include <ofUtils.h>
#include <vector>
#include "GameObject.h"

using namespace std;

class ObjectOrientedGame {
    vector< ofPtr<GameObject> > gameObjects;
    vector<GameObject*> gameObjects2;
    
public:
    
    const int gameObjectCount = 500;
    float worldSize = 4000;
    
    float cameraPanSpeed = 1500;
    ofRectangle cameraRect;
    ofVec2f cameraMovement;
    
    void setup();
    void tick(float dt);
    void render();
    
    ofPtr<GameObject> makeGameObject(string name);
    ofPoint randomCoordinate();
    
    void moveCamera(float x, float y);
};
