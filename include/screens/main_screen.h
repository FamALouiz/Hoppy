#ifndef MAIN_SCREEN_H
#define MAIN_SCREEN_H

#include "game_window/game_screen.h"
#include <string>
#include <GL/glut.h>
#include "utils.h"
#include "physics/objects.h"
#include "player.h"
#include "generators/platform_generator.h"
#include "generators/meteor_generator.h"
#include <vector>

class MainScreen : public GameScreen
{
private:
    std::vector<StaticObject *> platforms;
    std::vector<PhysicsObject *> objects;
    std::vector<PhysicsObject *> meteors;
    PlatformGenerator *platformGenerator;
    MeteorGenerator *meteorGenerator;
    Player *player;

public:
    MainScreen();
    ~MainScreen();

    void addPlatform(StaticObject *platform) { platforms.push_back(platform); }
    void addObject(PhysicsObject *obj) { objects.push_back(obj); }
    void addMeteor(PhysicsObject *meteor) { meteors.push_back(meteor); }
    Player *getPlayer();
    void init() override;
    void update(float deltaTime) override;
    void display() override;
    void handleKeyboardDown(unsigned char key, int x, int y) override;
    void handleSpecialKeysUp(int key, int x, int y) override;
    void handleSpecialKeysDown(int key, int x, int y) override;
    void handleKeyboardUp(unsigned char key, int x, int y) override;
};

#endif
