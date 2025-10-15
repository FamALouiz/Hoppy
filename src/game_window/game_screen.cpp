#include "game_window/game_screen.h"

GameScreen::GameScreen() : isActive(false)
{
}

GameScreen::~GameScreen()
{
}

void GameScreen::init()
{
}

void GameScreen::update(float deltaTime)
{
}

void GameScreen::display()
{
    glClear(GL_COLOR_BUFFER_BIT);
}

void GameScreen::handleKeyboard(unsigned char key, int x, int y)
{
}

void GameScreen::handleSpecialKeys(int key, int x, int y)
{
}

void GameScreen::handleMouse(int button, int state, int x, int y)
{
}

void GameScreen::handleMouseMotion(int x, int y)
{
}

void GameScreen::setActive(bool active)
{
    isActive = active;
}

bool GameScreen::getActive() const
{
    return isActive;
}
