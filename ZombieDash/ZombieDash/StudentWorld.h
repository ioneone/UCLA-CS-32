#ifndef STUDENTWORLD_H_
#define STUDENTWORLD_H_

#include "GameWorld.h"
#include "Level.h"
#include <string>
#include <vector>

class Actor;
class Penelope;
class Vomit;
class Zombie;
class VaccineGoodie;
class LandmineGoodie;
class Pit;
class GasCanGoodie;
class Landmine;
class Flame;
class Exit;
class DumbZombie;
class SmartZombie;
class Citizen;

class StudentWorld : public GameWorld
{
public:
    StudentWorld(std::string assetPath);
    virtual int init();
    virtual int move();
    virtual void cleanUp();
    virtual ~StudentWorld();
    
    void handleVomit(Vomit &vomit);
    void handleVaccineGoodie(VaccineGoodie &goodie);
    void handleLandmineGoodie(LandmineGoodie &goodie);
    void handlePit(Pit &pit);
    void handleGasCanGoodie(GasCanGoodie &goodie);
    void handleLandmineExplosion(Landmine &landmine);
    void handleFlame(Flame &flame);
    void handleExit(Exit &exit);
    
    bool handleCanMoveTo(Actor &actor, double minX, double minY);
    bool handleZombieVomit(Zombie &zombie, double vomitMinX, double vomitMinY);
    void getNearestPersonCoordinates(double x, double y, double &distance, double &personX, double &personY);
    void handleCitizenMutation(Citizen &citizen);
    void getPenelopeLocation(double &minX, double &minY);
    double getDistanceToPenelope(double minX, double minY);
    bool getDistanceToNearestZombie(double minX, double minY, double &distance);
    bool hasOverlapWithActorsOrPlayer(Actor &actor);
    bool hasOverlapWithActorsOrPlayer(double minX, double minY);
    bool hasOverlapWithFlameBlockable(double minX, double minY);
    void generateFlames(double minX, double minY, int direction);
    void generateLandmine(double minX, double minY);
    void decrementNumCitizens();
    void dropVaccineGoodie(double minX, double minY);
    
    bool probability(double probability);
    
private:
    bool loadLevelFile(Level &level, int &status) const;
    void handleMazeEntry(Level &level, int levelX, int levelY);
    
    // reutrn true if two bounding boxes intersect
    bool intersect(double minX, double minY, Actor const &other) const;
    
    // return true of two bounding boxes "overlap"
    bool overlap(double minX, double minY, Actor const &other) const;
    
    void removeDeadActors();
    void updateDisplayText();
    
    std::vector<Actor*> m_actors;
    Penelope *m_player;
    int m_numCitizens;
};

#endif // STUDENTWORLD_H_
