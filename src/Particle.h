//
//  Particle.hpp
//  shaderstest
//
//  Created by peterobbin on 10/28/15.
//
//

#pragma once
#include "ofMain.h"

class Particle{
public:
    Particle(ofVec2f _pos);
    
    void resetForces();
    void applyForce(ofVec2f force);
    void update(float multi);
    void draw();
    
    
    ofVec2f pos, vel, acc;
    float lifespan;
    float innermulti;
};

