//
//  Landmine.cpp
//  ZombieDash
//
//  Created by Junhong Wang on 2/17/19.
//  Copyright © 2019 David Smallberg. All rights reserved.
//

#include "Landmine.h"
#include "GameConstants.h"
#include "ActorConstants.h"
#include "StudentWorld.h"
#include "Penelope.h"
#include "Flame.h"
#include "Pit.h"

Landmine::Landmine(StudentWorld *world, double startX, double startY)
: FlammableEnvironment(world, IID_LANDMINE, startX, startY, LANDMINE_START_DIRECTION, LANDMINE_DEPTH) {
    m_numSafetyTicks = LANDMINE_START_SAFETY_TICKS;
}

void Landmine::doSomething() {
    if (!isAlive()) return;
    
    updateSafetyTicks();
    
    if (!isActive()) return;
    
    if (!getWorld()->hasOverlapWithActorsOrPlayer(*this)) return;
    
    explode();
    
}

Landmine::~Landmine() {
    
}

void Landmine::explode() {
    StudentWorld *world = getWorld();
    world->handleLandmineExplosion(*this);
    world->playSound(SOUND_LANDMINE_EXPLODE);
    die();
}

bool Landmine::isActive() const {
    return m_numSafetyTicks == 0;
}

void Landmine::updateSafetyTicks() {
    m_numSafetyTicks = (m_numSafetyTicks > 0) ? m_numSafetyTicks - 1 : m_numSafetyTicks;
}
