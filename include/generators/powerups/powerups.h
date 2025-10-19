#ifndef POWERUPS_H
#define POWERUPS_H

#include "physics/objects.h"
#include <GL/glut.h>

#define POWERUP_SIZE 0.06f

enum PowerupType
{
    POWERUP_JETPACK,
    POWERUP_LAVA_FREEZE,
    POWERUP_SHIELD
};

class Powerup : public StaticObject
{
protected:
    PowerupType type;
    float spawnRate;
    float duration;
    bool isActive;
    bool isCollected;

public:
    Powerup(float x, float y, PowerupType type, float spawnRate, float duration, void (*drawFunc)(float, float));
    virtual ~Powerup();

    PowerupType getType() const { return type; }
    float getSpawnRate() const { return spawnRate; }
    float getDuration() const { return duration; }
    bool getIsActive() const { return isActive; }
    bool getIsCollected() const { return isCollected; }
    void setCollected(bool collected) { isCollected = collected; }

    virtual void activate() = 0;
    virtual void deactivate() = 0;
};

#endif
