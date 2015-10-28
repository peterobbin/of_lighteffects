#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){

    shader.load("test.vert", "test.frag");

}

//--------------------------------------------------------------
void ofApp::update(){
    windowSize = ofVec2f(ofGetWidth(), ofGetHeight());
//    float b = ofGetHeight();
//    float c = a / b;
    cout<<windowSize.x/windowSize.y<<endl;
    circlePos = ofVec2f(sin(ofGetElapsedTimef()) * 50 + ofGetWidth()/2, cos(ofGetElapsedTimef()) * 50 + ofGetHeight()/2);
    
}

//--------------------------------------------------------------
void ofApp::draw(){
    ofSetColor(255);
    ofCircle(circlePos, 100);
    for (int i = 1 ; i <= 10 ; i ++){
    shader.begin();
   
    shader.setUniform2f("u_resolution", ofGetWidth(), ofGetHeight());
    shader.setUniform1f("u_time", ofGetElapsedTimef());
    shader.setUniform2f("u_mouse", circlePos.x * i, ofGetHeight() - circlePos.y * i);
    shader.setUniform1f("u_aspectRatio", windowSize.x/windowSize.y);
    
    ofRect(0, 0, ofGetWidth(), ofGetHeight());
    shader.end();
    }
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
