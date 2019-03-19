#include "StudentWorld.h"
#include "Actor.h"
#include <string>
#include <sstream>
#include <iomanip>
using namespace std;

GameWorld* createStudentWorld(string assetPath)
{
	return new StudentWorld(assetPath);
}

StudentWorld::StudentWorld(string assetPath)
: GameWorld(assetPath)
{
    m_player = nullptr;
    m_numCitizens = 0;
}

StudentWorld::~StudentWorld() {
    cleanUp();
}

int StudentWorld::init()
{

    Level level(assetPath());
    
    int status;
    if (!loadLevelFile(level, status)) return status;
    
    for (int levelX = 0; levelX < LEVEL_WIDTH; levelX++)
        for (int levelY = 0; levelY < LEVEL_HEIGHT; levelY++)
            handleMazeEntry(level, levelX, levelY);
    
    return GWSTATUS_CONTINUE_GAME;
}

int StudentWorld::move()
{
        
    m_player->doSomething();
    
    for (Actor *actor : m_actors) {
        actor->doSomething();
        
        if (!m_player->isAlive()) {
            decLives();
            return GWSTATUS_PLAYER_DIED;
        }
        
        if (m_player->didExit()) {
            playSound(SOUND_LEVEL_FINISHED);
            return GWSTATUS_FINISHED_LEVEL;
        }
        
    }
    
    removeDeadActors();
    
    updateDisplayText();
        
    return GWSTATUS_CONTINUE_GAME;
}

void StudentWorld::cleanUp()
{
    for (auto it = m_actors.begin(); it != m_actors.end();) {
        delete *it;
        m_actors.erase(it);
    }
    
    if (m_player) delete m_player;
    m_player = nullptr;
    m_numCitizens = 0;
}

bool StudentWorld::loadLevelFile(Level &level, int &status) const {
    
    if (getLevel() == 100) return GWSTATUS_PLAYER_WON;
    
    ostringstream levelFile;
    levelFile.fill('0');
    levelFile << "level" << std::setw(2) << getLevel() << ".txt";
    Level::LoadResult result = level.loadLevel(levelFile.str());
    
    if (result == Level::load_fail_file_not_found) {
        cerr << "Cannot find " << levelFile.str() << " data file" << endl;
        status = (getLevel() > 1) ? GWSTATUS_PLAYER_WON : GWSTATUS_LEVEL_ERROR;
    }
    else if (result == Level::load_fail_bad_format) {
        cerr << "Your level was improperly formatted" << endl;
        status = GWSTATUS_LEVEL_ERROR;
    }
    else if (result == Level::load_success) {
        cerr << "Successfully loaded level" << endl;
        return true;
    }
    
    return false;
}

void StudentWorld::handleMazeEntry(Level &level, int levelX, int levelY) {
    Level::MazeEntry entry = level.getContentsOf(levelX, levelY);
    switch (entry) {
        case Level::empty:
            //cout << "Location " << levelX << ", " << levelY << " is empty" << endl;
            break;
        case Level::player:
            m_player = new Penelope(this, levelX, levelY);
            //cout << "Location " << levelX << ", " << levelY << " is where Penelope starts" << endl;
            break;
        case Level::dumb_zombie:
            m_actors.push_back(new DumbZombie(this, levelX, levelY));
            break;
        case Level::smart_zombie:
            m_actors.push_back(new SmartZombie(this, levelX, levelY));
            break;
        case Level::citizen:
            m_actors.push_back(new Citizen(this, levelX, levelY));
            m_numCitizens++;
            break;
        case Level::wall:
            m_actors.push_back(new Wall(this, levelX, levelY));
            //cout << "Location " << levelX << ", " << levelY << " holds a Wall" << endl;
            break;
        case Level::exit:
            m_actors.push_back(new Exit(this, levelX, levelY));
            break;
        case Level::pit:
            m_actors.push_back(new Pit(this, levelX, levelY));
            break;
        case Level::vaccine_goodie:
            m_actors.push_back(new VaccineGoodie(this, levelX, levelY));
            break;
        case Level::gas_can_goodie:
            m_actors.push_back(new GasCanGoodie(this, levelX, levelY));
            break;
        case Level::landmine_goodie:
            m_actors.push_back(new LandmineGoodie(this, levelX, levelY));
            break;
        default:
            break;
    }
}

void StudentWorld::handleVomit(Vomit &vomit) {
    double minX = vomit.getX();
    double minY = vomit.getY();
    
    if (overlap(minX, minY, *m_player)) {
        m_player->getSick();
    }
    
    for (Actor *actor : m_actors) {
        if (overlap(minX, minY, *actor)) {
            actor->getSick();
        }
    }
}

bool StudentWorld::handleZombieVomit(Zombie &zombie, double vomitMinX, double vomitMinY) {
    
    if (overlap(vomitMinX, vomitMinY, *m_player)) {
        playSound(SOUND_ZOMBIE_VOMIT);
        if (probability(VOMIT_PROBABILITY)) {
            m_actors.push_back(new Vomit(this, vomitMinX, vomitMinY, zombie.getDirection()));
            return true;
        }
    }
    
    for (Actor *actor : m_actors) {
        if (actor->isPerson() && overlap(vomitMinX, vomitMinY, *actor)) {
            playSound(SOUND_ZOMBIE_VOMIT);
            if (probability(VOMIT_PROBABILITY)) {
                m_actors.push_back(new Vomit(this, vomitMinX, vomitMinY, zombie.getDirection()));
                return true;
            }
        }
    }
    
    return false;
}

bool StudentWorld::intersect(double minX, double minY, Actor const &other) const {
    
    double maxX = minX + SPRITE_WIDTH - 1;
    double maxY = minY + SPRITE_HEIGHT - 1;
    
    double otherMinX = other.getX();
    double otherMinY = other.getY();
    double otherMaxX = other.getX() + SPRITE_WIDTH - 1;
    double otherMaxY = other.getY() + SPRITE_HEIGHT - 1;
    
    double minMaxX = (maxX < otherMaxX) ? maxX : otherMaxX;
    double maxMinX = (minX > otherMinX) ? minX : otherMinX;
    double minMaxY = (maxY < otherMaxY) ? maxY : otherMaxY;
    double maxMinY = (minY > otherMinY) ? minY : otherMinY;
    
    double xIntersect = (minMaxX - maxMinX > 0) ? minMaxX - maxMinX : 0;
    double yIntersect = (minMaxY - maxMinY > 0) ? minMaxY - maxMinY : 0;
    
    return xIntersect > 0 && yIntersect > 0;
}

bool StudentWorld::overlap(double minX, double minY, Actor const &other) const {
    
    double dx = minX - other.getX();
    double dy = minY - other.getY();
    
    return dx * dx + dy * dy <= OVERLAP_EUCLIDEAN_DISTANCE * OVERLAP_EUCLIDEAN_DISTANCE;
    
}

void StudentWorld::handleVaccineGoodie(VaccineGoodie &goodie) {
    if (overlap(goodie.getX(), goodie.getY(), *m_player)) {
        m_player->getVaccineGoodie(goodie);
    }
}

void StudentWorld::handleLandmineGoodie(LandmineGoodie &goodie) {
    if (overlap(goodie.getX(), goodie.getY(), *m_player)) {
        m_player->getLandmineGoodie(goodie);
    }
}

void StudentWorld::handlePit(Pit &pit) {

    double minX = pit.getX();
    double minY = pit.getY();
    
    if (overlap(minX, minY, *m_player)) {
        m_player->die();
    }
    
    for (Actor *actor : m_actors) {
        if (overlap(minX, minY, *actor)) {
            actor->die();
        }
    }
}

bool StudentWorld::handleCanMoveTo(Actor &actor, double minX, double minY) {
    
    if (m_player != &actor && intersect(minX, minY, *m_player)) return false;
    
    for (Actor *a : m_actors) {
        if (a == &actor) continue;
        if (!a->isOverlappable() && intersect(minX, minY, *a)) {
            return false;
        }
    }
    
    return true;
}

void StudentWorld::handleGasCanGoodie(GasCanGoodie &goodie) {
    if (overlap(goodie.getX(), goodie.getY(), *m_player)) {
        m_player->getGasCanGoodie(goodie);
    }
}


bool StudentWorld::hasOverlapWithActorsOrPlayer(Actor &actor) {
    double minX = actor.getX();
    double minY = actor.getY();
    
    if (m_player != &actor && overlap(minX, minY, *m_player)) {
        return true;
    }
    
    for (Actor *a : m_actors) {
        if (a != &actor && overlap(minX, minY, *a)) {
            return true;
        }
    }
    
    return false;

}

bool StudentWorld::hasOverlapWithActorsOrPlayer(double minX, double minY) {
    
    if (overlap(minX, minY, *m_player)) {
        return true;
    }
    
    for (Actor *a : m_actors) {
        if (overlap(minX, minY, *a)) {
            return true;
        }
    }
    
    return false;
    
}

void StudentWorld::handleLandmineExplosion(Landmine &landmine) {
    double minX = landmine.getX();
    double minY = landmine.getY();
    
    m_actors.push_back(new Flame(this, minX, minY, GraphObject::right));
    m_actors.push_back(new Flame(this, minX + SPRITE_WIDTH, minY, GraphObject::right));
    m_actors.push_back(new Flame(this, minX + SPRITE_WIDTH, minY + SPRITE_HEIGHT, (GraphObject::right + GraphObject::up) / 2));
    m_actors.push_back(new Flame(this, minX, minY + SPRITE_HEIGHT, GraphObject::up));
    m_actors.push_back(new Flame(this, minX - SPRITE_WIDTH, minY + SPRITE_HEIGHT, (GraphObject::left + GraphObject::up) / 2));
    m_actors.push_back(new Flame(this, minX - SPRITE_WIDTH, minY, GraphObject::left));
    m_actors.push_back(new Flame(this, minX - SPRITE_WIDTH, minY - SPRITE_HEIGHT, (GraphObject::left + GraphObject::down) / 2));
    m_actors.push_back(new Flame(this, minX, minY - SPRITE_HEIGHT, GraphObject::down));
    m_actors.push_back(new Flame(this, minX + SPRITE_WIDTH, minY - SPRITE_HEIGHT, (GraphObject::right + GraphObject::down) / 2));
    
    m_actors.push_back(new Pit(this, minX, minY));
}

void StudentWorld::handleFlame(Flame &flame) {
    double minX = flame.getX();
    double minY = flame.getY();
    
    if (overlap(minX, minY, *m_player)) {
        m_player->die();
    }
    
    for (Actor *actor : m_actors) {
        if (actor->isFlammable() && overlap(minX, minY, *actor)) {
            actor->die();
        }
    }
}

void StudentWorld::handleExit(Exit &exit) {
    double minX = exit.getX();
    double minY = exit.getY();
    
    if (overlap(minX, minY, *m_player) && m_numCitizens == 0) {
        m_player->exit();
    }
    
    for (Actor *actor : m_actors) {
        if (actor->isPerson() && overlap(minX, minY, *actor)) {
            actor->exit();
        }
    }
}

void StudentWorld::getNearestPersonCoordinates(double x, double y, double &distance, double &personX, double &personY) {
    Actor *nearestPerson = m_player;
    double dx = x - m_player->getX();
    double dy = y - m_player->getY();
    double d;
    double nearestDistance = dx * dx + dy * dy;
    
    for (Actor *actor : m_actors) {
        if (actor->isPerson()) {
            dx = x - actor->getX();
            dy = y - actor->getY();
            d = dx * dx + dy * dy;
            if (d < nearestDistance) {
                nearestDistance = d;
                nearestPerson = actor;
            }
        }
    }
    
    distance = nearestDistance;
    personX = nearestPerson->getX();
    personY = nearestPerson->getY();
    
}

void StudentWorld::removeDeadActors() {
    for (auto it = m_actors.begin(); it != m_actors.end();) {
        if (!(*it)->isAlive()) {
            delete *it;
            m_actors.erase(it);
        } else {
            it++;
        }
    }
}

void StudentWorld::updateDisplayText() {
    ostringstream displayText;
    string doubleSpaces = "  ";
    
    displayText.fill('0');
    if (getScore() >= 0) {
        displayText << doubleSpaces << "Score: " << std::setw(6) << getScore() << doubleSpaces;
    } else {
        displayText << doubleSpaces << "Score: -" << std::setw(5) << -getScore() << doubleSpaces;
    }
    
    displayText.fill(' ');
    displayText << "Level: " << std::setw(2) << getLevel() << doubleSpaces;
    displayText << "Lives: " << std::setw(1) << getLives() << doubleSpaces;
    displayText << "Vaccines: " << std::setw(1) << m_player->getNumVaccines() << doubleSpaces;
    displayText << "Flames: " << std::setw(2) << m_player->getNumFlames() << doubleSpaces;
    displayText << "Mines: " << std::setw(1) << m_player->getNumLandmines() << doubleSpaces;
    displayText << "Infected: " << std::setw(1) << m_player->getNumInfectionCount() << doubleSpaces;
    setGameStatText(displayText.str());
}

bool StudentWorld::probability(double probability) {
    if (probability >= 1) return true;
    if (probability <= 0) return false;
    
    return randInt(0, 100) < probability * 100;
}

void StudentWorld::handleCitizenMutation(Citizen &citizen) {
    if (probability(DUMB_ZOMBIE_PROBABILITY)) {
        m_actors.push_back(new DumbZombie(this, citizen.getX(), citizen.getY()));
    } else {
        m_actors.push_back(new SmartZombie(this, citizen.getX(), citizen.getY()));
    }
}

void StudentWorld::getPenelopeLocation(double &minX, double &minY) {
    minX = m_player->getX();
    minY = m_player->getY();
}


bool StudentWorld::getDistanceToNearestZombie(double minX, double minY, double &distance) {
    Actor *nearestZombie = nullptr;
    double nearestDistance = 0;
    double d;
    double dx;
    double dy;
    for (Actor *actor : m_actors) {
        if (!actor->isZombie()) continue;
        
        if (nearestZombie == nullptr) {
            nearestZombie = actor;
            dx = minX - nearestZombie->getX();
            dy = minY - nearestZombie->getY();
            nearestDistance = dx * dx + dy * dy;
        } else {
            dx = minX - actor->getX();
            dy = minY - actor->getY();
            d = dx * dx + dy * dy;
            if (d < nearestDistance) {
                nearestDistance = d;
                nearestZombie = actor;
            }
        }
    }
    
    if (nearestZombie != nullptr) {
        distance = nearestDistance;
    }
    
    return nearestZombie != nullptr;
}

double StudentWorld::getDistanceToPenelope(double minX, double minY) {
    double dx = minX - m_player->getX();
    double dy = minY - m_player->getY();
    
    return dx * dx + dy * dy;
}

void StudentWorld::generateFlames(double minX, double minY, int direction) {
    int minXs[3];
    int minYs[3];
    switch (direction) {
        case GraphObject::right:
            for (int i = 0; i < 3; i++) {
                minXs[i] = minX + (i + 1) * SPRITE_WIDTH;
                minYs[i] = minY;
            }
            break;
        case GraphObject::left:
            for (int i = 0; i < 3; i++) {
                minXs[i] = minX - (i + 1) * SPRITE_WIDTH;
                minYs[i] = minY;
            }
            break;
        case GraphObject::up:
            for (int i = 0; i < 3; i++) {
                minXs[i] = minX;
                minYs[i] = minY + (i + 1) * SPRITE_HEIGHT;
            }
            break;
        case GraphObject::down:
            for (int i = 0; i < 3; i++) {
                minXs[i] = minX;
                minYs[i] = minY - (i + 1) * SPRITE_HEIGHT;
            }
            break;
        default:
            break;
    }
    
    for (int i = 0; i < 3; i++) {
        if (hasOverlapWithFlameBlockable(minXs[i], minYs[i])) break;
        m_actors.push_back(new Flame(this, minXs[i], minYs[i], direction));
    }
}

void StudentWorld::generateLandmine(double minX, double minY) {
    m_actors.push_back(new Landmine(this, minX, minY));
}

bool StudentWorld::hasOverlapWithFlameBlockable(double minX, double minY) {
    
    for (Actor *a : m_actors) {
        if (a->isFlameBlockable() && overlap(minX, minY, *a)) {
            return true;
        }
    }
    
    return false;
}

void StudentWorld::decrementNumCitizens() {
    m_numCitizens--;
}

void StudentWorld::dropVaccineGoodie(double minX, double minY) {
    if (hasOverlapWithActorsOrPlayer(minX, minY)) return;
    
    m_actors.push_back(new VaccineGoodie(this, minX, minY));
    
}
