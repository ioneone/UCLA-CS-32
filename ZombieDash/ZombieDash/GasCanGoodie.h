//
//  GasCanGoodie.h
//  ZombieDash
//
//  Created by Junhong Wang on 2/23/19.
//  Copyright © 2019 David Smallberg. All rights reserved.
//

#ifndef GasCanGoodie_h
#define GasCanGoodie_h

#include "Goodie.h"

class GasCanGoodie: public Goodie {
public:
    GasCanGoodie(StudentWorld *world, int levelX, int levelY);
    virtual void doSomething();
    virtual ~GasCanGoodie();
private:
};

#endif /* GasCanGoodie_h */
