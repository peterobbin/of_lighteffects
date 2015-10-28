//
//  particleSystem.hpp
//  shaderstest
//
//  Created by peterobbin on 10/28/15.
//
//


#pragma once
#include "ofMain.h"
#include "Particle.h"


class ParticleSystem{
public:
    ParticleSystem(ofVec2f _pos);
    void update(ofVec2f _force);
    void draw();
    
    
    vector<Particle> particleList;
    vector<Particle> sparkList;
    ofVec2f pos;
    
    int pushing = 1;
};