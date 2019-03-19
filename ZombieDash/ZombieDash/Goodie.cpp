//
//  Goodie.cpp
//  ZombieDash
//
//  Created by Junhong Wang on 2/23/19.
//  Copyright © 2019 David Smallberg. All rights reserved.
//

#include "Goodie.h"
#include "ActorConstants.h"


Goodie::Goodie(StudentWorld *world, int iid, int levelX, int levelY)
: FlammableEnvironment(world, iid, SPRITE_WIDTH * levelX, SPRITE_HEIGHT * levelY, GOODIE_START_DIRECTION, GOODIE_DEPTH) {
    
}

Goodie::Goodie(StudentWorld *world, int iid, double startX, double startY)
: FlammableEnvironment(world, iid, startX, startY, GOODIE_START_DIRECTION, GOODIE_DEPTH) {
    
}

Goodie::~Goodie() {
    
}

bool Goodie::isGoodie() {
    return true;
}

