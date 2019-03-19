//
//  Exit.cpp
//  ZombieDash
//
//  Created by Junhong Wang on 2/17/19.
//  Copyright © 2019 David Smallberg. All rights reserved.
//

#include "Exit.h"
#include "GameConstants.h"
#include "ActorConstants.h"
#include "StudentWorld.h"
#include "Penelope.h"

Exit::Exit(StudentWorld *world, int levelX, int levelY)
: ImmortalEnvironment(world, IID_EXIT, SPRITE_WIDTH * levelX , SPRITE_HEIGHT * levelY, EXIT_START_DIRECTION, EXIT_DEPTH){
    
}

void Exit::doSomething() {
    
    getWorld()->handleExit(*this);
    
}

bool Exit::isOverlappable() {
    return true;
}

Exit::~Exit() {
    
}


bool Exit::isFlameBlockable() {
    return true;
}
