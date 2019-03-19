#include "Actor.h"
#include "StudentWorld.h"

Actor::Actor(StudentWorld *world, int imageID, double startX, double startY, int startDirection, int depth)
: GraphObject(imageID, startX, startY, startDirection, depth) {
    m_world = world;
}

Actor::~Actor() {
    
}

StudentWorld* Actor::getWorld() const {
    return m_world;
}

bool Actor::isPerson() {
    return false;
}

void Actor::getSick() {
    
}

void Actor::exit() {
    
}

void Actor::doSomething() {
    
}

bool Actor::isOverlappable() {
    return false;
}

bool Actor::isAlive() {
    return false;
}

void Actor::die() {
}

bool Actor::isFlammable() {
    return false;
}

bool Actor::isEnvironment() {
    return false;
}

bool Actor::isCreature() {
    return false;
}

bool Actor::isImmortal() {
    return false;
}

bool Actor::isZombie() {
    return false;
}

bool Actor::isFlameBlockable() {
    return false;
}

bool Actor::isGoodie() {
    return false;
}


Environment::Environment(StudentWorld *world, int imageID, double startX, double startY, int startDirection, int depth)
: Actor(world, imageID, startX, startY, startDirection, depth) {
    
}

Environment::~Environment() {
    
}

bool Environment::isEnvironment() {
    return true;
}

ImmortalEnvironment::ImmortalEnvironment(StudentWorld *world, int imageID, double startX, double startY, int startDirection, int depth)
: Actor(world, imageID, startX, startY, startDirection, depth) {
    
}

void ImmortalEnvironment::die() {
    
}

bool ImmortalEnvironment::isAlive() {
    return true;
}

ImmortalEnvironment::~ImmortalEnvironment() {
    
}

bool ImmortalEnvironment::isImmortal() {
    return true;
}

Wall::Wall(StudentWorld *world, int levelX, int levelY)
: ImmortalEnvironment(world, IID_WALL, SPRITE_WIDTH * levelX, SPRITE_HEIGHT * levelY, WALL_START_DIRECTION, WALL_DEPTH) {
    
}

void Wall::doSomething() {
    
}

Wall::~Wall() {
    
}

bool Wall::isFlameBlockable() {
    return true;
}

Exit::Exit(StudentWorld *world, int levelX, int levelY)
: ImmortalEnvironment(world, IID_EXIT, SPRITE_WIDTH * levelX , SPRITE_HEIGHT * levelY, EXIT_START_DIRECTION, EXIT_DEPTH){
    
}

void Exit::doSomething() {
    
    getWorld()->handleExit(*this);
    
}

bool Exit::isOverlappable() {
    return true;
}

Exit::~Exit() {
    
}


bool Exit::isFlameBlockable() {
    return true;
}

Pit::Pit(StudentWorld *world, double startX, double startY)
: ImmortalEnvironment(world, IID_PIT, startX, startY, PIT_START_DIRECTION, PIT_DEPTH) {
    
}

Pit::Pit(StudentWorld *world, int levelX, int levelY)
: ImmortalEnvironment(world, IID_PIT, SPRITE_WIDTH * levelX, SPRITE_HEIGHT * levelY, PIT_START_DIRECTION, PIT_DEPTH) {
    
}

void Pit::doSomething() {
    
    getWorld()->handlePit(*this);
}

bool Pit::isOverlappable() {
    return true;
}

Pit::~Pit() {
    
}



MortalEnvironment::MortalEnvironment(StudentWorld *world, int imageID, double startX, double startY, int startDirection, int depth)
: Environment(world, imageID, startX, startY, startDirection, depth) {
    
}

MortalEnvironment::~MortalEnvironment() {
    
}

bool MortalEnvironment::isOverlappable() {
    return true;
}


InflammableEnvironment::InflammableEnvironment(StudentWorld *world, int imageID, double startX, double startY, int startLives, int startDirection, int depth)
: MortalEnvironment(world, imageID, startX, startY, startDirection, depth) {
    m_life = startLives;
}

InflammableEnvironment::~InflammableEnvironment() {
    
}

bool InflammableEnvironment::isAlive() {
    return m_life > 0;
}

void InflammableEnvironment::die() {
    m_life = 0;
}

void InflammableEnvironment::decrementLife() {
    if (m_life == 0) return;
    m_life--;
}


Flame::Flame(StudentWorld *world, double startX, double startY, int direction)
: InflammableEnvironment(world, IID_FLAME, startX, startY, START_FLAME_LIVES, direction, FLAME_DEPTH) {
    
}

void Flame::doSomething() {
    if (!isAlive()) return;
    
    decrementLife();
    
    if (!isAlive()) return;
    
    getWorld()->handleFlame(*this);
    
}

Flame::~Flame() {
    
}


Vomit::Vomit(StudentWorld *world, double startX, double startY, int direction)
: InflammableEnvironment(world, IID_VOMIT, startX, startY, START_VOMIT_LIVES, direction, VOMIT_DEPTH) {
}

void Vomit::doSomething() {
    if (!isAlive()) return;
    
    decrementLife();
    
    if (!isAlive()) return;
    
    getWorld()->handleVomit(*this);
        
}

Vomit::~Vomit() {
    
}


FlammableEnvironment::FlammableEnvironment(StudentWorld *world, int imageID, double startX, double startY, int startDirection, int depth)
: MortalEnvironment(world, imageID, startX, startY, startDirection, depth) {
    m_isAlive = true;
}
FlammableEnvironment::~FlammableEnvironment() {
    
}

bool FlammableEnvironment::isFlammable() {
    return true;
}

void FlammableEnvironment::die() {
    if (!m_isAlive) return;
    m_isAlive = false;
}

bool FlammableEnvironment::isAlive() {
    return m_isAlive;
}



Landmine::Landmine(StudentWorld *world, double startX, double startY)
: FlammableEnvironment(world, IID_LANDMINE, startX, startY, LANDMINE_START_DIRECTION, LANDMINE_DEPTH) {
    m_numSafetyTicks = LANDMINE_START_SAFETY_TICKS;
}

void Landmine::doSomething() {
    if (!isAlive()) return;
    
    updateSafetyTicks();
    
    if (!isActive()) return;
    
    if (!getWorld()->hasOverlapWithActorsOrPlayer(*this)) return;
    
    explode();
    
}

Landmine::~Landmine() {
    
}

void Landmine::explode() {
    StudentWorld *world = getWorld();
    world->handleLandmineExplosion(*this);
    world->playSound(SOUND_LANDMINE_EXPLODE);
    die();
}

bool Landmine::isActive() const {
    return m_numSafetyTicks == 0;
}

void Landmine::updateSafetyTicks() {
    m_numSafetyTicks = (m_numSafetyTicks > 0) ? m_numSafetyTicks - 1 : m_numSafetyTicks;
}


Goodie::Goodie(StudentWorld *world, int iid, int levelX, int levelY)
: FlammableEnvironment(world, iid, SPRITE_WIDTH * levelX, SPRITE_HEIGHT * levelY, GOODIE_START_DIRECTION, GOODIE_DEPTH) {
    
}

Goodie::Goodie(StudentWorld *world, int iid, double startX, double startY)
: FlammableEnvironment(world, iid, startX, startY, GOODIE_START_DIRECTION, GOODIE_DEPTH) {
    
}

Goodie::~Goodie() {
    
}

bool Goodie::isGoodie() {
    return true;
}

VaccineGoodie::VaccineGoodie(StudentWorld *world, int levelX, int levelY)
: Goodie(world, IID_VACCINE_GOODIE, levelX, levelY) {
    
}

VaccineGoodie::VaccineGoodie(StudentWorld *world, double startX, double startY)
: Goodie(world, IID_VACCINE_GOODIE, startX, startY) {
    
}

void VaccineGoodie::doSomething() {
    if (!isAlive()) return;
    
    getWorld()->handleVaccineGoodie(*this);
}

VaccineGoodie::~VaccineGoodie() {
    
}


GasCanGoodie::GasCanGoodie(StudentWorld *world, int levelX, int levelY)
: Goodie(world, IID_GAS_CAN_GOODIE, levelX, levelY) {
    
}

void GasCanGoodie::doSomething() {
    if (!isAlive()) return;
    
    getWorld()->handleGasCanGoodie(*this);
}

GasCanGoodie::~GasCanGoodie() {
    
}


LandmineGoodie::LandmineGoodie(StudentWorld *world, int levelX, int levelY)
: Goodie(world, IID_LANDMINE_GOODIE, levelX, levelY) {
    
}

void LandmineGoodie::doSomething() {
    if (!isAlive()) return;
    
    getWorld()->handleLandmineGoodie(*this);
}

LandmineGoodie::~LandmineGoodie() {
    
}


Creature::Creature(StudentWorld *world, int imageID, double startX, double startY, int startDirection, int depth)
: Actor(world, imageID, startX, startY, startDirection, depth) {
    m_isAlive = true;
}

Creature::~Creature() {
    
}

bool Creature::isCreature() {
    return true;
}

bool Creature::isFlammable() {
    return true;
}

bool Creature::canMoveForward(double &newX, double &newY) {
    
    bool canMove = true;
    
    double newMinX = getX();
    double newMinY = getY();
    double step = getStep();
    
    increment(getDirection(), step, step, newMinX, newMinY);
    
    canMove = getWorld()->handleCanMoveTo(*this, newMinX, newMinY);
    
    if (canMove) {
        newX = newMinX;
        newY = newMinY;
    }
    
    return canMove;
}

bool Creature::moveForward() {
    double newX;
    double newY;
    if (canMoveForward(newX, newY)) {
        moveTo(newX, newY);
        return true;
    }
    return false;
}

bool Creature::isAlive() {
    return m_isAlive;
}

void Creature::setDead() {
    m_isAlive = false;
}

void Creature::die() {
    m_isAlive = false;
}

void Creature::increment(int direction, double sizeX, double sizeY, double &x, double &y) {
    switch (direction) {
        case GraphObject::left:
            x -= sizeX;
            break;
        case GraphObject::right:
            x += sizeX;
            break;
        case GraphObject::up:
            y += sizeY;
            break;
        case GraphObject::down:
            y -= sizeY;
            break;
        default:
            break;
    }
}


Zombie::Zombie(StudentWorld *world, double startX, double startY)
: Creature(world, IID_ZOMBIE, startX, startY, ZOMBIE_START_DIRECTION, ZOMBIE_DEPTH) {
    m_isParalyzed = false;
    m_movementPlanDistance = 0;
    getWorld()->playSound(SOUND_ZOMBIE_BORN);
}

Zombie::Zombie(StudentWorld *world, int levelX, int levelY)
: Creature(world, IID_ZOMBIE, SPRITE_WIDTH * levelX, SPRITE_HEIGHT * levelY, ZOMBIE_START_DIRECTION, ZOMBIE_DEPTH) {
    m_isParalyzed = false;
    m_movementPlanDistance = 0;
}

void Zombie::doSomething() {
    if (!isAlive()) return;
    m_isParalyzed = !m_isParalyzed;
    
    if (isParalyzed()) return;
    
    if (vomit()) return;
    
    if (m_movementPlanDistance == 0) planMovement();
    
    moveForward();
}

bool Zombie::isParalyzed() {
    return m_isParalyzed;
}

bool Zombie::vomit() {
    
    double vomitMinX;
    double vomitMinY;
    computeVomitCoordinates(vomitMinX, vomitMinY);
    
    return getWorld()->handleZombieVomit(*this, vomitMinX, vomitMinY);

}

Zombie::~Zombie() {
    
}

void Zombie::die() {
    if (!isAlive()) return;
    Creature::die();
    StudentWorld *world = getWorld();
    world->increaseScore(score());
    world->playSound(SOUND_ZOMBIE_DIE);
}

bool Zombie::isZombie() {
    return true;
}

void Zombie::computeVomitCoordinates(double &vomitMinX, double &vomitMinY) {
    
    vomitMinX = getX();
    vomitMinY = getY();
    
    increment(getDirection(), SPRITE_WIDTH, SPRITE_HEIGHT, vomitMinX, vomitMinY);
}

double Zombie::getMovementPlanDistance() const {
    return m_movementPlanDistance;
}
void Zombie::setMovementPlanDistance(double distance) {
    m_movementPlanDistance = distance;
}

bool Zombie::moveForward() {
    if (Creature::moveForward()) {
        decrementMovementPlanDistance();
        return true;
    } else {
        setMovementPlanDistance(0);
        return false;
    }
}

double Zombie::getStep() {
    return ZOMBIE_STEP;
}

void Zombie::decrementMovementPlanDistance() {
    if (m_movementPlanDistance == 0) return;
    m_movementPlanDistance--;
}


DumbZombie::DumbZombie(StudentWorld *world, double startX, double startY)
: Zombie(world, startX, startY) {
   
}

DumbZombie::DumbZombie(StudentWorld *world, int levelX, int levelY)
: Zombie(world, levelX, levelY) {
    
}

DumbZombie::~DumbZombie() {
    
}

int DumbZombie::score() {
    return DUMB_ZOMBIE_SCORE;
}

void DumbZombie::planMovement() {
    setMovementPlanDistance(randInt(ZOMBIE_MOVEMENT_PLAN_MIN, ZOMBIE_MOVEMENT_PLAN_MAX));
    setDirection(90 * randInt(0, 3));
}

void DumbZombie::die() {
    if (!isAlive()) return;
    Zombie::die();
    dropVaccineGoodie();
}

void DumbZombie::dropVaccineGoodie() {
    if (!getWorld()->probability(VACCINE_GOODIE_DROP_PROBABILITY)) return;
    
    int directions[] = { GraphObject::right, GraphObject::left, GraphObject::up, GraphObject::down };
    int direction = directions[randInt(0, 3)];
    double minX = getX();
    double minY = getY();
    
    increment(direction, SPRITE_WIDTH, SPRITE_HEIGHT, minX, minY);
    
    getWorld()->dropVaccineGoodie(minX, minY);
}


SmartZombie::SmartZombie(StudentWorld *world, double startX, double startY)
: Zombie(world, startX, startY) {
    
}

SmartZombie::SmartZombie(StudentWorld *world, int levelX, int levelY)
: Zombie(world, levelX, levelY) {
    
}

void SmartZombie::planMovement() {
    double minX = getX();
    double minY = getY();

    double distance;
    double personMinX;
    double personMinY;
    getWorld()->getNearestPersonCoordinates(minX, minY, distance, personMinX, personMinY);
    
    setMovementPlanDistance(randInt(ZOMBIE_MOVEMENT_PLAN_MIN, ZOMBIE_MOVEMENT_PLAN_MAX));
    
    if (distance > SMART_ZOMBIE_VISION_DISTANE * SMART_ZOMBIE_VISION_DISTANE) {
        setDirection(90 * randInt(0, 3));
    } else {
        // get closer to person
        if (minX == personMinX) {
            if (minY < personMinY) {
                setDirection(GraphObject::up);
            } else {
                setDirection(GraphObject::down);
            }
        } else if (minY == personMinY) {
            if (minX < personMinX) {
                setDirection(GraphObject::right);
            } else {
                setDirection(GraphObject::left);
            }
        } else {
            int directions[2];
            directions[0] = (minX < personMinX) ? GraphObject::right : GraphObject::left;
            directions[1] = (minY < personMinY) ? GraphObject::up : GraphObject::down;
            
            setDirection(directions[randInt(0, 1)]);
        }
    }
}

SmartZombie::~SmartZombie() {
    
}

int SmartZombie::score() {
    return SMART_ZOMBIE_SCORE;
}


Person::Person(StudentWorld *world, int imageID, int levelX, int levelY, int direction, int depth)
: Creature(world, imageID, SPRITE_WIDTH * levelX, SPRITE_HEIGHT * levelY, direction, depth) {
    m_isInfected = false;
    m_infectionCount = 0;
}

void Person::doSomething() {
    if (!isAlive()) return;
    
    if (!m_isInfected) return;
    
    m_infectionCount++;
    
    if (m_infectionCount == MAX_INFECTION_COUNT) mutate();
    
}

void Person::getSick() {
    m_isInfected = true;
}

bool Person::isPerson() {
    return true;
}

Person::~Person() {
    
}

void Person::injectVaccine() {
    if (!isSmart()) return;
    
    m_isInfected = false;
    m_infectionCount = 0;
}

int Person::getNumInfectionCount() {
    return m_infectionCount;
}

bool Person::isInfected() {
    return m_isInfected;
}


Penelope::Penelope(StudentWorld *world, int levelX, int levelY)
: Person(world, IID_PLAYER, levelX, levelY, PENELOPE_START_DIRECTION, PENELOPE_DEPTH) {
    m_didExit = false;
    m_numLandmines = 0;
    m_numFlames = 0;
    m_numVaccines = 0;
}

void Penelope::doSomething() {
    Person::doSomething();
    
    if (!isAlive()) return;
    
    handleKeyAction();
    
}

void Penelope::mutate() {
    die();
}

void Penelope::die() {
    if (!isAlive()) return;
    Creature::die();
    getWorld()->playSound(SOUND_PLAYER_DIE);
}

void Penelope::exit() {
    m_didExit = true;
}

bool Penelope::didExit() {
    return m_didExit;
}

Penelope::~Penelope() {
    
}

void Penelope::handleKeyAction() {
    int key;
    StudentWorld *world = getWorld();
    
    if (!world->getKey(key)) return;
    switch (key) {
        case KEY_PRESS_LEFT:
            handleLeftKey();
            break;
        case KEY_PRESS_RIGHT:
            handleRightKey();
            break;
        case KEY_PRESS_UP:
            handleUpKey();
            break;
        case KEY_PRESS_DOWN:
            handleDownKey();
            break;
        case KEY_PRESS_SPACE:
            handleSpaceKey();
            break;
        case KEY_PRESS_TAB:
            handleTabKey();
            break;
        case KEY_PRESS_ENTER:
            handleEnterKey();
            break;
        default:
            return;
    }
}

void Penelope::handleLeftKey() {
    setDirection(GraphObject::left);
    moveForward();
}

void Penelope::handleRightKey() {
    setDirection(GraphObject::right);
    moveForward();
}

void Penelope::handleUpKey() {
    setDirection(GraphObject::up);
    moveForward();
}

void Penelope::handleDownKey() {
    setDirection(GraphObject::down);
    moveForward();
}

void Penelope::handleSpaceKey() {
    if (m_numFlames == 0) return;
    StudentWorld *world = getWorld();
    world->generateFlames(getX(), getY(), getDirection());
    world->playSound(SOUND_PLAYER_FIRE);
    m_numFlames--;
}

void Penelope::handleTabKey() {
    if (m_numLandmines == 0) return;
    getWorld()->generateLandmine(getX(), getY());
    m_numLandmines--;
}

void Penelope::handleEnterKey() {
    injectVaccine();
}

void Penelope::getVaccineGoodie(VaccineGoodie &goodie) {
    eat(goodie);
    m_numVaccines += CHARGES_PER_VACCINE_GOODIE;
}

void Penelope::getGasCanGoodie(GasCanGoodie &goodie) {
    eat(goodie);
    m_numFlames += CHARGES_PER_GAS_CAN_GOODIE;
}

void Penelope::getLandmineGoodie(LandmineGoodie &goodie) {
    eat(goodie);
    m_numLandmines += CHARGES_PER_GAS_CAN_GOODIE;
}

void Penelope::eat(Goodie &goodie) {
    goodie.die();
    StudentWorld *world = getWorld();
    world->increaseScore(GOODIE_SCORE);
    world->playSound(SOUND_GOT_GOODIE);
    
}

bool Penelope::isSmart() {
    return true;
}

void Penelope::injectVaccine() {
    if (m_numVaccines == 0) return;
    Person::injectVaccine();
    m_numVaccines--;
}

double Penelope::getStep() {
    return PENELOPE_STEP;
}

int Penelope::getNumLandmines() {
    return m_numLandmines;
}

int Penelope::getNumFlames() {
    return m_numFlames;
}
int Penelope::getNumVaccines() {
    return m_numVaccines;
}


Citizen::Citizen(StudentWorld *world, int levelX, int levelY)
: Person(world, IID_CITIZEN, levelX, levelY, CITIZEN_START_DIRECTION, CITIZEN_DEPTH) {
    m_isParalyzed = false;
}

Citizen::~Citizen() {
    
}

void Citizen::doSomething() {
    Person::doSomething();
    
    if (!isAlive()) return;
    
    m_isParalyzed = !m_isParalyzed;
    
    if (m_isParalyzed) return;
    
    double distanceToNearestZombie;
    bool isZombieExist = getWorld()->getDistanceToNearestZombie(getX(), getY(), distanceToNearestZombie);
    
    if (approachPenelope(isZombieExist, distanceToNearestZombie)) return;
    
    if (escapeFromZombies(isZombieExist, distanceToNearestZombie)) return;
    
}

void Citizen::mutate() {
    getWorld()->handleCitizenMutation(*this);
    die();
}

void Citizen::exit() {
    StudentWorld *world = getWorld();
    world->increaseScore(EXIT_SCORE);
    world->playSound(SOUND_CITIZEN_SAVED);
    world->decrementNumCitizens();
    setDead();
}

bool Citizen::isSmart() {
    return false;
}

double Citizen::getStep() {
    return CITIZEN_STEP;
}

bool Citizen::approachPenelope(bool isZombieExist, double distanceToNearestZombie) {
    double minX = getX();
    double minY = getY();
    double penelopeMinX;
    double penelopeMinY;
    getWorld()->getPenelopeLocation(penelopeMinX, penelopeMinY);
    double distanceToPenelope = getWorld()->getDistanceToPenelope(minX, minY);
    
    if ((!isZombieExist || distanceToPenelope < distanceToNearestZombie) && distanceToPenelope <= CITIZEN_VISION_DISTANCE * CITIZEN_VISION_DISTANCE) {
        if (minX == penelopeMinX) {
            if (approachPenelopeY(penelopeMinY)) return true;
        } else if (minY == penelopeMinY) {
            if (approachPenelopeX(penelopeMinX)) return true;
        } else {
            if (approachPenelopeXY(penelopeMinX, penelopeMinY)) return true;
        }
    }
    
    return false;
}

bool Citizen::approachPenelopeX(double penelopeMinX) {
    if (getX() < penelopeMinX) {
        setDirection(GraphObject::right);
        if (moveForward()) return true;
    } else {
        setDirection(GraphObject::left);
        if (moveForward()) return true;
    }
    return false;
}

bool Citizen::approachPenelopeY(double penelopeMinY) {
    if (getY() < penelopeMinY) {
        setDirection(GraphObject::up);
        if (moveForward()) return true;
    } else {
        setDirection(GraphObject::down);
        if (moveForward()) return true;
    }
    return false;
}
bool Citizen::approachPenelopeXY(double penelopeMinX, double penelopeMinY) {
    int directions[2];
    directions[0] = (getX() < penelopeMinX) ? GraphObject::right : GraphObject::left;
    directions[1] = (getY() < penelopeMinY) ? GraphObject::up : GraphObject::down;
    
    int r = randInt(0, 1);
    setDirection(directions[r]);
    if (moveForward()) return true;
    setDirection(directions[(r + 1) % 2]);
    if (moveForward()) return true;
    
    return false;
}

bool Citizen::escapeFromZombies(bool isZombieExist, double distanceToNearestZombie) {
    if (isZombieExist && distanceToNearestZombie < CITIZEN_VISION_DISTANCE * CITIZEN_VISION_DISTANCE) {
        
        int newDirection;
        double newMinX;
        double newMinY;
        if (!findSafestDirection(distanceToNearestZombie, newDirection, newMinX, newMinY)) return false;
        
        setDirection(newDirection);
        moveTo(newMinX, newMinY);
        return true;
        
    }
    
    return false;
}

bool Citizen::checkSafety(int direction, bool &isZombieExist, double &distance, double &newMinX, double &newMinY) {
    setDirection(direction);
    
    if (canMoveForward(newMinX, newMinY)) {
        isZombieExist = getWorld()->getDistanceToNearestZombie(newMinX, newMinY, distance);
        return true;
    }
    
    return false;
}

bool Citizen::findSafestDirection(double distanceToNearestZombie, int &newDirection, double &newMinX, double &newMinY) {
    double newDistanceToZombie = distanceToNearestZombie;
    bool isFound = false;
    
    bool tempIsZombieExist;
    double tempDistance;
    double tempX;
    double tempY;
    
    int directions[] = { GraphObject::right, GraphObject::left, GraphObject::up, GraphObject::down };
    
    for (int direction : directions) {
        if (checkSafety(direction, tempIsZombieExist, tempDistance, tempX, tempY)) {
            if (tempDistance > newDistanceToZombie) {
                newDistanceToZombie = tempDistance;
                newDirection = direction;
                newMinX = tempX;
                newMinY = tempY;
                isFound = true;
            }
        }
    }
    
    return isFound;
    
}

void Citizen::die() {
    if (!isAlive()) return;
    Creature::die();
    StudentWorld *world = getWorld();
    world->decrementNumCitizens();
    world->increaseScore(CITIZEN_DEAD_PENALTY_SCORE);
    world->playSound(SOUND_CITIZEN_DIE);
}

void Citizen::getSick() {
    if (isInfected()) return;
    Person::getSick();
    getWorld()->playSound(SOUND_CITIZEN_INFECTED);
}

