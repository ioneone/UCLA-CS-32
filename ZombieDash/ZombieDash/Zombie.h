//
//  Zombie.h
//  ZombieDash
//
//  Created by Junhong Wang on 2/22/19.
//  Copyright © 2019 David Smallberg. All rights reserved.
//

#ifndef Zombie_h
#define Zombie_h

#include "Creature.h"

class Zombie: public Creature {
public:
    Zombie(StudentWorld *world, double startX, double startY);
    Zombie(StudentWorld *world, int levelX, int levelY);
    virtual ~Zombie();
    
    virtual void doSomething();
    virtual bool isZombie();
    virtual void die();
    virtual int score() = 0;
    
protected:
    virtual double getStep();
    virtual bool moveForward();
    virtual void planMovement() = 0;
    bool vomit();
    void computeVomitCoordinates(double &vomitMinX, double &vomitMinY);
    double getMovementPlanDistance() const;
    void setMovementPlanDistance(double distance);
    void decrementMovementPlanDistance();
    bool isParalyzed();
    
private:
    double m_movementPlanDistance;
    bool m_isParalyzed;
};

#endif /* Zombie_h */
