//
//  Creature.cpp
//  ZombieDash
//
//  Created by Junhong Wang on 2/24/19.
//  Copyright © 2019 David Smallberg. All rights reserved.
//

#include "Creature.h"
#include "StudentWorld.h"

Creature::Creature(StudentWorld *world, int imageID, double startX, double startY, int startDirection, int depth)
: Actor(world, imageID, startX, startY, startDirection, depth) {
    m_isAlive = true;
}

Creature::~Creature() {
    
}

bool Creature::isCreature() {
    return true;
}

bool Creature::isFlammable() {
    return true;
}

bool Creature::canMoveForward(double &newX, double &newY) {
    
    bool canMove = true;
    
    double newMinX = getX();
    double newMinY = getY();
    double step = getStep();
    
    increment(getDirection(), step, step, newMinX, newMinY);
    
    canMove = getWorld()->handleCanMoveTo(*this, newMinX, newMinY);
    
    if (canMove) {
        newX = newMinX;
        newY = newMinY;
    }
    
    return canMove;
}

bool Creature::moveForward() {
    double newX;
    double newY;
    if (canMoveForward(newX, newY)) {
        moveTo(newX, newY);
        return true;
    }
    return false;
}

bool Creature::isAlive() {
    return m_isAlive;
}

void Creature::setDead() {
    m_isAlive = false;
}

void Creature::die() {
    m_isAlive = false;
}

void Creature::increment(int direction, double sizeX, double sizeY, double &x, double &y) {
    switch (direction) {
        case GraphObject::left:
            x -= sizeX;
            break;
        case GraphObject::right:
            x += sizeX;
            break;
        case GraphObject::up:
            y += sizeY;
            break;
        case GraphObject::down:
            y -= sizeY;
            break;
        default:
            break;
    }
}
