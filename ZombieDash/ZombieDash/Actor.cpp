//
//  Actor.cpp
//  ZombieDash
//
//  Created by Junhong Wang on 2/17/19.
//  Copyright © 2019 David Smallberg. All rights reserved.
//

#include "Actor.h"
#include "ActorConstants.h"

Actor::Actor(StudentWorld *world, int imageID, double startX, double startY, int startDirection, int depth)
: GraphObject(imageID, startX, startY, startDirection, depth) {
    m_world = world;
}

Actor::~Actor() {
    
}

StudentWorld* Actor::getWorld() const {
    return m_world;
}

bool Actor::isPerson() {
    return false;
}

void Actor::getSick() {
    
}

void Actor::exit() {
    
}

void Actor::doSomething() {
    
}

bool Actor::isOverlappable() {
    return false;
}

bool Actor::isAlive() {
    return false;
}

void Actor::die() {
}

bool Actor::isFlammable() {
    return false;
}

bool Actor::isEnvironment() {
    return false;
}

bool Actor::isCreature() {
    return false;
}

bool Actor::isImmortal() {
    return false;
}

bool Actor::isZombie() {
    return false;
}

bool Actor::isFlameBlockable() {
    return false;
}

bool Actor::isGoodie() {
    return false;
}
