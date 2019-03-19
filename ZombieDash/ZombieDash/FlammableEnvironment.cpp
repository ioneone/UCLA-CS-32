//
//  FlammableEnvironment.cpp
//  ZombieDash
//
//  Created by Junhong Wang on 2/24/19.
//  Copyright © 2019 David Smallberg. All rights reserved.
//

#include "FlammableEnvironment.h"

FlammableEnvironment::FlammableEnvironment(StudentWorld *world, int imageID, double startX, double startY, int startDirection, int depth)
: MortalEnvironment(world, imageID, startX, startY, startDirection, depth) {
    m_isAlive = true;
}
FlammableEnvironment::~FlammableEnvironment() {
    
}

bool FlammableEnvironment::isFlammable() {
    return true;
}

void FlammableEnvironment::die() {
    if (!m_isAlive) return;
    m_isAlive = false;
}

bool FlammableEnvironment::isAlive() {
    return m_isAlive;
}
