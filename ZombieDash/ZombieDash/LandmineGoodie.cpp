//
//  LandmineGoodie.cpp
//  ZombieDash
//
//  Created by Junhong Wang on 2/23/19.
//  Copyright © 2019 David Smallberg. All rights reserved.
//

#include "LandmineGoodie.h"
#include "GameConstants.h"
#include "Penelope.h"
#include "StudentWorld.h"

LandmineGoodie::LandmineGoodie(StudentWorld *world, int levelX, int levelY)
: Goodie(world, IID_LANDMINE_GOODIE, levelX, levelY) {
    
}

void LandmineGoodie::doSomething() {
    if (!isAlive()) return;
    
    getWorld()->handleLandmineGoodie(*this);
}

LandmineGoodie::~LandmineGoodie() {
    
}
