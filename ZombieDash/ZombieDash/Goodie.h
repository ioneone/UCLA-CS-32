//
//  Goodie.h
//  ZombieDash
//
//  Created by Junhong Wang on 2/23/19.
//  Copyright © 2019 David Smallberg. All rights reserved.
//

#ifndef Goodie_h
#define Goodie_h

#include "FlammableEnvironment.h"

class Goodie: public FlammableEnvironment {
public:
    Goodie(StudentWorld *world, int iid, int levelX, int levelY);
    Goodie(StudentWorld *world, int iid, double startX, double startY);
    virtual ~Goodie();
    
    virtual bool isGoodie();
};

#endif /* Goodie_h */
