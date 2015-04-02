#pragma once

#include <ofGraphics.h>
#include <ofUtils.h>

// Component interfaces

class GameObject;

class IBehaviour {
public:
    virtual void tick(GameObject* g, float dt) = 0;
    virtual void onCollision(GameObject* g, GameObject *other) = 0;
};

class IRenderer {
public:
    virtual void render(const GameObject* g, const ofRectangle& cameraRect) = 0;
};


// The one game object (should be a sealed class)

class GameObject {
public:
    string name;
    IBehaviour *behaviour;
    IRenderer *renderer;
    ofVec2f position;
    
    GameObject(string name);
    ~GameObject();
    
    void tick(float dt);
    void render(const ofRectangle& cameraRect);
};


// Component implementations

class ShipRenderer : public IRenderer {
public:
    float direction; // slave value
    ofColor color;
    void render(const GameObject* g, const ofRectangle& cameraRect) override;
};

class GoInCircles : public IBehaviour {
public:
    float speed = 50.0f;
    float direction = 0.0f;
    float *worldSize = NULL;
    ShipRenderer *renderer;
    
    void tick(GameObject* g, float dt) override;
    void onCollision(GameObject* g, GameObject *other) override;
    void moveForward(GameObject* g, float dt);
};


