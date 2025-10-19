#include "generators/powerups/super_key.h"
#include "player.h"
#include <cmath>

void SuperKey::defaultDrawFunc(float x, float y)
{
    glBegin(GL_QUADS);
    glColor3f(SUPER_KEY_COLOR_R, SUPER_KEY_COLOR_G, SUPER_KEY_COLOR_B);
    glVertex2f(x - SUPER_KEY_SIZE, y - SUPER_KEY_SIZE);
    glVertex2f(x + SUPER_KEY_SIZE, y - SUPER_KEY_SIZE);
    glVertex2f(x + SUPER_KEY_SIZE, y + SUPER_KEY_SIZE);
    glVertex2f(x - SUPER_KEY_SIZE, y + SUPER_KEY_SIZE);
    glEnd();

    glBegin(GL_TRIANGLES);
    glColor3f(1.0f, 1.0f, 1.0f);
    for (int i = 0; i < 8; i++)
    {
        float angle = 2.0f * 3.14159f * i / 8.0f;
        float nextAngle = 2.0f * 3.14159f * (i + 1) / 8.0f;
        float cx = x + SUPER_KEY_SIZE * 0.6f * cos(angle);
        float cy = y + SUPER_KEY_SIZE * 0.6f * sin(angle);
        float nx = x + SUPER_KEY_SIZE * 0.6f * cos(nextAngle);
        float ny = y + SUPER_KEY_SIZE * 0.6f * sin(nextAngle);
        glVertex2f(x, y);
        glVertex2f(cx, cy);
        glVertex2f(nx, ny);
    }
    glEnd();
}

SuperKey::SuperKey(float x, float y, Player *player)
    : Powerup(x, y, POWERUP_SUPER_KEY, SUPER_KEY_SPAWN_RATE, 0.0f, defaultDrawFunc), player(player)
{
    setCollisionBox(SUPER_KEY_SIZE * 2.0f, SUPER_KEY_SIZE * 2.0f);
}

SuperKey::SuperKey(float x, float y, Player *player, void (*drawFunc)(float, float))
    : Powerup(x, y, POWERUP_SUPER_KEY, SUPER_KEY_SPAWN_RATE, 0.0f, drawFunc), player(player)
{
    setCollisionBox(SUPER_KEY_SIZE * 2.0f, SUPER_KEY_SIZE * 2.0f);
}

SuperKey::~SuperKey()
{
}

void SuperKey::activate()
{
    if (player && !isActive)
    {
        isActive = true;
        player->setSuperKey(true);
    }
}

void SuperKey::deactivate()
{
    isActive = false;
}
