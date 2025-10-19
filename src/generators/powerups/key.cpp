#include "generators/powerups/key.h"
#include <iostream>

void Key::defaultDrawFunc(float x, float y)
{
    glColor3f(KEY_COLOR_R, KEY_COLOR_G, KEY_COLOR_B);
    glBegin(GL_TRIANGLES);
    glVertex2f(x - KEY_SIZE / 2.0f, y - KEY_SIZE / 4.0f);
    glVertex2f(x + KEY_SIZE / 2.0f, y - KEY_SIZE / 4.0f);
    glVertex2f(x, y + KEY_SIZE / 2.0f);
    glEnd();
    glBegin(GL_QUADS);
    glVertex2f(x - KEY_SIZE / 4.0f, y - KEY_SIZE / 4.0f);
    glVertex2f(x + KEY_SIZE / 4.0f, y - KEY_SIZE / 4.0f);
    glVertex2f(x + KEY_SIZE / 4.0f, y - KEY_SIZE / 2.0f);
    glVertex2f(x - KEY_SIZE / 4.0f, y - KEY_SIZE / 2.0f);
    glEnd();
}

Key::Key(float x, float y, Player *player)
    : Powerup(x, y, POWERUP_KEY, KEY_SPAWN_RATE, 0.0f, Key::defaultDrawFunc)
{
}

Key::Key(float x, float y, Player *player, void (*drawFunc)(float, float))
    : Powerup(x, y, POWERUP_KEY, KEY_SPAWN_RATE, 0.0f, drawFunc), player(player)
{
}

Key::~Key()
{
}

void Key::activate()
{
    std::cout << "Key collected!" << std::endl;
    if (player && !isActive)
    {
        isActive = true;
        player->addKey();
    }
}

void Key::deactivate()
{
    isActive = false;
}