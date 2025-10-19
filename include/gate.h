#ifndef GATE_H
#define GATE_H

#include "platform.h"
#include <GL/glut.h>

#define GATE_WIDTH 0.5f
#define GATE_HEIGHT 0.8f
#define GATE_COLOR_R 0.8f
#define GATE_COLOR_G 0.6f
#define GATE_COLOR_B 0.2f

class Gate : public Platform
{
private:
    static void defaultDrawFunc(float x, float y);

public:
    Gate(float x, float y);
    Gate(float x, float y, void (*drawFunc)(float, float));
    ~Gate();
};

#endif
