#include "generators/powerups/jetpack.h"
#include "player.h"
#include <iostream>

void Jetpack::defaultDrawFunc(float x, float y)
{
    glBegin(GL_QUADS);
    glColor3f(JETPACK_COLOR_R, JETPACK_COLOR_G, JETPACK_COLOR_B);
    glVertex2f(x - POWERUP_SIZE, y - POWERUP_SIZE);
    glVertex2f(x + POWERUP_SIZE, y - POWERUP_SIZE);
    glVertex2f(x + POWERUP_SIZE, y + POWERUP_SIZE);
    glVertex2f(x - POWERUP_SIZE, y + POWERUP_SIZE);
    glEnd();

    glBegin(GL_TRIANGLES);
    glColor3f(1.0f, 0.8f, 0.2f);
    glVertex2f(x - POWERUP_SIZE * 0.5f, y - POWERUP_SIZE);
    glVertex2f(x, y - POWERUP_SIZE * 1.5f);
    glVertex2f(x + POWERUP_SIZE * 0.5f, y - POWERUP_SIZE);
    glEnd();
}

Jetpack::Jetpack(float x, float y, Player *player)
    : Powerup(x, y, POWERUP_JETPACK, JETPACK_SPAWN_RATE, JETPACK_DURATION, defaultDrawFunc), player(player)
{
}

Jetpack::Jetpack(float x, float y, Player *player, void (*drawFunc)(float, float))
    : Powerup(x, y, POWERUP_JETPACK, JETPACK_SPAWN_RATE, JETPACK_DURATION, drawFunc), player(player)
{
}

Jetpack::~Jetpack()
{
}

void Jetpack::activate()
{
    if (player && !isActive)
    {
        isActive = true;
        player->setUsingJetpack(true);
        player->setVelocity(player->getVelocityX(), JETPACK_SPEED);
        player->setAcceleration(0.0f, 0.0f);
        std::cout << "Jetpack activated!" << std::endl;
    }
}

void Jetpack::deactivate()
{
    if (player && isActive)
    {
        isActive = false;
        player->setUsingJetpack(false);
        player->setAcceleration(0.0f, GRAVITY);
        std::cout << "Jetpack deactivated!" << std::endl;
    }
}
