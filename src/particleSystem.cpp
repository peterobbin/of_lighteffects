//
//  particleSystem.cpp
//  shaderstest
//
//  Created by peterobbin on 10/28/15.
//
//

#include "particleSystem.hpp"



//--------------------------------------------------------------
ParticleSystem::ParticleSystem(ofVec2f _pos){
    ofBackground(0);
    pos.set(_pos);
    
    
}

//--------------------------------------------------------------
void ParticleSystem::update(ofVec2f _force){
    

    for (int i = 0; i < 10; i++) {
        Particle particle(pos);
        if (pushing == 1){
            particleList.push_back(particle);
        }
        if (pushing == 0){
            //particleList.erase(particleList.begin());
        }
        
    }
    
    
    for (int i = 0; i < 1; i++) {
        Particle particle(pos);
        if (pushing == 1){
            sparkList.push_back(particle);
        }
        
        if (pushing == 0){
            sparkList.clear();
        }
    }
    
    
    
    
    for (int i = 0; i < particleList.size(); i++) {
        
        ofVec2f diff = ofVec2f(abs(particleList[i].pos.x - pos.x),abs(particleList[i].pos.y - pos.y));
        particleList[i].resetForces();
        particleList[i].applyForce(_force);
        particleList[i].update(ofMap(diff.length(), 0, 200, 4, 1));
        
        if (diff.length() >= ofRandom(200, 400)) {
            pushing = 0;
            
            if (particleList.size() > 0) {
                particleList.erase(particleList.begin()+i);
                
            }
            
        }
        
    }
    
    
    
    
}

//--------------------------------------------------------------
void ParticleSystem::draw(){
    
    for (int i = 0; i < particleList.size(); i++) {
        particleList[i].draw();
    }
}

//--------------------------------------------------------------