#include "ObjectOrientedGame.h"
#include "GameObject.h"
#include <ofGraphics.h>
#include <ofApp.h>

ofColor randomColor() {
    return ofColor(ofRandom(100, 255), ofRandom(100, 255), ofRandom(100, 255));
}

ofPoint ObjectOrientedGame::randomCoordinate() {
    return ofPoint(ofRandom(worldSize), ofRandom(worldSize));
}

void ObjectOrientedGame::setup(float worldSize, int gameObjectCount) {
    this->worldSize = worldSize;
    cameraRect = ofRectangle(0, 0, ofGetWidth(), ofGetHeight());
    
    for(int i = 0; i < gameObjectCount; i++) {
        stringstream s;
        s << "go" << i;
        makeGameObject(s.str());
    }
}

void ObjectOrientedGame::makeGameObject(string name) {
    GameObject *g = new GameObject(name);
    
    g->position = randomCoordinate();
    
    ShipRenderer *r = new ShipRenderer;
    r->color = randomColor();
    g->renderer = r;
    
    GoInCircles *c = new GoInCircles;
    c->renderer = r;
    c->speed = ofRandom(30, 50);
    c->direction = ofRandom(TWO_PI);
    c->worldSize = &worldSize;
    g->behaviour = c;
    
    gameObjects.push_back(g);
    return g;
}

void ObjectOrientedGame::tick(float dt) {
    cameraRect.translate(cameraMovement.x * cameraPanSpeed * dt,
                         cameraMovement.y * cameraPanSpeed * dt);
    
    for (int i = 0; i < gameObjects.size(); ++i) {
        gameObjects[i]->tick(dt);
    }
    
    for (int i = 0; i < gameObjects.size() - 1; ++i) {
        for (int j = i + 1; j < gameObjects.size(); ++j) {
            GameObject *a = gameObjects[i];
            GameObject *b = gameObjects[j];
            if(a->position.distanceSquared(b->position) < 300) {
                a->behaviour->onCollision(a, b);
                b->behaviour->onCollision(b, a);
            }
        }
    }
}

void ObjectOrientedGame::render() {
    ofBackground(10);
    ofFill();
    ofSetColor(50);
    ofRect(ofRectangle(-cameraRect.x, -cameraRect.y, worldSize, worldSize));
    
    for (int i = 0; i < gameObjects.size(); ++i) {
        gameObjects[i]->render(cameraRect);
    }
}
