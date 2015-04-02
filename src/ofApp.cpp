#include "ofApp.h"

void ofApp::setup() {
    game.setup();
    t = ofGetElapsedTimef();
}

void ofApp::update() {
    dt = ofGetElapsedTimef() - t;
    t = ofGetElapsedTimef();
    game.tick(dt);
}

void ofApp::draw() {
    game.render();
}

void ofApp::keyPressed(int key) {
    if(key == OF_KEY_LEFT) {
        game.cameraMovement.x = -1.0f;
    }
    else if(key == OF_KEY_RIGHT) {
        game.cameraMovement.x = 1.0f;
    }
    else if(key == OF_KEY_UP) {
        game.cameraMovement.y = -1.0f;
    }
    else if(key == OF_KEY_DOWN) {
        game.cameraMovement.y = 1.0f;
    }
}

void ofApp::keyReleased(int key) {
    if(key == OF_KEY_LEFT) {
        game.cameraMovement.x = 0.0f;
    }
    else if(key == OF_KEY_RIGHT) {
        game.cameraMovement.x = 0.0f;
    }
    else if(key == OF_KEY_UP) {
        game.cameraMovement.y = 0.0f;
    }
    else if(key == OF_KEY_DOWN) {
        game.cameraMovement.y = 0.0f;
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
