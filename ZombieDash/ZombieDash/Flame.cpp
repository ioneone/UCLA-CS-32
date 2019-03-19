//
//  Flame.cpp
//  ZombieDash
//
//  Created by Junhong Wang on 2/17/19.
//  Copyright © 2019 David Smallberg. All rights reserved.
//

#include "Flame.h"
#include "GameConstants.h"
#include "ActorConstants.h"
#include "Penelope.h"
#include "StudentWorld.h"

Flame::Flame(StudentWorld *world, double startX, double startY, int direction)
: InflammableEnvironment(world, IID_FLAME, startX, startY, START_FLAME_LIVES, direction, FLAME_DEPTH) {
    
}

void Flame::doSomething() {
    if (!isAlive()) return;
    
    decrementLife();
    
    if (!isAlive()) return;
    
    getWorld()->handleFlame(*this);
    
}

Flame::~Flame() {
    
}

