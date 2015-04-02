#include "GameObject.h"
#include <ofApp.h>

GameObject::GameObject(string name) : name(name) {
    
}

GameObject::~GameObject() {
    //cout << "Deleted " << name << "." << endl;
}

void GameObject::tick(float dt) {
    if(behaviour) {
        behaviour->tick(dt);
    }
}

void GameObject::render(const ofRectangle& cameraRect) {
    if(renderer) {
        renderer->render(cameraRect);
    }
}

void ShipRenderer::render(const ofRectangle& cameraRect) {
    if(cameraRect.inside(position)) {
        ofPushMatrix();
        ofTranslate(position - cameraRect.position);
        ofRotate(ofRadToDeg(direction));
        ofSetColor(color);
        ofTriangle(-15, -10, 20, 0, -15, 10);
        ofPopMatrix();
    }
}

void GoInCircles::tick(float dt) {
    assert(renderer);
    direction += sinf(ofGetElapsedTimef()) * speed * 0.01f * dt;
    renderer->position.x += cosf(direction) * speed * dt;
    renderer->position.y += sinf(direction) * speed * dt;
    renderer->direction = direction;

    assert(*worldSize);
    if(renderer->position.x < 0) renderer->position.x = *worldSize;
    if(renderer->position.x > *worldSize) renderer->position.x = 0;
    if(renderer->position.y < 0) renderer->position.y = *worldSize;
    if(renderer->position.y > *worldSize) renderer->position.y = 0;
}
