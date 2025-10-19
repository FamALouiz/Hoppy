#ifndef POWERUP_MANAGER_H
#define POWERUP_MANAGER_H

#include "generators/powerups/powerups.h"
#include <vector>

struct ActivePowerup
{
    Powerup *powerup;
    float timeRemaining;
    bool isActivated;

    ActivePowerup(Powerup *p, float time) : powerup(p), timeRemaining(time), isActivated(false) {}
};

class PowerupManager
{
private:
    std::vector<ActivePowerup> activePowerups;

public:
    PowerupManager();
    ~PowerupManager();

    void addPowerup(Powerup *powerup);
    void update(float deltaTime);
    void clear();
};

#endif
