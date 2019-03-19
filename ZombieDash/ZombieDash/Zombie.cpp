//
//  Zombie.cpp
//  ZombieDash
//
//  Created by Junhong Wang on 2/22/19.
//  Copyright © 2019 David Smallberg. All rights reserved.
//

#include "Zombie.h"
#include "ActorConstants.h"
#include "Penelope.h"
#include "StudentWorld.h"
#include "Vomit.h"

Zombie::Zombie(StudentWorld *world, double startX, double startY)
: Creature(world, IID_ZOMBIE, startX, startY, ZOMBIE_START_DIRECTION, ZOMBIE_DEPTH) {
    m_isParalyzed = false;
    m_movementPlanDistance = 0;
    getWorld()->playSound(SOUND_ZOMBIE_BORN);
}

Zombie::Zombie(StudentWorld *world, int levelX, int levelY)
: Creature(world, IID_ZOMBIE, SPRITE_WIDTH * levelX, SPRITE_HEIGHT * levelY, ZOMBIE_START_DIRECTION, ZOMBIE_DEPTH) {
    m_isParalyzed = false;
    m_movementPlanDistance = 0;
}

void Zombie::doSomething() {
    if (!isAlive()) return;
    m_isParalyzed = !m_isParalyzed;
    
    if (isParalyzed()) return;
    
    if (vomit()) return;
    
    if (m_movementPlanDistance == 0) planMovement();
    
    moveForward();
}

bool Zombie::isParalyzed() {
    return m_isParalyzed;
}

bool Zombie::vomit() {
    
    double vomitMinX;
    double vomitMinY;
    computeVomitCoordinates(vomitMinX, vomitMinY);
    
    return getWorld()->handleZombieVomit(*this, vomitMinX, vomitMinY);

}

Zombie::~Zombie() {
    
}

void Zombie::die() {
    if (!isAlive()) return;
    Creature::die();
    StudentWorld *world = getWorld();
    world->increaseScore(score());
    world->playSound(SOUND_ZOMBIE_DIE);
}

bool Zombie::isZombie() {
    return true;
}

void Zombie::computeVomitCoordinates(double &vomitMinX, double &vomitMinY) {
    
    vomitMinX = getX();
    vomitMinY = getY();
    
    increment(getDirection(), SPRITE_WIDTH, SPRITE_HEIGHT, vomitMinX, vomitMinY);
}

double Zombie::getMovementPlanDistance() const {
    return m_movementPlanDistance;
}
void Zombie::setMovementPlanDistance(double distance) {
    m_movementPlanDistance = distance;
}

bool Zombie::moveForward() {
    if (Creature::moveForward()) {
        decrementMovementPlanDistance();
        return true;
    } else {
        setMovementPlanDistance(0);
        return false;
    }
}

double Zombie::getStep() {
    return ZOMBIE_STEP;
}

void Zombie::decrementMovementPlanDistance() {
    if (m_movementPlanDistance == 0) return;
    m_movementPlanDistance--;
}
