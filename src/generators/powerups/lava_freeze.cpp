#include "generators/powerups/lava_freeze.h"
#include "lava.h"
#include <iostream>

void LavaFreeze::defaultDrawFunc(float x, float y)
{
    glBegin(GL_QUADS);
    glColor3f(LAVA_FREEZE_COLOR_R, LAVA_FREEZE_COLOR_G, LAVA_FREEZE_COLOR_B);
    glVertex2f(x - POWERUP_SIZE, y - POWERUP_SIZE);
    glVertex2f(x + POWERUP_SIZE, y - POWERUP_SIZE);
    glVertex2f(x + POWERUP_SIZE, y + POWERUP_SIZE);
    glVertex2f(x - POWERUP_SIZE, y + POWERUP_SIZE);
    glEnd();

    glBegin(GL_TRIANGLES);
    glColor3f(1.0f, 1.0f, 1.0f);
    glVertex2f(x, y + POWERUP_SIZE * 0.5f);
    glVertex2f(x - POWERUP_SIZE * 0.4f, y - POWERUP_SIZE * 0.3f);
    glVertex2f(x + POWERUP_SIZE * 0.4f, y - POWERUP_SIZE * 0.3f);
    glEnd();
}

LavaFreeze::LavaFreeze(float x, float y, Lava *lava)
    : Powerup(x, y, POWERUP_LAVA_FREEZE, LAVA_FREEZE_SPAWN_RATE, LAVA_FREEZE_DURATION, defaultDrawFunc),
      lava(lava), savedSpeed(0.0f), savedAcceleration(0.0f)
{
}

LavaFreeze::LavaFreeze(float x, float y, Lava *lava, void (*drawFunc)(float, float))
    : Powerup(x, y, POWERUP_LAVA_FREEZE, LAVA_FREEZE_SPAWN_RATE, LAVA_FREEZE_DURATION, drawFunc),
      lava(lava), savedSpeed(0.0f), savedAcceleration(0.0f)
{
}

LavaFreeze::~LavaFreeze()
{
}

void LavaFreeze::activate()
{
    if (lava && !isActive)
    {
        isActive = true;
        savedSpeed = lava->getCurrentSpeed();
        savedAcceleration = lava->getAccelerationY();
        std::cout << "Saved lava speed: " << savedSpeed << ", acceleration: " << savedAcceleration << std::endl;
        lava->setVelocity(0.0f, 0.0f);
        lava->setAcceleration(0.0f, 0.0f);
        std::cout << "Lava freeze activated!" << std::endl;
    }
}

void LavaFreeze::deactivate()
{
    if (lava && isActive)
    {
        isActive = false;
        lava->setVelocity(0.0f, savedSpeed);
        lava->setAcceleration(0.0f, savedAcceleration);
        std::cout << "Lava freeze deactivated!" << std::endl;
    }
}
