//
//  DumbZombie.cpp
//  ZombieDash
//
//  Created by Junhong Wang on 2/17/19.
//  Copyright © 2019 David Smallberg. All rights reserved.
//

#include "DumbZombie.h"
#include "StudentWorld.h"
#include "Penelope.h"
#include "ActorConstants.h"

DumbZombie::DumbZombie(StudentWorld *world, double startX, double startY)
: Zombie(world, startX, startY) {
   
}

DumbZombie::DumbZombie(StudentWorld *world, int levelX, int levelY)
: Zombie(world, levelX, levelY) {
    
}

DumbZombie::~DumbZombie() {
    
}

int DumbZombie::score() {
    return DUMB_ZOMBIE_SCORE;
}

void DumbZombie::planMovement() {
    setMovementPlanDistance(randInt(ZOMBIE_MOVEMENT_PLAN_MIN, ZOMBIE_MOVEMENT_PLAN_MAX));
    setDirection(90 * randInt(0, 3));
}

void DumbZombie::die() {
    if (!isAlive()) return;
    Zombie::die();
    dropVaccineGoodie();
}

void DumbZombie::dropVaccineGoodie() {
    if (!getWorld()->probability(VACCINE_GOODIE_DROP_PROBABILITY)) return;
    
    int directions[] = { GraphObject::right, GraphObject::left, GraphObject::up, GraphObject::down };
    int direction = directions[randInt(0, 3)];
    double minX = getX();
    double minY = getY();
    
    increment(direction, SPRITE_WIDTH, SPRITE_HEIGHT, minX, minY);
    
    getWorld()->dropVaccineGoodie(minX, minY);
}
