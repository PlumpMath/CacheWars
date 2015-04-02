#include "GameObject.h"
#include <ofApp.h>

GameObject::GameObject(string name) : name(name) {
    
}

GameObject::~GameObject() {
    //cout << "Deleted " << name << "." << endl;
}

void GameObject::tick(float dt) {
    if(behaviour) {
        behaviour->tick(this, dt);
    }
}

void GameObject::render(const ofRectangle& cameraRect) {
    if(renderer) {
        renderer->render(this, cameraRect);
    }
}

void ShipRenderer::render(const GameObject* g, const ofRectangle& cameraRect) {
    if(cameraRect.inside(g->position)) {
        ofPushMatrix();
        ofTranslate(g->position - cameraRect.position);
        ofRotate(ofRadToDeg(direction));
        ofSetColor(color);
        ofTriangle(-15, -10, 20, 0, -15, 10);
        ofPopMatrix();
    }
}

void GoInCircles::moveForward(GameObject* g, float dt) {
    g->position.x += cosf(direction) * speed * dt;
    g->position.y += sinf(direction) * speed * dt;
}

void GoInCircles::tick(GameObject* g, float dt) {
    assert(renderer);
    speed += 10.0f * dt;
    direction += sinf(ofGetElapsedTimef()) * speed * 0.01f * dt;
    moveForward(g, dt);
    renderer->direction = direction;

    assert(*worldSize);
    if(g->position.x < 0) g->position.x = *worldSize;
    if(g->position.x > *worldSize) g->position.x = 0;
    if(g->position.y < 0) g->position.y = *worldSize;
    if(g->position.y > *worldSize) g->position.y = 0;
}

void GoInCircles::onCollision(GameObject* g, GameObject *other) {
    renderer->color *= 1.2;
    speed = ofRandom(10, 20);
    ofPoint diff = other->position - g->position;
    direction = atan2f(diff.x, diff.y);
    moveForward(g, 1.0);
}
