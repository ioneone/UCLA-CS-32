//
//  GasCanGoodie.cpp
//  ZombieDash
//
//  Created by Junhong Wang on 2/23/19.
//  Copyright © 2019 David Smallberg. All rights reserved.
//

#include "GasCanGoodie.h"
#include "GameConstants.h"
#include "Penelope.h"
#include "StudentWorld.h"

GasCanGoodie::GasCanGoodie(StudentWorld *world, int levelX, int levelY)
: Goodie(world, IID_GAS_CAN_GOODIE, levelX, levelY) {
    
}

void GasCanGoodie::doSomething() {
    if (!isAlive()) return;
    
    getWorld()->handleGasCanGoodie(*this);
}

GasCanGoodie::~GasCanGoodie() {
    
}
