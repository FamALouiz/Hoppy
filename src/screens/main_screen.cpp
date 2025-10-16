#include <GL/glut.h>
#include "screens/main_screen.h"
#include "physics/core.h"
#include <iostream>

MainScreen::MainScreen() : platformGenerator(nullptr)
{
}

MainScreen::~MainScreen()
{
    for (PhysicsObject *obj : objects)
    {
        delete obj;
    }
    objects.clear();

    for (StaticObject *platform : platforms)
    {
        delete platform;
    }
    platforms.clear();
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

    auto playerDrawFunc = [](float x, float y)
    {
        glBegin(GL_QUADS);
        glColor3f(0.0f, 0.8f, 0.0f);
        glVertex2f(x - 0.05f, y - 0.05f);
        glVertex2f(x + 0.05f, y - 0.05f);
        glVertex2f(x + 0.05f, y + 0.05f);
        glVertex2f(x - 0.05f, y + 0.05f);
        glEnd();
    };
    PhysicsObject *player = new PhysicsObject(0.0f, 0.0f, 1.5f, 1.5f, playerDrawFunc);
    player->setVelocity(0.0f, 0.0f);
    player->setAcceleration(0.0f, GRAVITY);
    player->setCollisionBox(0.1f, 0.1f);
    addObject(player);

    auto platformDrawFunc = [](float x, float y)
    {
        glBegin(GL_QUADS);
        glColor3f(0.5f, 0.3f, 0.1f);
        glVertex2f(x - 0.2f, y - 0.05f);
        glVertex2f(x + 0.2f, y - 0.05f);
        glVertex2f(x + 0.2f, y + 0.05f);
        glVertex2f(x - 0.2f, y + 0.05f);
        glEnd();
    };

    StaticObject *ground = new StaticObject(0.0f, -0.8f, platformDrawFunc);
    ground->setCollisionBox(0.4f, 0.1f);
    addPlatform(ground);

    StaticObject *platform1 = new StaticObject(-0.6f, -0.4f, platformDrawFunc);
    platform1->setCollisionBox(0.4f, 0.1f);
    addPlatform(platform1);

    StaticObject *platform2 = new StaticObject(0.6f, -0.2f, platformDrawFunc);
    platform2->setCollisionBox(0.4f, 0.1f);
    addPlatform(platform2);

    StaticObject *platform3 = new StaticObject(-0.3f, 0.2f, platformDrawFunc);
    platform3->setCollisionBox(0.4f, 0.1f);
    addPlatform(platform3);

    StaticObject *platform4 = new StaticObject(0.8f, 0.4f, platformDrawFunc);
    platform4->setCollisionBox(0.4f, 0.1f);
    addPlatform(ground);
}

void MainScreen::update(float deltaTime)
{
    PhysicsObject *player = getPlayer();
    if (player)
    {
        player->update(deltaTime);
        std::vector<_Object *> collisions = player->getCollidingObjects();
        bool grounded = false;

        for (_Object *obj : collisions)
        {
            StaticObject *platform = dynamic_cast<StaticObject *>(obj);
            if (platform)
            {
                if (player->isCollidingFromTop(platform))
                {
                    float platformTop = platform->getY() + platform->getCollisionHeight() / 2.0f;
                    player->setPosition(player->getX(), platformTop + player->getCollisionHeight() / 2.0f);

                    if (player->getVelocityY() < 0)
                    {
                        player->setVelocity(player->getVelocityX(), 0.0f);
                    }

                    grounded = true;
                }
                else if (player->isCollidingFromBottom(platform))
                {
                    float platformBottom = platform->getY() - platform->getCollisionHeight() / 2.0f;
                    player->setPosition(player->getX(), platformBottom - player->getCollisionHeight() / 2.0f);

                    if (player->getVelocityY() > 0)
                    {
                        player->setVelocity(player->getVelocityX(), 0.0f);
                    }
                }
                else if (player->isCollidingFromLeft(platform))
                {
                    float platformLeft = platform->getX() - platform->getCollisionWidth() / 2.0f;
                    player->setPosition(platformLeft - player->getCollisionWidth() / 2.0f, player->getY());
                    player->setVelocity(0.0f, player->getVelocityY());
                }
                else if (player->isCollidingFromRight(platform))
                {
                    float platformRight = platform->getX() + platform->getCollisionWidth() / 2.0f;
                    player->setPosition(platformRight + player->getCollisionWidth() / 2.0f, player->getY());
                    player->setVelocity(0.0f, player->getVelocityY());
                }
            }
        }

        player->setGrounded(grounded);

        if (grounded)
        {
            player->setAcceleration(0.0f, 0.0f);
        }
        else
        {
            player->setAcceleration(0.0f, GRAVITY);
        }
    }

    for (PhysicsObject *obj : objects)
    {
        if (obj != player)
            obj->update(deltaTime);
    }
}

void MainScreen::display()
{
    PhysicsObject *player = getPlayer();
    if (player)
    {
        float camY = player->getY();

        glLoadIdentity();
        gluLookAt(0.0f, camY, 1.0f, 0.0f, camY, 0.0f, 0.0f, 1.0f, 0.0f);
    }
    else
    {
        glLoadIdentity();
        gluLookAt(0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f);
    }

    for (StaticObject *platform : platforms)
    {
        platform->draw();
    }

    for (PhysicsObject *obj : objects)
    {
        obj->draw();
    }
}

PhysicsObject *MainScreen::getPlayer()
{
    if (objects.empty())
        return nullptr;
    return objects[0]; // Assuming the first object is the player
}

void MainScreen::handleKeyboardUp(unsigned char key, int x, int y)
{
}

void MainScreen::handleKeyboardDown(unsigned char key, int x, int y)
{
}

void MainScreen::handleSpecialKeysDown(int key, int x, int y)
{
    PhysicsObject *player = getPlayer();
    if (!player)
        return;

    switch (key)
    {
    case GLUT_KEY_LEFT:
        player->setVelocity(-MOVEMENT_SPEED, player->getVelocityY());
        break;
    case GLUT_KEY_RIGHT:
        player->setVelocity(MOVEMENT_SPEED, player->getVelocityY());
        break;
    case GLUT_KEY_UP:
        if (player->getIsGrounded())
        {
            player->setVelocity(player->getVelocityX(), JUMP_SPEED);
        }
        break;
    }
}

void MainScreen::handleSpecialKeysUp(int key, int x, int y)
{
    PhysicsObject *player = getPlayer();
    if (!player)
        return;

    switch (key)
    {
    case GLUT_KEY_LEFT:
    case GLUT_KEY_RIGHT:
        player->setVelocity(0.0f, player->getVelocityY());
        break;
    }
}