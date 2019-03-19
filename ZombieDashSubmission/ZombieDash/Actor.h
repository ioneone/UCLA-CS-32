#ifndef ACTOR_H_
#define ACTOR_H_

#include "GraphObject.h"

// Step
const double PENELOPE_STEP = 4;
const double ZOMBIE_STEP   = 1;
const double CITIZEN_STEP  = 2;

// Start Direction
const int PENELOPE_START_DIRECTION = GraphObject::right;
const int WALL_START_DIRECTION     = GraphObject::right;
const int EXIT_START_DIRECTION     = GraphObject::right;
const int PIT_START_DIRECTION      = GraphObject::right;
const int GOODIE_START_DIRECTION   = GraphObject::right;
const int LANDMINE_START_DIRECTION = GraphObject::right;
const int ZOMBIE_START_DIRECTION   = GraphObject::right;
const int CITIZEN_START_DIRECTION  = GraphObject::right;

// Depth
const int PENELOPE_DEPTH = 0;
const int WALL_DEPTH     = 0;
const int EXIT_DEPTH     = 1;
const int PIT_DEPTH      = 0;
const int FLAME_DEPTH    = 0;
const int VOMIT_DEPTH    = 0;
const int GOODIE_DEPTH   = 1;
const int LANDMINE_DEPTH = 1;
const int ZOMBIE_DEPTH   = 0;
const int CITIZEN_DEPTH  = 0;

// Infection Count
const int MAX_INFECTION_COUNT = 500;

// Scores
const int EXIT_SCORE                 = 500;
const int GOODIE_SCORE               = 50;
const int DUMB_ZOMBIE_SCORE          = 1000;
const int SMART_ZOMBIE_SCORE         = 2000;
const int CITIZEN_DEAD_PENALTY_SCORE = -1000;


// Life
const int START_FLAME_LIVES = 2;
const int START_VOMIT_LIVES = 2;

// Charges
const int CHARGES_PER_VACCINE_GOODIE = 1;
const int CHARGES_PER_GAS_CAN_GOODIE = 5;
const int CHARGES_PER_LANDMINE_GOODIE = 2;

// Safety Ticks
const int LANDMINE_START_SAFETY_TICKS = 30;

// Probabilities
const double VOMIT_PROBABILITY               = 0.3;
const double DUMB_ZOMBIE_PROBABILITY         = 0.7;
const double VACCINE_GOODIE_DROP_PROBABILITY = 0.1;

// Distances
const double OVERLAP_EUCLIDEAN_DISTANCE  = 10;
const double CITIZEN_VISION_DISTANCE     = 80;
const double SMART_ZOMBIE_VISION_DISTANE = 80;

const int ZOMBIE_MOVEMENT_PLAN_MIN = 3;
const int ZOMBIE_MOVEMENT_PLAN_MAX = 10;

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

class Environment: public Actor {
public:
    Environment(StudentWorld *world, int imageID, double startX, double startY, int startDirection = 0, int depth = 0);
    virtual ~Environment();
    
    virtual bool isEnvironment();
};


class ImmortalEnvironment: public Actor {
public:
    ImmortalEnvironment(StudentWorld *world, int imageID, double startX, double startY, int startDirection, int depth);
    virtual ~ImmortalEnvironment();
    
    virtual void die();
    virtual bool isAlive();
    virtual bool isImmortal();
};

class Wall: public ImmortalEnvironment {
public:
    Wall(StudentWorld *world, int levelX, int levelY);
    virtual ~Wall();
    
    virtual void doSomething();
    virtual bool isFlameBlockable();
};


class Exit: public ImmortalEnvironment {
public:
    Exit(StudentWorld *world, int levelX, int levelY);
    virtual void doSomething();
    virtual bool isOverlappable();
    virtual ~Exit();
    virtual bool isFlameBlockable();
};

class Pit: public ImmortalEnvironment {
public:
    Pit(StudentWorld *world, double startX, double startY);
    Pit(StudentWorld *world, int levelX, int levelY);
    virtual ~Pit();
    
    virtual void doSomething();
    virtual bool isOverlappable();
};

class MortalEnvironment: public Environment {
public:
    MortalEnvironment(StudentWorld *world, int imageID, double startX, double startY, int startDirection = 0, int depth = 0);
    virtual ~MortalEnvironment();
    
    virtual bool isOverlappable();
};

class InflammableEnvironment: public MortalEnvironment {
public:
    InflammableEnvironment(StudentWorld *world, int imageID, double startX, double startY, int startLives, int startDirection = 0, int depth = 0);
    virtual ~InflammableEnvironment();
    
    virtual bool isAlive();
    virtual void die();
    
protected:
    void decrementLife();
    
private:
    int m_life;
};

class Flame: public InflammableEnvironment {
public:
    Flame(StudentWorld *world, double startX, double startY, int direction);
    virtual ~Flame();
    
    virtual void doSomething();
    
};


class Vomit: public InflammableEnvironment {
public:
    Vomit(StudentWorld *world, double startX, double startY, int direction);
    virtual ~Vomit();
    
    virtual void doSomething();
    
};


class FlammableEnvironment: public MortalEnvironment {
public:
    FlammableEnvironment(StudentWorld *world, int imageID, double startX, double startY, int startDirection = 0, int depth = 0);
    virtual ~FlammableEnvironment();
    
    virtual bool isFlammable();
    virtual void die();
    virtual bool isAlive();
private:
    bool m_isAlive;
};


class Landmine: public FlammableEnvironment {
public:
    Landmine(StudentWorld *world, double startX, double startY);
    virtual void doSomething();
    virtual ~Landmine();
    
private:
    void updateSafetyTicks();
    void explode();
    bool isActive() const;
    int m_numSafetyTicks;
};


class Goodie: public FlammableEnvironment {
public:
    Goodie(StudentWorld *world, int iid, int levelX, int levelY);
    Goodie(StudentWorld *world, int iid, double startX, double startY);
    virtual ~Goodie();
    
    virtual bool isGoodie();
};

class VaccineGoodie: public Goodie {
public:
    VaccineGoodie(StudentWorld *world, int levelX, int levelY);
    VaccineGoodie(StudentWorld *world, double startX, double startY);
    virtual void doSomething();
    virtual ~VaccineGoodie();
private:
};


class GasCanGoodie: public Goodie {
public:
    GasCanGoodie(StudentWorld *world, int levelX, int levelY);
    virtual void doSomething();
    virtual ~GasCanGoodie();
private:
};


class LandmineGoodie: public Goodie {
public:
    LandmineGoodie(StudentWorld *world, int levelX, int levelY);
    virtual void doSomething();
    virtual ~LandmineGoodie();
private:
};


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


class SmartZombie: public Zombie {
public:
    SmartZombie(StudentWorld *world, double startX, double startY);
    SmartZombie(StudentWorld *world, int levelX, int levelY);
    virtual ~SmartZombie();
    virtual int score();
protected:
    virtual void planMovement();
};


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


class Citizen: public Person {
public:
    Citizen(StudentWorld *world, int levelX, int levelY);
    virtual ~Citizen();
    virtual void doSomething();
    virtual void exit();
    virtual void die();
    virtual void getSick();
    
protected:
    virtual double getStep();
    virtual bool isSmart();
    virtual void mutate();
    
private:
    bool approachPenelope(bool isZombieExist, double distanceToNearestZombie);
    bool approachPenelopeX(double penelopeMinX);
    bool approachPenelopeY(double penelopeMinY);
    bool approachPenelopeXY(double penelopeMinX, double penelopeMinY);
    bool escapeFromZombies(bool isZombieExist, double distanceToNearestZombie);
    bool checkSafety(int direction, bool &isZombieExist, double &distance, double &newMinX, double &newMinY);
    bool findSafestDirection(double distanceToNearestZombie, int &newDirection, double &newMinX, double &newMinY);
    bool m_isParalyzed;
};

#endif // ACTOR_H_
