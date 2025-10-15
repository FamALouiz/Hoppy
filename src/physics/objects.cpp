#include "physics/objects.h"
#include "physics/core.h"

PhysicsObject::PhysicsObject(float x, float y, void (*drawFunc)())
    : _Object(x, y, drawFunc), velocityX(0.0f), velocityY(0.0f)
{
}

void PhysicsObject::update(float deltaTime)
{
    velocityX += accelerationX * deltaTime;
    velocityY += accelerationY * deltaTime;

    x += velocityX * deltaTime;
    y += velocityY * deltaTime;
}

void PhysicsObject::draw()
{
    if (drawFunction)
    {
        drawFunction();
    }
}

StaticObject::StaticObject(float x, float y, void (*drawFunc)())
    : _Object(x, y, drawFunc)
{
}

void StaticObject::draw()
{
    if (drawFunction)
    {
        drawFunction();
    }
}