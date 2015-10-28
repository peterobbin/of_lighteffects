//
//  Particle.cpp
//  shaderstest
//
//  Created by peterobbin on 10/28/15.
//


#include "Particle.h"

Particle::Particle(ofVec2f _pos){
    pos.set(_pos);
    vel.x = ofRandom(-2,2);
    vel.y = ofRandom(-2,2);
    lifespan = 255.0;
    
    
}

void Particle::resetForces(){
    acc *= 0;
}

void Particle::applyForce(ofVec2f force){
    acc +=force;
}

void Particle::update(float multi){
    vel += acc;
    pos += vel * multi;
    innermulti = multi;
    
    if (lifespan > 0) {
        lifespan -= 2.0;
    }
}


void Particle::draw(){
    if(lifespan>100){
        ofSetColor(lifespan);
        
    }else if(lifespan<=100){
        ofSetColor(ofRandom(0, 255));
    };
    
    
    
    
    ofCircle(pos,2.0 * ofMap(lifespan, 0, 255, 0, 1));
}








