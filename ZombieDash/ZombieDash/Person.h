//
//  Person.h
//  ZombieDash
//
//  Created by Junhong Wang on 2/24/19.
//  Copyright © 2019 David Smallberg. All rights reserved.
//

#ifndef Person_h
#define Person_h

#include "Creature.h"

class Person: public Creature {
public:
    Person(StudentWorld *world, int imageID, int levelX, int levelY, int direction, int depth);
    virtual ~Person();
    
    // virtual functions of Actor
    virtual void doSomething();
    virtual void getSick();
    virtual bool isPerson();
    
    int getNumInfectionCount();
    
protected:
    // virtual functions of Person
    virtual void injectVaccine();
    virtual bool isSmart() = 0;
    virtual void mutate() = 0;
    
    bool isInfected();
    
private:
    bool m_isInfected;
    int m_infectionCount;
};

#endif /* Person_h */
