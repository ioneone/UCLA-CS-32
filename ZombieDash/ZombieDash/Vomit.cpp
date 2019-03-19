//
//  Vomit.cpp
//  ZombieDash
//
//  Created by Junhong Wang on 2/17/19.
//  Copyright © 2019 David Smallberg. All rights reserved.
//

#include "Vomit.h"
#include "GameConstants.h"
#include "ActorConstants.h"
#include "StudentWorld.h"
#include "Penelope.h"

Vomit::Vomit(StudentWorld *world, double startX, double startY, int direction)
: InflammableEnvironment(world, IID_VOMIT, startX, startY, START_VOMIT_LIVES, direction, VOMIT_DEPTH) {
}

void Vomit::doSomething() {
    if (!isAlive()) return;
    
    decrementLife();
    
    if (!isAlive()) return;
    
    getWorld()->handleVomit(*this);
        
}

Vomit::~Vomit() {
    
}
