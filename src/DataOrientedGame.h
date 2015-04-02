#ifndef DATA_ORIENTED
#define DATA_ORIENTED

#include <ofUtils.h>
#include <ofGraphics.h>
#include <vector>
#include "GameData.h"
#include "IGame.h"

class DataOrientedGame : public IGame {
    float worldSize;
    vector<ShipData> shipDatas;
    vector<EngineData> engineDatas;
    vector<RenderData> renderDatas;
    ofRectangle cameraRect;
    void make_ship(string name);
    float cameraPanSpeed = 1500;
    ofVec2f cameraMovement;
    
    void ship_collided(int collider, int other);
    
public:
    
    void setup(float worldSize, int gameObjectCount);
    void tick(float dt);
    void render();
    void setCameraMovement(ofVec2f mov) { cameraMovement = mov; }
    
};

#endif