#include "ofApp.h"

void ofApp::setup() {
    float worldSize = 6000.0f;
    int ship_count = 4000;
    do_game.setup(worldSize, ship_count);
    oo_game.setup(worldSize, ship_count);
    game = &do_game;
    t = ofGetElapsedTimef();
}

void ofApp::update() {
    dt = ofGetElapsedTimef() - t;
    t = ofGetElapsedTimef();
    game->tick(dt);
    float tick_t = ofGetElapsedTimef();
    frame++;
    if(frame % 60 == 0) {
        cout << "dt: " << dt << ", fps: " << 1.0f / dt << ", tick: " << tick_t - t << endl;
    }
}

void ofApp::draw() {
    game->render();
}

void ofApp::keyPressed(int key) {
    if(key == OF_KEY_LEFT) {
        game->setCameraMovement(ofVec2f(-1.0f, 0));
    }
    else if(key == OF_KEY_RIGHT) {
        game->setCameraMovement(ofVec2f(1.0f, 0));
    }
    else if(key == OF_KEY_UP) {
        game->setCameraMovement(ofVec2f(0, -1.0f));
    }
    else if(key == OF_KEY_DOWN) {
        game->setCameraMovement(ofVec2f(0, 1.0f));
    }
}

void ofApp::keyReleased(int key) {
    if(key == OF_KEY_TAB) {
        if(game == &oo_game) {
            cout << "Switching to data oriented game..." << endl;
            game = &do_game;
        } else {
            cout << "Switching to object oriented game..." << endl;
            game = &oo_game;
        }
    }
    
    if(key == OF_KEY_LEFT) {
        game->setCameraMovement(ofVec2f(0, 0));
    }
    else if(key == OF_KEY_RIGHT) {
        game->setCameraMovement(ofVec2f(0, 0));
    }
    else if(key == OF_KEY_UP) {
        game->setCameraMovement(ofVec2f(0, 0));
    }
    else if(key == OF_KEY_DOWN) {
        game->setCameraMovement(ofVec2f(0, 0));
    }
}

void ofApp::mouseMoved(int x, int y ) {

}

void ofApp::mouseDragged(int x, int y, int button) {

}

void ofApp::mousePressed(int x, int y, int button) {

}

void ofApp::mouseReleased(int x, int y, int button) {

}

void ofApp::windowResized(int w, int h) {

}

void ofApp::gotMessage(ofMessage msg) {

}

void ofApp::dragEvent(ofDragInfo dragInfo) {

}
