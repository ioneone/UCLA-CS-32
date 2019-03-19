//
//  Citizen.cpp
//  ZombieDash
//
//  Created by Junhong Wang on 2/17/19.
//  Copyright © 2019 David Smallberg. All rights reserved.
//

#include "Citizen.h"
#include "GameConstants.h"
#include "ActorConstants.h"
#include "StudentWorld.h"

Citizen::Citizen(StudentWorld *world, int levelX, int levelY)
: Person(world, IID_CITIZEN, levelX, levelY, CITIZEN_START_DIRECTION, CITIZEN_DEPTH) {
    m_isParalyzed = false;
}

Citizen::~Citizen() {
    
}

void Citizen::doSomething() {
    Person::doSomething();
    
    if (!isAlive()) return;
    
    m_isParalyzed = !m_isParalyzed;
    
    if (m_isParalyzed) return;
    
    double distanceToNearestZombie;
    bool isZombieExist = getWorld()->getDistanceToNearestZombie(getX(), getY(), distanceToNearestZombie);
    
    if (approachPenelope(isZombieExist, distanceToNearestZombie)) return;
    
    if (escapeFromZombies(isZombieExist, distanceToNearestZombie)) return;
    
}

void Citizen::mutate() {
    getWorld()->handleCitizenMutation(*this);
    die();
}

void Citizen::exit() {
    StudentWorld *world = getWorld();
    world->increaseScore(EXIT_SCORE);
    world->playSound(SOUND_CITIZEN_SAVED);
    world->decrementNumCitizens();
    setDead();
}

bool Citizen::isSmart() {
    return false;
}

double Citizen::getStep() {
    return CITIZEN_STEP;
}

bool Citizen::approachPenelope(bool isZombieExist, double distanceToNearestZombie) {
    double minX = getX();
    double minY = getY();
    double penelopeMinX;
    double penelopeMinY;
    getWorld()->getPenelopeLocation(penelopeMinX, penelopeMinY);
    double distanceToPenelope = getWorld()->getDistanceToPenelope(minX, minY);
    
    if ((!isZombieExist || distanceToPenelope < distanceToNearestZombie) && distanceToPenelope <= CITIZEN_VISION_DISTANCE * CITIZEN_VISION_DISTANCE) {
        if (minX == penelopeMinX) {
            if (approachPenelopeY(penelopeMinY)) return true;
        } else if (minY == penelopeMinY) {
            if (approachPenelopeX(penelopeMinX)) return true;
        } else {
            if (approachPenelopeXY(penelopeMinX, penelopeMinY)) return true;
        }
    }
    
    return false;
}

bool Citizen::approachPenelopeX(double penelopeMinX) {
    if (getX() < penelopeMinX) {
        setDirection(GraphObject::right);
        if (moveForward()) return true;
    } else {
        setDirection(GraphObject::left);
        if (moveForward()) return true;
    }
    return false;
}

bool Citizen::approachPenelopeY(double penelopeMinY) {
    if (getY() < penelopeMinY) {
        setDirection(GraphObject::up);
        if (moveForward()) return true;
    } else {
        setDirection(GraphObject::down);
        if (moveForward()) return true;
    }
    return false;
}
bool Citizen::approachPenelopeXY(double penelopeMinX, double penelopeMinY) {
    int directions[2];
    directions[0] = (getX() < penelopeMinX) ? GraphObject::right : GraphObject::left;
    directions[1] = (getY() < penelopeMinY) ? GraphObject::up : GraphObject::down;
    
    int r = randInt(0, 1);
    setDirection(directions[r]);
    if (moveForward()) return true;
    setDirection(directions[(r + 1) % 2]);
    if (moveForward()) return true;
    
    return false;
}

bool Citizen::escapeFromZombies(bool isZombieExist, double distanceToNearestZombie) {
    if (isZombieExist && distanceToNearestZombie < CITIZEN_VISION_DISTANCE * CITIZEN_VISION_DISTANCE) {
        
        int newDirection;
        double newMinX;
        double newMinY;
        if (!findSafestDirection(distanceToNearestZombie, newDirection, newMinX, newMinY)) return false;
        
        setDirection(newDirection);
        moveTo(newMinX, newMinY);
        return true;
        
    }
    
    return false;
}

bool Citizen::checkSafety(int direction, bool &isZombieExist, double &distance, double &newMinX, double &newMinY) {
    setDirection(direction);
    
    if (canMoveForward(newMinX, newMinY)) {
        isZombieExist = getWorld()->getDistanceToNearestZombie(newMinX, newMinY, distance);
        return true;
    }
    
    return false;
}

bool Citizen::findSafestDirection(double distanceToNearestZombie, int &newDirection, double &newMinX, double &newMinY) {
    double newDistanceToZombie = distanceToNearestZombie;
    bool isFound = false;
    
    bool tempIsZombieExist;
    double tempDistance;
    double tempX;
    double tempY;
    
    int directions[] = { GraphObject::right, GraphObject::left, GraphObject::up, GraphObject::down };
    
    for (int direction : directions) {
        if (checkSafety(direction, tempIsZombieExist, tempDistance, tempX, tempY)) {
            if (tempDistance > newDistanceToZombie) {
                newDistanceToZombie = tempDistance;
                newDirection = direction;
                newMinX = tempX;
                newMinY = tempY;
                isFound = true;
            }
        }
    }
    
    return isFound;
    
}

void Citizen::die() {
    if (!isAlive()) return;
    Creature::die();
    StudentWorld *world = getWorld();
    world->decrementNumCitizens();
    world->increaseScore(CITIZEN_DEAD_PENALTY_SCORE);
    world->playSound(SOUND_CITIZEN_DIE);
}

void Citizen::getSick() {
    if (isInfected()) return;
    Person::getSick();
    getWorld()->playSound(SOUND_CITIZEN_INFECTED);
}
