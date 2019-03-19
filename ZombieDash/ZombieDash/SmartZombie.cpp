//
//  SmartZombie.cpp
//  ZombieDash
//
//  Created by Junhong Wang on 2/17/19.
//  Copyright © 2019 David Smallberg. All rights reserved.
//

#include "SmartZombie.h"
#include "StudentWorld.h"
#include "ActorConstants.h"

SmartZombie::SmartZombie(StudentWorld *world, double startX, double startY)
: Zombie(world, startX, startY) {
    
}

SmartZombie::SmartZombie(StudentWorld *world, int levelX, int levelY)
: Zombie(world, levelX, levelY) {
    
}

void SmartZombie::planMovement() {
    double minX = getX();
    double minY = getY();

    double distance;
    double personMinX;
    double personMinY;
    getWorld()->getNearestPersonCoordinates(minX, minY, distance, personMinX, personMinY);
    
    setMovementPlanDistance(randInt(ZOMBIE_MOVEMENT_PLAN_MIN, ZOMBIE_MOVEMENT_PLAN_MAX));
    
    if (distance > SMART_ZOMBIE_VISION_DISTANE * SMART_ZOMBIE_VISION_DISTANE) {
        setDirection(90 * randInt(0, 3));
    } else {
        // get closer to person
        if (minX == personMinX) {
            if (minY < personMinY) {
                setDirection(GraphObject::up);
            } else {
                setDirection(GraphObject::down);
            }
        } else if (minY == personMinY) {
            if (minX < personMinX) {
                setDirection(GraphObject::right);
            } else {
                setDirection(GraphObject::left);
            }
        } else {
            int directions[2];
            directions[0] = (minX < personMinX) ? GraphObject::right : GraphObject::left;
            directions[1] = (minY < personMinY) ? GraphObject::up : GraphObject::down;
            
            setDirection(directions[randInt(0, 1)]);
        }
    }
}

SmartZombie::~SmartZombie() {
    
}

int SmartZombie::score() {
    return SMART_ZOMBIE_SCORE;
}
