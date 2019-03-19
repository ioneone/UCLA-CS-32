//
//  Actor.h
//  ZombieDash
//
//  Created by Junhong Wang on 2/17/19.
//  Copyright © 2019 David Smallberg. All rights reserved.
//

#ifndef Actor_h
#define Actor_h

#include "GraphObject.h"

class StudentWorld;

class Actor: public GraphObject {
public:
    Actor(StudentWorld *world, int imageID, double startX, double startY, int startDirection = 0, int depth = 0);
    virtual ~Actor();

    // pure virtual
    virtual void doSomething() = 0;
    virtual bool isAlive() = 0;
    virtual void die() = 0;
    
    // virtual
    virtual bool isOverlappable();
    virtual bool isFlammable();
    virtual bool isPerson();
    virtual bool isZombie();
    virtual bool isFlameBlockable();
    
    virtual bool isEnvironment();
    virtual bool isImmortal();
    virtual bool isCreature();
    virtual bool isGoodie();
    
    virtual void getSick();
    virtual void exit();
        
protected:
    StudentWorld* getWorld() const;
    
private:
    StudentWorld *m_world;
};

#endif /* Actor_h */
