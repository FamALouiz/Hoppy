#include "generators/powerups/jetpack.h"
#include "player.h"
#include "stb_image.h"
#include <iostream>

GLuint Jetpack::texture = 0;
bool Jetpack::textureLoaded = false;

void Jetpack::loadTexture()
{
    if (textureLoaded)
        return;

    int width, height, channels;
    unsigned char *data = stbi_load("C:\\Users\\fam\\OneDrive\\Desktop\\GIU\\Semester 7\\Graphics\\Hoppy\\assets\\sprites\\jetpack.png", &width, &height, &channels, 4);

    if (data)
    {
        glGenTextures(1, &texture);
        glBindTexture(GL_TEXTURE_2D, texture);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
        stbi_image_free(data);
        textureLoaded = true;
    }
    else
    {
        std::cerr << "Failed to load jetpack texture: " << stbi_failure_reason() << std::endl;
    }
}

void Jetpack::defaultDrawFunc(float x, float y)
{
    if (!textureLoaded)
    {
        loadTexture();
    }

    if (textureLoaded)
    {
        glEnable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D, texture);
        glColor4f(1.0f, 1.0f, 1.0f, 1.0f);

        glBegin(GL_QUADS);
        glTexCoord2f(0.0f, 1.0f);
        glVertex2f(x - POWERUP_SIZE, y - POWERUP_SIZE);
        glTexCoord2f(1.0f, 1.0f);
        glVertex2f(x + POWERUP_SIZE, y - POWERUP_SIZE);
        glTexCoord2f(1.0f, 0.0f);
        glVertex2f(x + POWERUP_SIZE, y + POWERUP_SIZE);
        glTexCoord2f(0.0f, 0.0f);
        glVertex2f(x - POWERUP_SIZE, y + POWERUP_SIZE);
        glEnd();

        glDisable(GL_TEXTURE_2D);
    }
    else
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
