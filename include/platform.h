#ifndef PLATFORM_H
#define PLATFORM_H

#include "physics/objects.h"
#include <GL/glut.h>

#define PLATFORM_WIDTH 0.4f
#define PLATFORM_HEIGHT 0.1f
#define PLATFORM_COLOR_R 0.5f
#define PLATFORM_COLOR_G 0.3f
#define PLATFORM_COLOR_B 0.1f

class Platform : public StaticObject
{
private:
    static void defaultDrawFunc(float x, float y);

public:
    Platform(float x, float y);
    Platform(float x, float y, void (*drawFunc)(float, float));
    Platform(float x, float y, float width, float height);
    Platform(float x, float y, float width, float height, void (*drawFunc)(float, float));
    ~Platform();

    static float getDefaultWidth() { return PLATFORM_WIDTH; }
    static float getDefaultHeight() { return PLATFORM_HEIGHT; }
};

#endif
