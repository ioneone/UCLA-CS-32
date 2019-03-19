//
//  ImmortalActor.cpp
//  ZombieDash
//
//  Created by Junhong Wang on 2/24/19.
//  Copyright © 2019 David Smallberg. All rights reserved.
//

#include "ImmortalEnvironment.h"

ImmortalEnvironment::ImmortalEnvironment(StudentWorld *world, int imageID, double startX, double startY, int startDirection, int depth)
: Actor(world, imageID, startX, startY, startDirection, depth) {
    
}

void ImmortalEnvironment::die() {
    
}

bool ImmortalEnvironment::isAlive() {
    return true;
}

ImmortalEnvironment::~ImmortalEnvironment() {
    
}

bool ImmortalEnvironment::isImmortal() {
    return true;
}
