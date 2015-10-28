#pragma once

#include "ofMain.h"
#include "particleSystem.hpp"

class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();

		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
    
    void bokeh();
    void flareBar();
    void flareStripes();
    void blur(float bluramt);
    
    
    
    
    ofVec2f windowSize;
    ofVec2f circlePos;
    ofShader shader;
    ofShader flare;
    ofShader stripes;
    
    
    vector<ParticleSystem> systems;
    ofVec2f gravity;
    ofVec2f systemLocation;
    
    float timestamp;
    float timer;
    bool enableEffects;
    
    float bluramt;
    
    
    ofImage image;
    ofFbo fboBlurOnePass;
    ofShader shaderBlurX;
    ofFbo fboBlurTwoPass;
    ofShader shaderBlurY;
    

};
