#ifndef WIN_SCREEN_H
#define WIN_SCREEN_H

#include "game_window/game_screen.h"
#include <string>
#include <GL/glut.h>
#include "utils.h"

class WinScreen : public GameScreen
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
    WinScreen();
    ~WinScreen();

    void init() override;
    void update(float deltaTime) override;
    void display() override;
    void handleKeyboardUp(unsigned char key, int x, int y) override;
    void handleKeyboardDown(unsigned char key, int x, int y) override;
    void handleSpecialKeysUp(int key, int x, int y) override;
    void handleSpecialKeysDown(int key, int x, int y) override;
};

#endif
