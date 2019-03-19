//
//  Wall.cpp
//  ZombieDash
//
//  Created by Junhong Wang on 2/17/19.
//  Copyright © 2019 David Smallberg. All rights reserved.
//

#include "Wall.h"
#include "GameConstants.h"
#include "ActorConstants.h"

Wall::Wall(StudentWorld *world, int levelX, int levelY)
: ImmortalEnvironment(world, IID_WALL, SPRITE_WIDTH * levelX, SPRITE_HEIGHT * levelY, WALL_START_DIRECTION, WALL_DEPTH) {
    
}

void Wall::doSomething() {
    
}

Wall::~Wall() {
    
}

bool Wall::isFlameBlockable() {
    return true;
}

