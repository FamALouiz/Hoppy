#ifndef MAIN_SCREEN_H
#define MAIN_SCREEN_H

#include "game_window/game_screen.h"
#include <string>
#include <GL/glut.h>
#include "utils.h"
#include "physics/objects.h"
#include <vector>

class MainScreen : public GameScreen
{
private:
    std::vector<StaticObject> platforms;
    std::vector<PhysicsObject> objects;

public:
    MainScreen();
    ~MainScreen();

    void addPlatform(const StaticObject &platform) { platforms.push_back(platform); }
    void addObject(const PhysicsObject &obj) { objects.push_back(obj); }
    void init() override;
    void update(float deltaTime) override;
    void display() override;
    void handleKeyboard(unsigned char key, int x, int y) override;
    void handleSpecialKeys(int key, int x, int y) override;
};

#endif
