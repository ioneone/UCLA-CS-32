//
//  Creature.h
//  ZombieDash
//
//  Created by Junhong Wang on 2/24/19.
//  Copyright © 2019 David Smallberg. All rights reserved.
//

#ifndef Creature_h
#define Creature_h

#include "Actor.h"

class Creature: public Actor {
public:
    Creature(StudentWorld *world, int imageID, double startX, double startY, int startDirection = 0, int depth = 0);
    virtual ~Creature();
    
    virtual bool isCreature();
    virtual bool isFlammable();
    virtual bool isAlive();
    virtual void die();
    
protected:
    virtual double getStep() = 0;
    virtual bool moveForward();
    
    void setDead();
    void increment(int direction, double sizeX, double sizeY, double &x, double &y);
    bool canMoveForward(double &newX, double &newY);
    
private:
    bool m_isAlive;
    
};

#endif /* Creature_h */
