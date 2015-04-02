#pragma once

#include <ofUtils.h>
#include <vector>
#include "GameObject.h"

using namespace std;

class ObjectOrientedGame {
    vector< ofPtr<GameObject> > gameObjects;
    vector<GameObject*> gameObjects2;
    
public:
    
    float worldSize = 6000;
    
    float cameraPanSpeed = 500;
    ofRectangle cameraRect;
    ofVec2f cameraMovement;
    
    void setup();
    void tick(float dt);
    void render();
    
    ofPtr<GameObject> makeGameObject(string name);
    ofPoint randomCoordinate();
    
    void moveCamera(float x, float y);
};