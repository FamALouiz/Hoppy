#include <GL/glut.h>
#include "screens/main_screen.h"
#include "physics/core.h"

#define MOVEMENT_SPEED 0.01f

MainScreen::MainScreen()
{
}

MainScreen::~MainScreen()
{
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
    PhysicsObject player = PhysicsObject(0.0f, 0.0f, 1.5f, 1.5f, playerDrawFunc);
    player.setVelocity(0.0f, 0.0f);
    player.setAcceleration(0.0f, GRAVITY);
    addObject(player);
}

void MainScreen::update(float deltaTime)
{
    for (PhysicsObject &obj : objects)
    {
        obj.update(deltaTime);
    }
}

void MainScreen::display()
{
    for (StaticObject &platform : platforms)
    {
        platform.draw();
    }

    for (PhysicsObject &obj : objects)
    {
        obj.draw();
    }
}

PhysicsObject *MainScreen::getPlayer()
{
    if (objects.empty())
        return nullptr;
    return &objects[0]; // Assuming the first object is the player
}

void MainScreen::handleKeyboard(unsigned char key, int x, int y)
{
}

void MainScreen::handleSpecialKeys(int key, int x, int y)
{
    PhysicsObject *player = getPlayer();
    if (!player)
        return;

    switch (key)
    {
    case GLUT_KEY_LEFT:
        player->moveLeft(MOVEMENT_SPEED);
        break;
    case GLUT_KEY_RIGHT:
        player->moveRight(MOVEMENT_SPEED);
        break;
    case GLUT_KEY_UP:
        player->setVelocity(player->getVelocityX(), 20.0f);
        break;
    case GLUT_KEY_DOWN:
        player->moveDown(MOVEMENT_SPEED);
        break;
    }
}