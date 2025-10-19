#ifndef PLAYER_H
#define PLAYER_H

#include "physics/objects.h"
#include "physics/core.h"
#include <GL/glut.h>

#define PLAYER_WIDTH 0.2f
#define PLAYER_HEIGHT 0.25f
#define PLAYER_TERMINAL_VELOCITY_X 1.5f
#define PLAYER_TERMINAL_VELOCITY_Y 1.5f
#define PLAYER_MOVEMENT_SPEED 25.0f
#define PLAYER_JUMP_SPEED 50.0f
#define PLAYER_COLOR_R 0.0f
#define PLAYER_COLOR_G 0.8f
#define PLAYER_COLOR_B 0.0f

#define PLAYER_SPRITE_COLS 8
#define PLAYER_SPRITE_ROWS 8
#define PLAYER_SPRITE_INDEX 0
#define PLAYER_SPRITE_PATH "C:\\Users\\fam\\OneDrive\\Desktop\\GIU\\Semester 7\\Graphics\\Hoppy\\assets\\sprites\\knight.png"

class Player : public PhysicsObject
{
private:
    bool moveLeft;
    bool moveRight;
    bool canJump;
    bool isInvincible = false;
    bool isUsingJetpack = false;
    int lives = 3;
    int keys = 0;
    bool hasSuperKey = false;

    static GLuint spriteTexture;
    static bool textureLoaded;
    static void loadTexture();
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
    void loseLife()
    {
        if (lives > 0)
            lives--;
    }
    bool isDead() const { return lives <= 0; }
    int getLives() const { return lives; }
    bool getIsInvincible() const { return isInvincible; }
    void setInvincible(bool invincible) { isInvincible = invincible; }
    bool getIsUsingJetpack() const { return isUsingJetpack; }
    void setUsingJetpack(bool usingJetpack) { isUsingJetpack = usingJetpack; }
    int getKeys() const { return keys; }
    void addKey() { keys++; }
    bool getHasSuperKey() const { return hasSuperKey; }
    void setSuperKey(bool superKey) { hasSuperKey = superKey; }
    static void cleanupTexture();
};

#endif
