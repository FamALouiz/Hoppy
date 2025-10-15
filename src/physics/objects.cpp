#include "physics/objects.h"
#include "physics/core.h"

PhysicsObject::PhysicsObject(float x, float y, float terminalVelocityX, float terminalVelocityY, void (*drawFunc)(float, float))
    : _Object(x, y, drawFunc), velocityX(0.0f), velocityY(0.0f), terminalVelocityY(terminalVelocityY), terminalVelocityX(terminalVelocityX)
{
}

void PhysicsObject::update(float deltaTime)
{
    velocityX += accelerationX * deltaTime;
    velocityY += accelerationY * deltaTime;

    if (velocityX > terminalVelocityX)
        velocityX = terminalVelocityX;
    if (velocityX < -terminalVelocityX)
        velocityX = -terminalVelocityX;
    if (velocityY > terminalVelocityY)
        velocityY = terminalVelocityY;
    if (velocityY < -terminalVelocityY)
        velocityY = -terminalVelocityY;

    x += velocityX * deltaTime;
    y += velocityY * deltaTime;
}

void PhysicsObject::draw()
{
    if (drawFunction)
    {
        drawFunction(x, y);
    }
}

StaticObject::StaticObject(float x, float y, void (*drawFunc)(float, float))
    : _Object(x, y, drawFunc)
{
}

void StaticObject::draw()
{
    if (drawFunction)
    {
        drawFunction(x, y);
    }
}