//
//  Penelope.h
//  ZombieDash
//
//  Created by Junhong Wang on 2/17/19.
//  Copyright © 2019 David Smallberg. All rights reserved.
//

#ifndef Penelope_h
#define Penelope_h

#include "Person.h"

class Goodie;
class VaccineGoodie;
class GasCanGoodie;
class LandmineGoodie;


class Penelope: public Person {
public:
    Penelope(StudentWorld *world, int levelX, int levelY);
    virtual void doSomething();
    virtual void exit();
    virtual void die();
    bool didExit();
    void getVaccineGoodie(VaccineGoodie &goodie);
    void getGasCanGoodie(GasCanGoodie &goodie);
    void getLandmineGoodie(LandmineGoodie &goodie);
    virtual ~Penelope();
    
    int getNumLandmines();
    int getNumFlames();
    int getNumVaccines();
    
protected:
    virtual double getStep();
    virtual void injectVaccine();
    virtual bool isSmart();
    virtual void mutate();
    
private:
    
    void handleKeyAction();
    void handleLeftKey();
    void handleRightKey();
    void handleUpKey();
    void handleDownKey();
    void handleSpaceKey();
    void handleTabKey();
    void handleEnterKey();
    
    void eat(Goodie &goodie);
    
    bool m_didExit;
    int m_numLandmines;
    int m_numFlames;
    int m_numVaccines;

};

#endif /* Penelope_h */
