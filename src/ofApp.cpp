#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){

    
    gravity.set(0.0, 0.02);
    shader.load("test.vert", "test.frag");

}

//--------------------------------------------------------------
void ofApp::update(){
    windowSize = ofVec2f(ofGetWidth(), ofGetHeight());
    circlePos = ofVec2f(sin(ofGetElapsedTimef()) * 50 + ofGetWidth()/2, cos(ofGetElapsedTimef()) * 50 + ofGetHeight()/2);

    
    for (int i = 0; i < systems.size(); i++) {
        systems[i].update(gravity);
    }
}

//--------------------------------------------------------------
void ofApp::draw(){
    ofSetColor(255);
    ofBackground(0);
    ofCircle(circlePos, 10);
    ofCircle(mouseX, mouseY, 1.0);
    
    for (int i = 0; i < systems.size(); i++) {
        systems[i].draw();
        
        //  only do certain amount of particles
        for (int j = 0; j < systems[i].particleList.size(); j += 30) {
            
            
            //  checking life span and normalize it
            float lifespan = ofClamp(systems[i].particleList[j].lifespan/255, 0.0, 1.0);
            float lifespan_invert = 1.0 - lifespan;
            
    
            shader.begin();
            shader.setUniform2f("u_resolution", ofGetWidth(), ofGetHeight());
            shader.setUniform1f("u_time", ofGetElapsedTimef());
            shader.setUniform2f("u_mouse", systems[i].particleList[j].pos.x , systems[i].particleList[j].pos.y);
            shader.setUniform1f("u_particle_lifespan", lifespan);
            
            shader.setUniform1f("u_aspectRatio", windowSize.x/windowSize.y);
            ofRect(0, 0, ofGetWidth(), ofGetHeight());
            shader.end();

        }
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
    ParticleSystem system(ofVec2f(x, y));
    systems.push_back(system);
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
