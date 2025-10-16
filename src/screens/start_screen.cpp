#include "screens/start_screen.h"
#include "screens/main_screen.h"
#include <GL/glut.h>
#include <stdio.h>
#include <math.h>
#include "game_window/game_window.h"

StartScreen::StartScreen() : titlePulse(0.0f), showPressStart(true), blinkTimer(0.0f)
{
}

StartScreen::~StartScreen()
{
}

void StartScreen::init()
{
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-1.0, 1.0, -1.0, 1.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

void StartScreen::update(float deltaTime)
{
    titlePulse += deltaTime * 2.0f;
    if (titlePulse > 6.28f)
    {
        titlePulse -= 6.28f;
    }

    blinkTimer += deltaTime;
    if (blinkTimer > 0.5f)
    {
        showPressStart = !showPressStart;
        blinkTimer = 0.0f;
    }
}

void StartScreen::display()
{
    drawBackground();
    drawTitle();
    drawPressStart();
}

void StartScreen::handleKeyboardUp(unsigned char key, int x, int y)
{
    if (key == ' ' || key == 13)
    {
        printf("Starting game...\n");
        MainScreen *mainScreen = new MainScreen();
        GameWindow::getInstance()->setScreen(mainScreen);
    }
}

void StartScreen::handleSpecialKeysUp(int key, int x, int y)
{
}

void StartScreen::handleKeyboardDown(unsigned char key, int x, int y)
{
}

void StartScreen::handleSpecialKeysDown(int key, int x, int y)
{
}

void StartScreen::drawBackground()
{
    glBegin(GL_QUADS);
    glColor3f(0.1f, 0.1f, 0.2f);
    glVertex2f(-1.0f, -1.0f);
    glVertex2f(1.0f, -1.0f);
    glColor3f(0.2f, 0.2f, 0.4f);
    glVertex2f(1.0f, 1.0f);
    glVertex2f(-1.0f, 1.0f);
    glEnd();

    for (int i = 0; i < 30; i++)
    {
        float x = -1.0f + (i * 0.1f);
        float pulse = sin(titlePulse + i * 0.3f) * 0.2f;
        float alpha = 0.1f + pulse * 0.3f;

        glBegin(GL_QUADS);
        glColor4f(0.3f, 0.5f, 0.7f, alpha);
        glVertex2f(x, -1.0f);
        glVertex2f(x + 0.05f, -1.0f);
        glVertex2f(x + 0.05f, 1.0f);
        glVertex2f(x, 1.0f);
        glEnd();
    }
}

void StartScreen::drawTitle()
{
    float pulse = sin(titlePulse) * 0.1f + 0.9f;
    glColor3f(pulse, pulse * 0.8f, 0.2f);

    // drawRect(-0.4f, 0.3f, 0.8f, 0.3f);

    glColor3f(0.1f, 0.1f, 0.2f);
    drawRect(0.0f, 0.45f, 0.7f, 0.15f);

    glColor3f(pulse, pulse * 0.8f, 0.2f);
    drawText("Hoppy - Ready to have fun?", 0.0f, 0.45f, 0.04f);
}

void StartScreen::drawPressStart()
{
    if (showPressStart)
    {
        glColor3f(0.8f, 0.8f, 0.8f);
        drawText("PRESS SPACE TO START", 0.0f, -0.3f, 0.05f);

        glColor3f(0.6f, 0.6f, 0.6f);
        drawText("ESC TO QUIT", 0.0f, -0.5f, 0.04f);
    }
}

void StartScreen::drawRect(float x, float y, float width, float height)
{
    float halfWidth = width * 0.5f;
    float halfHeight = height * 0.5f;

    glBegin(GL_QUADS);
    glVertex2f(x - halfWidth, y - halfHeight);
    glVertex2f(x + halfWidth, y - halfHeight);
    glVertex2f(x + halfWidth, y + halfHeight);
    glVertex2f(x - halfWidth, y + halfHeight);
    glEnd();
}
