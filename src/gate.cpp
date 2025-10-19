#include "gate.h"

void Gate::defaultDrawFunc(float x, float y)
{
    glBegin(GL_QUADS);
    glColor3f(GATE_COLOR_R, GATE_COLOR_G, GATE_COLOR_B);
    glVertex2f(x - GATE_WIDTH / 2.0f, y - GATE_HEIGHT / 2.0f);
    glVertex2f(x + GATE_WIDTH / 2.0f, y - GATE_HEIGHT / 2.0f);
    glVertex2f(x + GATE_WIDTH / 2.0f, y + GATE_HEIGHT / 2.0f);
    glVertex2f(x - GATE_WIDTH / 2.0f, y + GATE_HEIGHT / 2.0f);
    glEnd();

    glBegin(GL_QUADS);
    glColor3f(0.3f, 0.2f, 0.1f);
    glVertex2f(x - GATE_WIDTH / 2.0f + 0.05f, y);
    glVertex2f(x + GATE_WIDTH / 2.0f - 0.05f, y);
    glVertex2f(x + GATE_WIDTH / 2.0f - 0.05f, y + GATE_HEIGHT / 2.0f - 0.1f);
    glVertex2f(x - GATE_WIDTH / 2.0f + 0.05f, y + GATE_HEIGHT / 2.0f - 0.1f);
    glEnd();

    glBegin(GL_LINE_LOOP);
    glColor3f(1.0f, 0.84f, 0.0f);
    glVertex2f(x - 0.05f, y + 0.1f);
    glVertex2f(x + 0.05f, y + 0.1f);
    glVertex2f(x + 0.05f, y + 0.2f);
    glVertex2f(x - 0.05f, y + 0.2f);
    glEnd();
}

Gate::Gate(float x, float y)
    : Platform(x, y, GATE_WIDTH, GATE_HEIGHT, defaultDrawFunc)
{
}

Gate::Gate(float x, float y, void (*drawFunc)(float, float))
    : Platform(x, y, GATE_WIDTH, GATE_HEIGHT, drawFunc)
{
}

Gate::~Gate()
{
}
