//
//  Person.cpp
//  ZombieDash
//
//  Created by Junhong Wang on 2/24/19.
//  Copyright © 2019 David Smallberg. All rights reserved.
//

#include "Person.h"
#include "GameConstants.h"
#include "ActorConstants.h"

Person::Person(StudentWorld *world, int imageID, int levelX, int levelY, int direction, int depth)
: Creature(world, imageID, SPRITE_WIDTH * levelX, SPRITE_HEIGHT * levelY, direction, depth) {
    m_isInfected = false;
    m_infectionCount = 0;
}

void Person::doSomething() {
    if (!isAlive()) return;
    
    if (!m_isInfected) return;
    
    m_infectionCount++;
    
    if (m_infectionCount == MAX_INFECTION_COUNT) mutate();
    
}

void Person::getSick() {
    m_isInfected = true;
}

bool Person::isPerson() {
    return true;
}

Person::~Person() {
    
}

void Person::injectVaccine() {
    if (!isSmart()) return;
    
    m_isInfected = false;
    m_infectionCount = 0;
}

int Person::getNumInfectionCount() {
    return m_infectionCount;
}

bool Person::isInfected() {
    return m_isInfected;
}
