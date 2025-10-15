#include "physics/objects.h"
#include "physics/core.h"

PhysicsObject::PhysicsObject(float x, float y, void (*drawFunc)())
    : _Object(x, y, drawFunc), velocityX(0.0f), velocityY(0.0f)
{
}

void PhysicsObject::update(float deltaTime)
{
}

void PhysicsObject::draw()
{
    if (drawFunction)
    {
        drawFunction();
    }
}

void PhysicsObject::setVelocity(float vx, float vy)
{
    velocityX = vx;
    velocityY = vy;
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