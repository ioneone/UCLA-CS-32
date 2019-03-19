//
//  MortalEnvironment.cpp
//  ZombieDash
//
//  Created by Junhong Wang on 2/24/19.
//  Copyright © 2019 David Smallberg. All rights reserved.
//

#include "MortalEnvironment.h"

MortalEnvironment::MortalEnvironment(StudentWorld *world, int imageID, double startX, double startY, int startDirection, int depth)
: Environment(world, imageID, startX, startY, startDirection, depth) {
    
}

MortalEnvironment::~MortalEnvironment() {
    
}

bool MortalEnvironment::isOverlappable() {
    return true;
}
