#include "generators/powerups/powerups.h"

Powerup::Powerup(float x, float y, PowerupType type, float spawnRate, float duration, void (*drawFunc)(float, float))
    : StaticObject(x, y, drawFunc), type(type), spawnRate(spawnRate), duration(duration), isActive(false), isCollected(false)
{
    setCollisionBox(POWERUP_SIZE * 2.0f, POWERUP_SIZE * 2.0f);
}

Powerup::~Powerup()
{
}
