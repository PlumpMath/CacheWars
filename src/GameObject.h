#pragma once

#include <ofGraphics.h>
#include <ofUtils.h>

// Component interfaces

class IBehaviour {
public:
    virtual void tick(float dt) = 0;
};

class IRenderer {
public:
    virtual void render(const ofRectangle& cameraRect) = 0;
};


// The one game object (should be a sealed class)

class GameObject {
public:
    string name;
    ofPtr<IBehaviour> behaviour;
    ofPtr<IRenderer> renderer;
    
    GameObject(string name);
    ~GameObject();
    
    void tick(float dt);
    void render(const ofRectangle& cameraRect);
};


// Component implementations

class ShipRenderer : public IRenderer {
public:
    float direction; // slave value
    ofPoint position;
    ofColor color;
    void render(const ofRectangle& cameraRect) override;
};

class GoInCircles : public IBehaviour {
public:
    float speed = 50.0f;
    float direction = 0.0f;
    float *worldSize = NULL;
    ShipRenderer *renderer;
    void tick(float dt) override;
};


