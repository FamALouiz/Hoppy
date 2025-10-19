#include "generators/powerups/shield.h"
#include "player.h"
#include <cmath>
#include <iostream>

void Shield::defaultDrawFunc(float x, float y)
{
    glBegin(GL_QUADS);
    glColor3f(SHIELD_COLOR_R, SHIELD_COLOR_G, SHIELD_COLOR_B);
    glVertex2f(x - POWERUP_SIZE, y - POWERUP_SIZE);
    glVertex2f(x + POWERUP_SIZE, y - POWERUP_SIZE);
    glVertex2f(x + POWERUP_SIZE, y + POWERUP_SIZE);
    glVertex2f(x - POWERUP_SIZE, y + POWERUP_SIZE);
    glEnd();

    glBegin(GL_POLYGON);
    glColor3f(1.0f, 1.0f, 1.0f);
    int segments = 8;
    for (int i = 0; i < segments; i++)
    {
        float angle = 2.0f * 3.14159f * i / segments;
        float cx = x + POWERUP_SIZE * 0.5f * cos(angle);
        float cy = y + POWERUP_SIZE * 0.5f * sin(angle);
        glVertex2f(cx, cy);
    }
    glEnd();
}

Shield::Shield(float x, float y, Player *player)
    : Powerup(x, y, POWERUP_SHIELD, SHIELD_SPAWN_RATE, SHIELD_DURATION, defaultDrawFunc), player(player)
{
}

Shield::Shield(float x, float y, Player *player, void (*drawFunc)(float, float))
    : Powerup(x, y, POWERUP_SHIELD, SHIELD_SPAWN_RATE, SHIELD_DURATION, drawFunc), player(player)
{
}

Shield::~Shield()
{
}

void Shield::activate()
{
    if (player && !isActive)
    {
        isActive = true;
        player->setInvincible(true);
        std::cout << "Shield activated!" << std::endl;
    }
}

void Shield::deactivate()
{
    if (player && isActive)
    {
        isActive = false;
        player->setInvincible(false);
        std::cout << "Shield deactivated!" << std::endl;
    }
}
