#ifndef START_SCREEN_H
#define START_SCREEN_H

#include "game_window/game_screen.h"
#include <string>
#include <GL/glut.h>
#include "utils.h"

class StartScreen : public GameScreen
{
private:
    float titlePulse;
    bool showPressStart;
    float blinkTimer;

    void drawRect(float x, float y, float width, float height);
    void drawTitle();
    void drawPressStart();
    void drawBackground();

public:
    StartScreen();
    ~StartScreen();

    void init() override;
    void update(float deltaTime) override;
    void display() override;
    void handleKeyboard(unsigned char key, int x, int y) override;
    void handleSpecialKeys(int key, int x, int y) override;
};

#endif
