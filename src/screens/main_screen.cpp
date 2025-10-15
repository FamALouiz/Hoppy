#include <GL/glut.h>
#include "screens/main_screen.h"

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
}

void MainScreen::update(float deltaTime)
{
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

void MainScreen::handleKeyboard(unsigned char key, int x, int y)
{
}

void MainScreen::handleSpecialKeys(int key, int x, int y)
{
}