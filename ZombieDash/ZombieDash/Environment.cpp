//
//  Environment.cpp
//  ZombieDash
//
//  Created by Junhong Wang on 2/24/19.
//  Copyright © 2019 David Smallberg. All rights reserved.
//

#include "Environment.h"

Environment::Environment(StudentWorld *world, int imageID, double startX, double startY, int startDirection, int depth)
: Actor(world, imageID, startX, startY, startDirection, depth) {
    
}

Environment::~Environment() {
    
}

bool Environment::isEnvironment() {
    return true;
}

