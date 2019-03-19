//
//  LandmineGoodie.h
//  ZombieDash
//
//  Created by Junhong Wang on 2/23/19.
//  Copyright © 2019 David Smallberg. All rights reserved.
//

#ifndef LandmineGoodie_h
#define LandmineGoodie_h

#include "Goodie.h"

class LandmineGoodie: public Goodie {
public:
    LandmineGoodie(StudentWorld *world, int levelX, int levelY);
    virtual void doSomething();
    virtual ~LandmineGoodie();
private:
};

#endif /* LandmineGoodie_h */
