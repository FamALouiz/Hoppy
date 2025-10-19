#include "platform.h"

void Platform::defaultDrawFunc(float x, float y)
{
    glBegin(GL_QUADS);
    glColor3f(PLATFORM_COLOR_R, PLATFORM_COLOR_G, PLATFORM_COLOR_B);
    glVertex2f(x - PLATFORM_WIDTH / 2.0f, y - PLATFORM_HEIGHT / 2.0f);
    glVertex2f(x + PLATFORM_WIDTH / 2.0f, y - PLATFORM_HEIGHT / 2.0f);
    glVertex2f(x + PLATFORM_WIDTH / 2.0f, y + PLATFORM_HEIGHT / 2.0f);
    glVertex2f(x - PLATFORM_WIDTH / 2.0f, y + PLATFORM_HEIGHT / 2.0f);
    glEnd();
}

Platform::Platform(float x, float y)
    : StaticObject(x, y, defaultDrawFunc)
{
    setCollisionBox(PLATFORM_WIDTH, PLATFORM_HEIGHT);
}

Platform::Platform(float x, float y, void (*drawFunc)(float, float))
    : StaticObject(x, y, drawFunc)
{
    setCollisionBox(PLATFORM_WIDTH, PLATFORM_HEIGHT);
}

Platform::Platform(float x, float y, float width, float height)
    : StaticObject(x, y, defaultDrawFunc)
{
    setCollisionBox(width, height);
}

Platform::Platform(float x, float y, float width, float height, void (*drawFunc)(float, float))
    : StaticObject(x, y, drawFunc)
{
    setCollisionBox(width, height);
}

Platform::~Platform()
{
}
