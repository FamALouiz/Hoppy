#ifndef LAVA_H
#define LAVA_H

#include "physics/objects.h"
#include <GL/glut.h>

#define LAVA_WIDTH 2.0f
#define LAVA_HEIGHT 5.0f
#define LAVA_INITIAL_SPEED 0.05f
#define LAVA_ACCELERATION 0.002f
#define LAVA_MAX_SPEED 0.5f
#define LAVA_TERMINAL_VELOCITY 2.0f
#define LAVA_COLOR_R 1.0f
#define LAVA_COLOR_G 0.3f
#define LAVA_COLOR_B 0.0f

class Lava : public PhysicsObject
{
private:
    float currentSpeed;
    float accelerationRate;
    float maxSpeed;

    static void defaultDrawFunc(float x, float y);

public:
    Lava(float x, float y);
    Lava(float x, float y, void (*drawFunc)(float, float));
    ~Lava();

    void updateLava(float deltaTime);
    void resetSpeed();
    void setAccelerationRate(float rate) { accelerationRate = rate; }
    void setMaxSpeed(float speed) { maxSpeed = speed; }
    float getCurrentSpeed() const { return currentSpeed; }
};

#endif
