#ifndef CacheWars_IGame_h
#define CacheWars_IGame_h

#include <ofUtils.h>

class IGame {
public:
    virtual void setup(float worldSize, int gameObjectCount) = 0;
    virtual void tick(float dt) = 0;
    virtual void render() = 0;
    virtual void setCameraMovement(ofVec2f mov) = 0;
};

#endif
