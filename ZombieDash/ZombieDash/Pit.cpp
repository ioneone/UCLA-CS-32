//
//  Pit.cpp
//  ZombieDash
//
//  Created by Junhong Wang on 2/17/19.
//  Copyright © 2019 David Smallberg. All rights reserved.
//

#include "Pit.h"
#include "GameConstants.h"
#include "ActorConstants.h"
#include "StudentWorld.h"
#include "Penelope.h"

Pit::Pit(StudentWorld *world, double startX, double startY)
: ImmortalEnvironment(world, IID_PIT, startX, startY, PIT_START_DIRECTION, PIT_DEPTH) {
    
}

Pit::Pit(StudentWorld *world, int levelX, int levelY)
: ImmortalEnvironment(world, IID_PIT, SPRITE_WIDTH * levelX, SPRITE_HEIGHT * levelY, PIT_START_DIRECTION, PIT_DEPTH) {
    
}

void Pit::doSomething() {
    
    getWorld()->handlePit(*this);
}

bool Pit::isOverlappable() {
    return true;
}

Pit::~Pit() {
    
}


