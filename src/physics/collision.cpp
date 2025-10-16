#include "physics/collision.h"
#include <cmath>
#include <algorithm>
#include <iostream>

CollisionDetector *CollisionDetector::instance = nullptr;

CollisionBox::CollisionBox(float x, float y, float w, float h, _Object *obj)
    : x(x), y(y), width(w), height(h), radius(0.0f), shape(SHAPE_RECTANGLE), owner(obj)
{
}

CollisionBox::CollisionBox(float x, float y, float r, _Object *obj)
    : x(x), y(y), width(0.0f), height(0.0f), radius(r), shape(SHAPE_CIRCLE), owner(obj)
{
}

CollisionBox::CollisionBox(float x, float y, _Object *obj)
    : x(x), y(y), width(0.0f), height(0.0f), radius(0.0f), shape(SHAPE_POINT), owner(obj)
{
}

void CollisionBox::updatePosition(float newX, float newY)
{
    x = newX;
    y = newY;
}

CollisionDetector::CollisionDetector()
{
}

CollisionDetector::~CollisionDetector()
{
    for (CollisionBox *box : collisionBoxes)
    {
        delete box;
    }
    collisionBoxes.clear();
}

CollisionDetector *CollisionDetector::getInstance()
{
    if (instance == nullptr)
    {
        instance = new CollisionDetector();
    }
    return instance;
}

void CollisionDetector::destroy()
{
    if (instance != nullptr)
    {
        delete instance;
        instance = nullptr;
    }
}

CollisionBox *CollisionDetector::addCollisionBox(float x, float y, float width, float height, _Object *owner)
{
    CollisionBox *box = new CollisionBox(x, y, width, height, owner);
    collisionBoxes.push_back(box);
    return box;
}

CollisionBox *CollisionDetector::addCollisionCircle(float x, float y, float radius, _Object *owner)
{
    CollisionBox *circle = new CollisionBox(x, y, radius, owner);
    collisionBoxes.push_back(circle);
    return circle;
}

CollisionBox *CollisionDetector::addCollisionPoint(float x, float y, _Object *owner)
{
    CollisionBox *point = new CollisionBox(x, y, owner);
    collisionBoxes.push_back(point);
    return point;
}

void CollisionDetector::removeCollisionBox(CollisionBox *box)
{
    auto it = std::find(collisionBoxes.begin(), collisionBoxes.end(), box);
    if (it != collisionBoxes.end())
    {
        delete *it;
        collisionBoxes.erase(it);
    }
}

void CollisionDetector::removeCollisionBoxesByOwner(_Object *owner)
{
    for (auto it = collisionBoxes.begin(); it != collisionBoxes.end();)
    {
        if ((*it)->owner == owner)
        {
            delete *it;
            it = collisionBoxes.erase(it);
        }
        else
        {
            ++it;
        }
    }
}

bool CollisionDetector::checkCollision(const CollisionBox *a, const CollisionBox *b)
{
    if (a->shape == SHAPE_CIRCLE && b->shape == SHAPE_CIRCLE)
    {
        return checkCircleCircle(a, b);
    }
    else if (a->shape == SHAPE_RECTANGLE && b->shape == SHAPE_RECTANGLE)
    {
        return checkRectRect(a, b);
    }
    else if ((a->shape == SHAPE_CIRCLE && b->shape == SHAPE_RECTANGLE) ||
             (a->shape == SHAPE_RECTANGLE && b->shape == SHAPE_CIRCLE))
    {
        return checkCircleRect(a, b);
    }
    else if (a->shape == SHAPE_POINT && b->shape == SHAPE_CIRCLE)
    {
        return checkPointCircle(a, b);
    }
    else if (a->shape == SHAPE_CIRCLE && b->shape == SHAPE_POINT)
    {
        return checkPointCircle(b, a);
    }
    else if (a->shape == SHAPE_POINT && b->shape == SHAPE_RECTANGLE)
    {
        return checkPointRect(a, b);
    }
    else if (a->shape == SHAPE_RECTANGLE && b->shape == SHAPE_POINT)
    {
        return checkPointRect(b, a);
    }

    return false;
}

std::vector<CollisionBox *> CollisionDetector::getCollisions(const CollisionBox *box)
{
    std::vector<CollisionBox *> collisions;
    for (CollisionBox *other : collisionBoxes)
    {
        if (other != box && checkCollision(box, other))
        {
            collisions.push_back(other);
        }
    }

    return collisions;
}

std::vector<_Object *> CollisionDetector::getCollidingObjects(const CollisionBox *box)
{
    std::vector<_Object *> objects;
    std::vector<CollisionBox *> collisions = getCollisions(box);

    for (CollisionBox *collision : collisions)
    {
        if (collision->owner != nullptr)
        {
            objects.push_back(collision->owner);
        }
    }

    return objects;
}

void CollisionDetector::clear()
{
    for (CollisionBox *box : collisionBoxes)
    {
        delete box;
    }
    collisionBoxes.clear();
}

int CollisionDetector::getCollisionBoxCount() const
{
    return collisionBoxes.size();
}

bool CollisionDetector::checkCircleCircle(const CollisionBox *a, const CollisionBox *b)
{
    float dx = a->x - b->x;
    float dy = a->y - b->y;
    float distance = std::sqrt(dx * dx + dy * dy);
    float radiusSum = a->radius + b->radius;

    return distance < radiusSum;
}

bool CollisionDetector::checkRectRect(const CollisionBox *a, const CollisionBox *b)
{
    float aLeft = a->x - a->width / 2.0f;
    float aRight = a->x + a->width / 2.0f;
    float aTop = a->y + a->height / 2.0f;
    float aBottom = a->y - a->height / 2.0f;

    float bLeft = b->x - b->width / 2.0f;
    float bRight = b->x + b->width / 2.0f;
    float bTop = b->y + b->height / 2.0f;
    float bBottom = b->y - b->height / 2.0f;

    return !(aRight < bLeft || aLeft > bRight || aTop < bBottom || aBottom > bTop);
}

bool CollisionDetector::checkCircleRect(const CollisionBox *a, const CollisionBox *b)
{
    const CollisionBox *circle = (a->shape == SHAPE_CIRCLE) ? a : b;
    const CollisionBox *rect = (a->shape == SHAPE_RECTANGLE) ? a : b;

    float rectLeft = rect->x - rect->width / 2.0f;
    float rectRight = rect->x + rect->width / 2.0f;
    float rectTop = rect->y + rect->height / 2.0f;
    float rectBottom = rect->y - rect->height / 2.0f;

    float closestX = std::max(rectLeft, std::min(circle->x, rectRight));
    float closestY = std::max(rectBottom, std::min(circle->y, rectTop));

    float dx = circle->x - closestX;
    float dy = circle->y - closestY;
    float distance = std::sqrt(dx * dx + dy * dy);

    return distance < circle->radius;
}

bool CollisionDetector::checkPointCircle(const CollisionBox *point, const CollisionBox *circle)
{
    float dx = point->x - circle->x;
    float dy = point->y - circle->y;
    float distance = std::sqrt(dx * dx + dy * dy);

    return distance < circle->radius;
}

bool CollisionDetector::checkPointRect(const CollisionBox *point, const CollisionBox *rect)
{
    float rectLeft = rect->x - rect->width / 2.0f;
    float rectRight = rect->x + rect->width / 2.0f;
    float rectTop = rect->y + rect->height / 2.0f;
    float rectBottom = rect->y - rect->height / 2.0f;

    return point->x >= rectLeft && point->x <= rectRight &&
           point->y >= rectBottom && point->y <= rectTop;
}
