#include "physics/objects.h"
#include "physics/core.h"
#include "physics/collision.h"
#include <iostream>

_CollisionObject::_CollisionObject(float x, float y, void (*drawFunc)(float, float))
    : _Object(x, y, drawFunc), collisionBox(nullptr)
{
}

_CollisionObject::~_CollisionObject()
{
    if (collisionBox != nullptr)
    {
        CollisionDetector *detector = CollisionDetector::getInstance();
        detector->removeCollisionBox(collisionBox);
        collisionBox = nullptr;
    }
}

void _CollisionObject::setCollisionBox(float width, float height)
{
    if (collisionBox != nullptr)
    {
        CollisionDetector *detector = CollisionDetector::getInstance();
        detector->removeCollisionBox(collisionBox);
    }

    CollisionDetector *detector = CollisionDetector::getInstance();
    collisionBox = detector->addCollisionBox(x, y, width, height, this);
}

void _CollisionObject::setCollisionCircle(float radius)
{
    if (collisionBox != nullptr)
    {
        CollisionDetector *detector = CollisionDetector::getInstance();
        detector->removeCollisionBox(collisionBox);
    }

    CollisionDetector *detector = CollisionDetector::getInstance();
    collisionBox = detector->addCollisionCircle(x, y, radius, this);
}

bool _CollisionObject::isColliding()
{
    if (collisionBox == nullptr)
    {
        return false;
    }

    CollisionDetector *detector = CollisionDetector::getInstance();
    std::vector<CollisionBox *> collisions = detector->getCollisions(collisionBox);
    return !collisions.empty();
}

std::vector<_Object *> _CollisionObject::getCollidingObjects()
{
    if (collisionBox == nullptr)
    {
        return std::vector<_Object *>();
    }

    CollisionDetector *detector = CollisionDetector::getInstance();
    return detector->getCollidingObjects(collisionBox);
}

PhysicsObject::PhysicsObject(float x, float y, float terminalVelocityX, float terminalVelocityY, void (*drawFunc)(float, float))
    : _CollisionObject(x, y, drawFunc), velocityX(0.0f), velocityY(0.0f), terminalVelocityY(terminalVelocityY), terminalVelocityX(terminalVelocityX), accelerationX(0.0f), accelerationY(0.0f)
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
    if (collisionBox != nullptr)
    {
        collisionBox->updatePosition(x, y);
    }
}

void PhysicsObject::draw()
{
    if (drawFunction)
    {
        drawFunction(x, y);
    }
}

StaticObject::StaticObject(float x, float y, void (*drawFunc)(float, float))
    : _CollisionObject(x, y, drawFunc)
{
}

void StaticObject::draw()
{
    if (drawFunction)
    {
        drawFunction(x, y);
    }
}