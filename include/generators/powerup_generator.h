#ifndef POWERUP_GENERATOR_H
#define POWERUP_GENERATOR_H

#include "generators/powerups/powerups.h"
#include "generators/powerups/jetpack.h"
#include "generators/powerups/lava_freeze.h"
#include "generators/powerups/shield.h"
#include "platform.h"
#include <vector>

#define POWERUP_CHECK_DISTANCE 0.2f

class Player;
class Lava;

class PowerupGenerator
{
private:
    Player *player;
    Lava *lava;
    float lastCheckedHeight;
    float checkInterval;

    bool shouldSpawnPowerup(float spawnRate);
    PowerupType selectRandomPowerup();

public:
    PowerupGenerator(Player *player, Lava *lava, float checkInterval = 1.0f);
    ~PowerupGenerator();

    void generatePowerups(std::vector<Powerup *> &powerups, std::vector<Platform *> &platforms, float cameraY);
};

#endif
