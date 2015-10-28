#pragma once

#include "ofMain.h"
#include "particleSystem.hpp"
#include "ofxGui.h"

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
    void blooms();
    
    
    
    
    
    ofVec2f windowSize;
    ofVec2f circlePos;
    ofShader shader;
    ofShader flare;
    ofShader stripes;
    ofShader bloom;
    
    ofImage image;
    ofFbo fboBlurOnePass;
    ofShader shaderBlurX;
    ofFbo fboBlurTwoPass;
    ofShader shaderBlurY;
    
    
    vector<ParticleSystem> systems;
    ofVec2f gravity;
    ofVec2f systemLocation;
    
    float timestamp;
    float timer;
    bool enableEffects;
    
    ofParameter<float> bluramt;
    ofParameter<float> bloomsize;
    ofParameter<float> bloombrightness;
    ofParameter<float> flareBarRange;
    ofParameter<float> flareBarThickness;
    ofParameter<float> flareStripeBlur;
    ofParameter<float> flareStripeBrightness;
    ofParameter<float> flareStripeSize;
    ofParameter<int> bokehSides;
    ofParameter<float> bokehSize;
    
    
    ofxPanel gui;
    ofParameter<bool> showBokeh;
    ofParameter<bool> showFlareBar;
    ofParameter<bool> showFlareStripes;
    ofParameter<bool> enableBlooms;
    ofParameter<bool> enableBlur;
    
    
    

};
