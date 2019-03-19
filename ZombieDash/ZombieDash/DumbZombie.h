//
//  DumbZombie.h
//  ZombieDash
//
//  Created by Junhong Wang on 2/17/19.
//  Copyright © 2019 David Smallberg. All rights reserved.
//

#ifndef DumbZombie_h
#define DumbZombie_h

#include "Zombie.h"

class DumbZombie: public Zombie {
public:
    DumbZombie(StudentWorld *world, double startX, double startY);
    DumbZombie(StudentWorld *world, int levelX, int levelY);
    virtual ~DumbZombie();
    virtual int score();
    virtual void die();
protected:
    virtual void planMovement();
    
private:
    void dropVaccineGoodie();
};

#endif /* DumbZombie_h */
