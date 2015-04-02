#include "ObjectOrientedGame.h"
#include "GameObject.h"
#include <ofGraphics.h>
#include <ofApp.h>

ofColor randomColor() {
    return ofColor(ofRandom(100, 255), ofRandom(100, 255), ofRandom(100, 255));
}

void ObjectOrientedGame::setup() {
    cameraRect = ofRectangle(0, 0, ofGetWidth(), ofGetHeight());
    
    for(int i = 0; i < 5000; i++) {
        stringstream s;
        s << "go" << i;
        makeGameObject(s.str());
    }
}

void ObjectOrientedGame::tick(float dt) {
    cameraRect.translate(cameraMovement.x * cameraPanSpeed * dt,
                         cameraMovement.y * cameraPanSpeed * dt);
    
    for (int i = 0; i < gameObjects.size(); ++i) {
        gameObjects[i]->tick(dt);
    }

    cout << "dt: " << dt << ", fps: " << 1.0f / dt << endl;
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

ofPoint ObjectOrientedGame::randomCoordinate() {
    return ofPoint(ofRandom(worldSize), ofRandom(worldSize));
}

ofPtr<GameObject> ObjectOrientedGame::makeGameObject(string name) {
    ofPtr<GameObject> g(new GameObject(name));
    
    ShipRenderer *r = new ShipRenderer;
    r->position = randomCoordinate();
    r->color = randomColor();
    g->renderer = ofPtr<IRenderer>(r);
    
    GoInCircles *c = new GoInCircles;
    c->renderer = r;
    c->speed = ofRandom(30, 50);
    c->direction = ofRandom(TWO_PI);
    c->worldSize = &worldSize;
    g->behaviour = ofPtr<IBehaviour>(c);
  
    gameObjects.push_back(g);
    return g;
}
