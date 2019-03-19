//
//  Penelope.cpp
//  ZombieDash
//
//  Created by Junhong Wang on 2/17/19.
//  Copyright © 2019 David Smallberg. All rights reserved.
//

#include "Penelope.h"
#include "GameConstants.h"
#include "GameController.h"
#include "StudentWorld.h"
#include "ActorConstants.h"
#include "VaccineGoodie.h"
#include "GasCanGoodie.h"
#include "LandmineGoodie.h"

Penelope::Penelope(StudentWorld *world, int levelX, int levelY)
: Person(world, IID_PLAYER, levelX, levelY, PENELOPE_START_DIRECTION, PENELOPE_DEPTH) {
    m_didExit = false;
    m_numLandmines = 0;
    m_numFlames = 0;
    m_numVaccines = 0;
}

void Penelope::doSomething() {
    Person::doSomething();
    
    if (!isAlive()) return;
    
    handleKeyAction();
    
}

void Penelope::mutate() {
    die();
}

void Penelope::die() {
    if (!isAlive()) return;
    Creature::die();
    getWorld()->playSound(SOUND_PLAYER_DIE);
}

void Penelope::exit() {
    m_didExit = true;
}

bool Penelope::didExit() {
    return m_didExit;
}

Penelope::~Penelope() {
    
}

void Penelope::handleKeyAction() {
    int key;
    StudentWorld *world = getWorld();
    
    if (!world->getKey(key)) return;
    switch (key) {
        case KEY_PRESS_LEFT:
            handleLeftKey();
            break;
        case KEY_PRESS_RIGHT:
            handleRightKey();
            break;
        case KEY_PRESS_UP:
            handleUpKey();
            break;
        case KEY_PRESS_DOWN:
            handleDownKey();
            break;
        case KEY_PRESS_SPACE:
            handleSpaceKey();
            break;
        case KEY_PRESS_TAB:
            handleTabKey();
            break;
        case KEY_PRESS_ENTER:
            handleEnterKey();
            break;
        default:
            return;
    }
}

void Penelope::handleLeftKey() {
    setDirection(GraphObject::left);
    moveForward();
}

void Penelope::handleRightKey() {
    setDirection(GraphObject::right);
    moveForward();
}

void Penelope::handleUpKey() {
    setDirection(GraphObject::up);
    moveForward();
}

void Penelope::handleDownKey() {
    setDirection(GraphObject::down);
    moveForward();
}

void Penelope::handleSpaceKey() {
    if (m_numFlames == 0) return;
    StudentWorld *world = getWorld();
    world->generateFlames(getX(), getY(), getDirection());
    world->playSound(SOUND_PLAYER_FIRE);
    m_numFlames--;
}

void Penelope::handleTabKey() {
    if (m_numLandmines == 0) return;
    getWorld()->generateLandmine(getX(), getY());
    m_numLandmines--;
}

void Penelope::handleEnterKey() {
    injectVaccine();
}

void Penelope::getVaccineGoodie(VaccineGoodie &goodie) {
    eat(goodie);
    m_numVaccines += CHARGES_PER_VACCINE_GOODIE;
}

void Penelope::getGasCanGoodie(GasCanGoodie &goodie) {
    eat(goodie);
    m_numFlames += CHARGES_PER_GAS_CAN_GOODIE;
}

void Penelope::getLandmineGoodie(LandmineGoodie &goodie) {
    eat(goodie);
    m_numLandmines += CHARGES_PER_GAS_CAN_GOODIE;
}

void Penelope::eat(Goodie &goodie) {
    goodie.die();
    StudentWorld *world = getWorld();
    world->increaseScore(GOODIE_SCORE);
    world->playSound(SOUND_GOT_GOODIE);
    
}

bool Penelope::isSmart() {
    return true;
}

void Penelope::injectVaccine() {
    if (m_numVaccines == 0) return;
    Person::injectVaccine();
    m_numVaccines--;
}

double Penelope::getStep() {
    return PENELOPE_STEP;
}

int Penelope::getNumLandmines() {
    return m_numLandmines;
}

int Penelope::getNumFlames() {
    return m_numFlames;
}
int Penelope::getNumVaccines() {
    return m_numVaccines;
}
