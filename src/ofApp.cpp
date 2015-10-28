#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){

    
    gravity.set(0.0, 0.02);
    shader.load("test.vert", "test.frag");
    flare.load("flare.vert", "flare.frag");
    stripes.load("flareStripes.vert", "flareStripes.frag");
    timestamp = ofGetElapsedTimef();
    enableEffects = false;
    
}

//--------------------------------------------------------------
void ofApp::update(){
    windowSize = ofVec2f(ofGetWidth(), ofGetHeight());
    circlePos = ofVec2f(sin(ofGetElapsedTimef()) * 50 + ofGetWidth()/2, cos(ofGetElapsedTimef()) * 50 + ofGetHeight()/2);
    
    for (int i = 0; i < systems.size(); i++) {
        systems[i].update(gravity);
    }
    
    // normalized timer vlue
    timer = ofGetElapsedTimef() - timestamp;
    timer = 1.0 - ofClamp(timer, 0.0, 3.0) / 3.0;
}

//--------------------------------------------------------------
void ofApp::draw(){
    ofSetColor(255);
    ofBackground(0);
    // pinpoint mouse location
    ofCircle(mouseX, mouseY, 1.0);
    
    if (enableEffects){
        flareStripes();
        bokeh();
        flareBar();
    }
 
    
}
//-------------------------------------------
void ofApp::flareStripes(){
    stripes.begin();
    stripes.setUniform2f("u_resolution", ofGetWidth(), ofGetHeight());
    stripes.setUniform1f("u_time", ofGetElapsedTimef());
    stripes.setUniform2f("u_mouse", systemLocation.x ,systemLocation.y);
    stripes.setUniform1f("u_timer", timer);
    ofRect(0, 0, ofGetWidth(), ofGetHeight());
    stripes.end();

}

//--------------------------------------------
void ofApp::bokeh(){

    for (int i = 0; i < systems.size(); i++) {
        systems[i].draw();
        //  only do certain amount of particles
        for (int j = 0; j < systems[i].particleList.size(); j += 40) {
            
            //  checking life span and normalize it
            float lifespan = ofClamp(systems[i].particleList[j].lifespan/255, 0.0, 1.0);
            
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

//--------------------------------------------
void ofApp::flareBar(){
    
    for (int i = 0; i < systems.size(); i++) {
        systems[i].draw();
        
        //  only do certain amount of particles
        for (int j = 0; j < systems[i].particleList.size(); j += 200) {
            
            //  checking life span and normalize it
            float lifespan = ofClamp(systems[i].particleList[j].lifespan/255, 0.0, 1.0);
            flare.begin();
            flare.setUniform2f("u_resolution", ofGetWidth(), ofGetHeight());
            flare.setUniform1f("u_time", ofGetElapsedTimef());
            flare.setUniform2f("u_mouse", systems[i].particleList[j].pos.x , systems[i].particleList[j].pos.y);
            flare.setUniform1f("u_particle_lifespan", lifespan);
            flare.setUniform1f("u_aspectRatio", windowSize.x/windowSize.y);
            ofRect(0, 0, ofGetWidth(), ofGetHeight());
            flare.end();
            
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
    systemLocation = ofVec2f(x, y);
    systems.push_back(system);
    timestamp = ofGetElapsedTimef();
    enableEffects = true;
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
