#include <GL/glut.h>
#include "screens/main_screen.h"
#include "physics/core.h"
#include <iostream>

MainScreen::MainScreen() : platformGenerator(nullptr), meteorGenerator(nullptr), player(nullptr), lava(nullptr)
{
}

MainScreen::~MainScreen()
{
    if (player)
    {
        delete player;
        player = nullptr;
    }

    if (lava)
    {
        delete lava;
        lava = nullptr;
    }

    for (PhysicsObject *obj : objects)
    {
        delete obj;
    }
    objects.clear();

    for (PhysicsObject *meteor : meteors)
    {
        delete meteor;
    }
    meteors.clear();

    for (Platform *platform : platforms)
    {
        delete platform;
    }
    platforms.clear();

    if (platformGenerator)
    {
        delete platformGenerator;
        platformGenerator = nullptr;
    }

    if (meteorGenerator)
    {
        delete meteorGenerator;
        meteorGenerator = nullptr;
    }
}

void MainScreen::init()
{
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-1.0, 1.0, -1.0, 1.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    player = new Player(0.0f, 0.0f);

    Platform *ground = new Platform(0.0f, -0.8f);
    addPlatform(ground);

    auto platformDrawFunc = [](float x, float y)
    {
        glBegin(GL_QUADS);
        glColor3f(PLATFORM_COLOR_R, PLATFORM_COLOR_G, PLATFORM_COLOR_B);
        glVertex2f(x - PLATFORM_WIDTH / 2.0f, y - PLATFORM_HEIGHT / 2.0f);
        glVertex2f(x + PLATFORM_WIDTH / 2.0f, y - PLATFORM_HEIGHT / 2.0f);
        glVertex2f(x + PLATFORM_WIDTH / 2.0f, y + PLATFORM_HEIGHT / 2.0f);
        glVertex2f(x - PLATFORM_WIDTH / 2.0f, y + PLATFORM_HEIGHT / 2.0f);
        glEnd();
    };

    platformGenerator = new PlatformGenerator(
        SCREEN_SECTIONS,
        PLATFORM_SPACING,
        PLATFORM_WIDTH,
        PLATFORM_HEIGHT,
        SCREEN_LEFT,
        SCREEN_RIGHT,
        GENERATION_AHEAD,
        platformDrawFunc);

    auto meteorDrawFunc = [](float x, float y)
    {
        glBegin(GL_TRIANGLES);
        glColor3f(METEOR_COLOR_R, METEOR_COLOR_G, METEOR_COLOR_B);
        glVertex2f(x, y + METEOR_SIZE);
        glVertex2f(x - METEOR_SIZE, y - METEOR_SIZE);
        glVertex2f(x + METEOR_SIZE, y - METEOR_SIZE);
        glEnd();
    };

    meteorGenerator = new MeteorGenerator(
        METEOR_SECTIONS,
        METEOR_SPACING,
        METEOR_SIZE,
        SCREEN_LEFT,
        SCREEN_RIGHT,
        METEOR_TERMINAL_VELOCITY_X,
        METEOR_TERMINAL_VELOCITY_Y,
        METEOR_GRAVITY,
        METEOR_BATCH_SIZE,
        meteorDrawFunc);

    lava = new Lava(0.0f, SCREEN_BOTTOM - LAVA_HEIGHT);
}

void MainScreen::update(float deltaTime)
{
    if (player)
    {
        player->updateControls(deltaTime);
        player->update(deltaTime);

        player->checkBoundaries(SCREEN_LEFT, SCREEN_RIGHT);

        if (platformGenerator)
        {
            platformGenerator->generatePlatforms(platforms, player->getY());
        }

        if (meteorGenerator)
        {
            meteorGenerator->generateMeteors(meteors, player->getY());
        }

        std::vector<_Object *> collisions = player->getCollidingObjects();
        player->handleCollisions(collisions);
    }

    if (lava)
    {
        lava->updateLava(deltaTime);
    }

    for (PhysicsObject *obj : objects)
    {
        if (obj != player)
            obj->update(deltaTime);
    }

    for (PhysicsObject *meteor : meteors)
    {
        meteor->update(deltaTime);
    }
}

void MainScreen::display()
{
    if (player)
    {
        float camY = player->getY();

        glLoadIdentity();
        gluLookAt(0.0f, camY, 1.0f, 0.0f, camY, 0.0f, 0.0f, 1.0f, 0.0f);

        if (player->getIsInvincible())
        {
            glColor4f(1.0f, 1.0f, 0.0f, 0.5f);
            player->draw();
        }
        else
        {
            player->draw();
        }
    }
    else
    {
        glLoadIdentity();
        gluLookAt(0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f);
    }

    for (Platform *platform : platforms)
    {
        platform->draw();
    }

    if (lava)
    {
        lava->draw();
    }

    for (PhysicsObject *meteor : meteors)
    {
        meteor->draw();
    }

    for (PhysicsObject *obj : objects)
    {
        obj->draw();
    }
}

Player *MainScreen::getPlayer()
{
    return player;
}

Lava *MainScreen::getLava()
{
    return lava;
}

void MainScreen::handleKeyboardUp(unsigned char key, int x, int y)
{
    if (player)
    {
        player->handleKeyUp(key);
    }
}

void MainScreen::handleKeyboardDown(unsigned char key, int x, int y)
{
    if (player)
    {
        player->handleKeyDown(key);
    }
}

void MainScreen::handleSpecialKeysDown(int key, int x, int y)
{
    if (player)
    {
        player->handleSpecialKeyDown(key);
    }
}

void MainScreen::handleSpecialKeysUp(int key, int x, int y)
{
    if (player)
    {
        player->handleSpecialKeyUp(key);
    }
}