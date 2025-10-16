#ifndef COLLISION_H
#define COLLISION_H

#include "physics/objects.h"
#include <vector>

enum CollisionShape
{
    SHAPE_CIRCLE,
    SHAPE_RECTANGLE,
    SHAPE_POINT
};

struct CollisionBox
{
    float x, y;
    float width, height;
    float radius;
    CollisionShape shape;
    _Object *owner;

    CollisionBox(float x, float y, float w, float h, _Object *obj);
    CollisionBox(float x, float y, float r, _Object *obj);
    CollisionBox(float x, float y, _Object *obj);

    void updatePosition(float newX, float newY);
};

class CollisionDetector
{
private:
    static CollisionDetector *instance;
    std::vector<CollisionBox *> collisionBoxes;

    CollisionDetector();
    CollisionDetector(const CollisionDetector &) = delete;
    CollisionDetector &operator=(const CollisionDetector &) = delete;

    bool checkCircleCircle(const CollisionBox *a, const CollisionBox *b);
    bool checkRectRect(const CollisionBox *a, const CollisionBox *b);
    bool checkCircleRect(const CollisionBox *a, const CollisionBox *b);
    bool checkPointCircle(const CollisionBox *point, const CollisionBox *circle);
    bool checkPointRect(const CollisionBox *point, const CollisionBox *rect);

public:
    ~CollisionDetector();

    static CollisionDetector *getInstance();
    static void destroy();

    CollisionBox *addCollisionBox(float x, float y, float width, float height, _Object *owner);
    CollisionBox *addCollisionCircle(float x, float y, float radius, _Object *owner);
    CollisionBox *addCollisionPoint(float x, float y, _Object *owner);

    void removeCollisionBox(CollisionBox *box);
    void removeCollisionBoxesByOwner(_Object *owner);

    bool checkCollision(const CollisionBox *a, const CollisionBox *b);
    std::vector<CollisionBox *> getCollisions(const CollisionBox *box);
    std::vector<_Object *> getCollidingObjects(const CollisionBox *box);

    void clear();
    int getCollisionBoxCount() const;
};

#endif
