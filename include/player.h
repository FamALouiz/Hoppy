#ifndef PLAYER_H
#define PLAYER_H

#include "physics/objects.h"
#include "physics/core.h"
#include <GL/glut.h>

#define PLAYER_SIZE 0.05f
#define PLAYER_TERMINAL_VELOCITY_X 1.5f
#define PLAYER_TERMINAL_VELOCITY_Y 1.5f
#define PLAYER_MOVEMENT_SPEED 25.0f
#define PLAYER_JUMP_SPEED 50.0f
#define PLAYER_COLOR_R 0.0f
#define PLAYER_COLOR_G 0.8f
#define PLAYER_COLOR_B 0.0f

class Player : public PhysicsObject
{
private:
    bool moveLeft;
    bool moveRight;
    bool canJump;

    static void defaultDrawFunc(float x, float y);

public:
    Player(float x, float y);
    Player(float x, float y, void (*drawFunc)(float, float));
    ~Player();

    void handleKeyDown(int key);
    void handleKeyUp(int key);
    void handleSpecialKeyDown(int key);
    void handleSpecialKeyUp(int key);
    void updateControls(float deltaTime);
    void handleCollisions(const std::vector<_Object *> &collisions);
    void checkBoundaries(float screenLeft, float screenRight);
};

#endif
