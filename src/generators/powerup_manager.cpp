#include "generators/powerup_manager.h"

PowerupManager::PowerupManager()
{
}

PowerupManager::~PowerupManager()
{
    clear();
}

void PowerupManager::addPowerup(Powerup *powerup)
{
    if (powerup)
    {
        activePowerups.push_back(ActivePowerup(powerup, powerup->getDuration()));
    }
}

void PowerupManager::update(float deltaTime)
{
    for (auto it = activePowerups.begin(); it != activePowerups.end();)
    {
        if (!it->isActivated)
        {
            it->powerup->activate();
            it->isActivated = true;
        }

        it->timeRemaining -= deltaTime;

        if (it->timeRemaining <= 0.0f)
        {
            it->powerup->deactivate();
            it = activePowerups.erase(it);
        }
        else
        {
            ++it;
        }
    }
}

void PowerupManager::clear()
{
    for (auto &active : activePowerups)
    {
        if (active.isActivated)
        {
            active.powerup->deactivate();
        }
    }
    activePowerups.clear();
}
