//
//  Citizen.h
//  ZombieDash
//
//  Created by Junhong Wang on 2/17/19.
//  Copyright © 2019 David Smallberg. All rights reserved.
//

#ifndef Citizen_h
#define Citizen_h

#include "Person.h"

class Citizen: public Person {
public:
    Citizen(StudentWorld *world, int levelX, int levelY);
    virtual ~Citizen();
    virtual void doSomething();
    virtual void exit();
    virtual void die();
    virtual void getSick();
    
protected:
    virtual double getStep();
    virtual bool isSmart();
    virtual void mutate();
    
private:
    bool approachPenelope(bool isZombieExist, double distanceToNearestZombie);
    bool approachPenelopeX(double penelopeMinX);
    bool approachPenelopeY(double penelopeMinY);
    bool approachPenelopeXY(double penelopeMinX, double penelopeMinY);
    bool escapeFromZombies(bool isZombieExist, double distanceToNearestZombie);
    bool checkSafety(int direction, bool &isZombieExist, double &distance, double &newMinX, double &newMinY);
    bool findSafestDirection(double distanceToNearestZombie, int &newDirection, double &newMinX, double &newMinY);
    bool m_isParalyzed;
};

#endif /* Citizen_h */
