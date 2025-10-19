#include "player.h"
#include <iostream>
#include "platform.h"
#include <lava.h>
#include "generators/powerup_manager.h"

void Player::defaultDrawFunc(float x, float y)
{
    glBegin(GL_QUADS);
    glVertex2f(x - PLAYER_SIZE, y - PLAYER_SIZE);
    glVertex2f(x + PLAYER_SIZE, y - PLAYER_SIZE);
    glVertex2f(x + PLAYER_SIZE, y + PLAYER_SIZE);
    glVertex2f(x - PLAYER_SIZE, y + PLAYER_SIZE);
    glEnd();
}

Player::Player(float x, float y)
    : PhysicsObject(x, y, PLAYER_TERMINAL_VELOCITY_X, PLAYER_TERMINAL_VELOCITY_Y, defaultDrawFunc),
      moveLeft(false), moveRight(false), canJump(false)
{
    setVelocity(0.0f, 0.0f);
    setAcceleration(0.0f, GRAVITY);
    setCollisionBox(PLAYER_SIZE * 2.0f, PLAYER_SIZE * 2.0f);
}

Player::Player(float x, float y, void (*drawFunc)(float, float))
    : PhysicsObject(x, y, PLAYER_TERMINAL_VELOCITY_X, PLAYER_TERMINAL_VELOCITY_Y, drawFunc),
      moveLeft(false), moveRight(false), canJump(false)
{
    setVelocity(0.0f, 0.0f);
    setAcceleration(0.0f, GRAVITY);
    setCollisionBox(PLAYER_SIZE * 2.0f, PLAYER_SIZE * 2.0f);
}

Player::~Player()
{
}

void Player::handleKeyDown(int key)
{
}

void Player::handleKeyUp(int key)
{
}

void Player::handleSpecialKeyDown(int key)
{
    if (key == GLUT_KEY_LEFT)
    {
        moveLeft = true;
    }
    if (key == GLUT_KEY_RIGHT)
    {
        moveRight = true;
    }
    if (key == GLUT_KEY_UP)
    {
        canJump = true;
    }
}

void Player::handleSpecialKeyUp(int key)
{
    if (key == GLUT_KEY_LEFT)
    {
        moveLeft = false;
    }
    if (key == GLUT_KEY_RIGHT)
    {
        moveRight = false;
    }
    if (key == GLUT_KEY_UP)
    {
        canJump = false;
    }
}

void Player::updateControls(float deltaTime)
{
    float currentVelX = 0.0f;

    if (moveLeft)
    {
        currentVelX = -PLAYER_MOVEMENT_SPEED;
    }
    if (moveRight)
    {
        currentVelX = PLAYER_MOVEMENT_SPEED;
    }

    setVelocity(currentVelX, getVelocityY());

    if (canJump && getIsGrounded())
    {
        setVelocity(getVelocityX(), PLAYER_JUMP_SPEED);
    }
}

void Player::handleCollisions(const std::vector<_Object *> &collisions)
{

    bool grounded = false;

    for (_Object *obj : collisions)
    {
        if (typeid(*obj) == typeid(Platform) && !isUsingJetpack)
        {
            Platform *platform = dynamic_cast<Platform *>(obj);
            if (isCollidingFromTop(platform))
            {
                float platformTop = platform->getY() + platform->getCollisionHeight() / 2.0f;
                setPosition(getX(), platformTop + getCollisionHeight() / 2.0f);

                if (getVelocityY() < 0)
                {
                    setVelocity(getVelocityX(), 0.0f);
                }

                grounded = true;
            }
            else if (isCollidingFromBottom(platform))
            {
                float platformBottom = platform->getY() - platform->getCollisionHeight() / 2.0f;
                setPosition(getX(), platformBottom - getCollisionHeight() / 2.0f);

                if (getVelocityY() > 0)
                {
                    setVelocity(getVelocityX(), 0.0f);
                }
            }
            else if (isCollidingFromLeft(platform))
            {
                float platformLeft = platform->getX() - platform->getCollisionWidth() / 2.0f;
                setPosition(platformLeft - getCollisionWidth() / 2.0f, getY());
                setVelocity(0.0f, getVelocityY());
            }
            else if (isCollidingFromRight(platform))
            {
                float platformRight = platform->getX() + platform->getCollisionWidth() / 2.0f;
                setPosition(platformRight + getCollisionWidth() / 2.0f, getY());
                setVelocity(0.0f, getVelocityY());
            }
        }
        else if (typeid(*obj) == typeid(Lava) && !getIsInvincible())
        {
            loseLife();
            loseLife();
            loseLife();
            PowerupManager::getInstance()->activateDamageShield();
            std::cout << "Player hit by lava! Lives left: " << getLives() << std::endl;
        }
        else if (typeid(*obj) == typeid(PhysicsObject) && !getIsInvincible())
        {
            loseLife();
            PowerupManager::getInstance()->activateDamageShield();
            std::cout << "Player hit by meteor! Lives left: " << getLives() << std::endl;
        }
    }

    setGrounded(grounded);

    if (grounded)
    {
        setAcceleration(0.0f, 0.0f);
    }
    else if (!isUsingJetpack)
    {
        setAcceleration(0.0f, GRAVITY);
    }
}

void Player::checkBoundaries(float screenLeft, float screenRight)
{
    float playerX = getX();
    float playerWidth = getCollisionWidth() / 2.0f;

    if (playerX - playerWidth < screenLeft)
    {
        setPosition(screenLeft + playerWidth, getY());
        setVelocity(0.0f, getVelocityY());
    }
    else if (playerX + playerWidth > screenRight)
    {
        setPosition(screenRight - playerWidth, getY());
        setVelocity(0.0f, getVelocityY());
    }
}
