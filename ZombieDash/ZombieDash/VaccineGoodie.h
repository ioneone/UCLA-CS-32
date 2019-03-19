//
//  VaccineGoodie.h
//  ZombieDash
//
//  Created by Junhong Wang on 2/23/19.
//  Copyright © 2019 David Smallberg. All rights reserved.
//

#ifndef VaccineGoodie_h
#define VaccineGoodie_h

#include "Goodie.h"

class VaccineGoodie: public Goodie {
public:
    VaccineGoodie(StudentWorld *world, int levelX, int levelY);
    VaccineGoodie(StudentWorld *world, double startX, double startY);
    virtual void doSomething();
    virtual ~VaccineGoodie();
private:
};

#endif /* VaccineGoodie_h */
