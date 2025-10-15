#ifndef OBJECTS_H
#define OBJECTS_H

#include <GL/glut.h>
#include <vector>

class _Object
{
protected:
    float x, y;
    void (*drawFunction)(float, float);

public:
    _Object(float x, float y, void (*drawFunc)(float, float)) : x(x), y(y), drawFunction(drawFunc) {}
    virtual void draw() = 0;
    virtual void update(float deltaTime) = 0;
    virtual ~_Object() {}
    float getX() const { return x; }
    float getY() const { return y; }
    void setPosition(float newX, float newY)
    {
        x = newX;
        y = newY;
    }
};

class PhysicsObject : public _Object
{
private:
    float velocityX, velocityY;
    float terminalVelocityY, terminalVelocityX;
    float accelerationX, accelerationY;

public:
    PhysicsObject(float x, float y, float terminalVelocityX, float terminalVelocityY, void (*drawFunc)(float, float));
    void setVelocity(float vx, float vy)
    {
        velocityX = vx;
        velocityY = vy;
    }
    void setAcceleration(float ax, float ay)
    {
        accelerationX = ax;
        accelerationY = ay;
    }
    void moveLeft(float amount) { x -= amount; }
    void moveRight(float amount) { x += amount; }
    void moveUp(float amount) { y += amount; }
    void moveDown(float amount) { y -= amount; }
    float getVelocityX() const { return velocityX; }
    float getVelocityY() const { return velocityY; }
    float getAccelerationX() const { return accelerationX; }
    float getAccelerationY() const { return accelerationY; }
    void update(float deltaTime);
    void draw();
};

class StaticObject : public _Object
{
public:
    StaticObject(float x, float y, void (*drawFunc)(float, float));
    void draw();
    void update(float deltaTime) {};
};

#endif