//
//  InflammableEnvironment.cpp
//  ZombieDash
//
//  Created by Junhong Wang on 2/24/19.
//  Copyright © 2019 David Smallberg. All rights reserved.
//

#include "InflammableEnvironment.h"

InflammableEnvironment::InflammableEnvironment(StudentWorld *world, int imageID, double startX, double startY, int startLives, int startDirection, int depth)
: MortalEnvironment(world, imageID, startX, startY, startDirection, depth) {
    m_life = startLives;
}

InflammableEnvironment::~InflammableEnvironment() {
    
}

bool InflammableEnvironment::isAlive() {
    return m_life > 0;
}

void InflammableEnvironment::die() {
    m_life = 0;
}

void InflammableEnvironment::decrementLife() {
    if (m_life == 0) return;
    m_life--;
}
