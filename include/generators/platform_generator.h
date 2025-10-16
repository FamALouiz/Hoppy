#ifndef PLATFORM_GENERATOR_H
#define PLATFORM_GENERATOR_H

#include "physics/objects.h"
#include <vector>

#define SCREEN_SECTIONS 3
#define PLATFORM_SPACING 0.5f
#define PLATFORM_WIDTH 0.4f
#define PLATFORM_HEIGHT 0.1f
#define SCREEN_LEFT -1.0f
#define SCREEN_RIGHT 1.0f
#define SCREEN_BOTTOM -1.0f
#define SCREEN_TOP 1.0f
#define GENERATION_AHEAD 10.0f
#define PLATFORM_COLOR_R 0.5f
#define PLATFORM_COLOR_G 0.3f
#define PLATFORM_COLOR_B 0.1f

class PlatformGenerator
{
private:
    float lastGeneratedHeight;
    int sections;
    float spacing;
    float platformWidth;
    float platformHeight;
    float screenLeft;
    float screenRight;
    float generationAhead;
    int lastSection = -1;

    float getSectionCenter(int section);
    void (*platformDrawFunc)(float, float);

public:
    PlatformGenerator(int sections, float spacing, float platformWidth, float platformHeight,
                      float screenLeft, float screenRight, float generationAhead,
                      void (*drawFunc)(float, float));

    void generatePlatforms(std::vector<StaticObject *> &platforms, float cameraY);
};

#endif
