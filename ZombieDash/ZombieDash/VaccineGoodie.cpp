//
//  VaccineGoodie.cpp
//  ZombieDash
//
//  Created by Junhong Wang on 2/23/19.
//  Copyright © 2019 David Smallberg. All rights reserved.
//

#include "VaccineGoodie.h"
#include "GameConstants.h"
#include "StudentWorld.h"
#include "Penelope.h"
#include "ActorConstants.h"

VaccineGoodie::VaccineGoodie(StudentWorld *world, int levelX, int levelY)
: Goodie(world, IID_VACCINE_GOODIE, levelX, levelY) {
    
}

VaccineGoodie::VaccineGoodie(StudentWorld *world, double startX, double startY)
: Goodie(world, IID_VACCINE_GOODIE, startX, startY) {
    
}

void VaccineGoodie::doSomething() {
    if (!isAlive()) return;
    
    getWorld()->handleVaccineGoodie(*this);
}

VaccineGoodie::~VaccineGoodie() {
    
}
