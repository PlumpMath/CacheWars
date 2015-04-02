#include "DataOrientedGame.h"
#include <ofGraphics.h>
#include <ofApp.h>

ofColor randomColor() {
    return ofColor(ofRandom(100, 255), ofRandom(100, 255), ofRandom(100, 255));
}

ofPoint randomCoordinate(float worldSize) {
    return ofPoint(ofRandom(worldSize), ofRandom(worldSize));
}

void DataOrientedGame::make_ship(string name) {
    ShipData shipData = { randomCoordinate(worldSize) };
    shipDatas.push_back(shipData);
    
    EngineData engineData = {
        .direction = ofRandom(TWO_PI),
        .speed = ofRandom(30, 50)
    };
    engineDatas.push_back(engineData);
    
    RenderData renderData = {
        .color = randomColor(),
        .name = name
    };
    renderDatas.push_back(renderData);
}

void DataOrientedGame::setup(float worldSize, int gameObjectCount) {
    this->worldSize = worldSize;
    cameraRect = ofRectangle(0, 0, ofGetWidth(), ofGetHeight());
    
    for(int i = 0; i < gameObjectCount; i++) {
        stringstream s;
        s << "gd" << i;
        make_ship(s.str());
    }
}

void move_ship(ShipData& shipData, float direction, float speed_times_dt) {
    shipData.position.x += cosf(direction) * speed_times_dt;
    shipData.position.y += sinf(direction) * speed_times_dt;
}

void tick_ship(float dt, ShipData& shipData, EngineData& engineData, float worldSize) {

    engineData.speed += 10.0f * dt;
    float speed = engineData.speed;
    engineData.direction += sinf(ofGetElapsedTimef()) * speed * 0.01f * dt;
    move_ship(shipData, engineData.direction, speed * dt);
    
    if(shipData.position.x < 0) shipData.position.x = worldSize;
    if(shipData.position.x > worldSize) shipData.position.x = 0;
    if(shipData.position.y < 0) shipData.position.y = worldSize;
    if(shipData.position.y > worldSize) shipData.position.y = 0;
}

void DataOrientedGame::ship_collided(int ship, int other) {
    renderDatas[ship].color *= 1.2;
    engineDatas[ship].speed = ofRandom(10, 20);
    ofPoint diff = shipDatas[other].position - shipDatas[ship].position;
    engineDatas[ship].direction = atan2f(diff.x, diff.y);
    move_ship(shipDatas[ship], engineDatas[ship].direction, 1.0f);
}

void DataOrientedGame::tick(float dt) {
    
    cameraRect.translate(cameraMovement.x * cameraPanSpeed * dt,
                         cameraMovement.y * cameraPanSpeed * dt);

    for (int i = 0; i < shipDatas.size(); ++i) {
        tick_ship(dt, shipDatas[i], engineDatas[i], worldSize);
    }
    
    const int size = shipDatas.size();
    for (int i = 0; i < size - 1; ++i) {
        for (int j = i + 1; j < size; ++j) {
            ofPoint p1 = shipDatas[i].position;
            ofPoint p2 = shipDatas[j].position;
            float dx = p2.x - p1.x;
            float dy = p2.y - p1.y;
            float distanceSquared = dx * dx + dy * dy;
            if(distanceSquared < 300) {
                ship_collided(i, j);
                ship_collided(j, i);
            }
        }
    }
}

void render_ship(const ofRectangle& cameraRect,
                 const ofPoint& position,
                 ofColor& color,
                 float direction)
{
    if(cameraRect.inside(position)) {
        ofPushMatrix();
        ofTranslate(position - cameraRect.position);
        ofRotate(ofRadToDeg(direction));
        ofSetColor(color);
        ofTriangle(-15, -10, 20, 0, -15, 10);
        ofPopMatrix();
    }
}

void DataOrientedGame::render() {
    ofBackground(10);
    ofFill();
    ofSetColor(50);
    ofRect(ofRectangle(-cameraRect.x, -cameraRect.y, worldSize, worldSize));
    
    for(int i = 0; i < shipDatas.size(); ++i) {
        render_ship(cameraRect,
                    shipDatas[i].position,
                    renderDatas[i].color,
                    engineDatas[i].direction);
    }
}
