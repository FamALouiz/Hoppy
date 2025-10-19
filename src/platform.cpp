#include "platform.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#include <iostream>

GLuint Platform::spriteTexture = 0;
bool Platform::textureLoaded = false;

void Platform::loadTexture()
{
    if (textureLoaded)
        return;

    int width, height, channels;
    unsigned char *data = stbi_load(PLATFORM_SPRITE_PATH, &width, &height, &channels, 4);

    if (!data)
    {
        std::cerr << "Failed to load platform texture: " << PLATFORM_SPRITE_PATH << std::endl;
        std::cerr << "STB Error: " << stbi_failure_reason() << std::endl;
        return;
    }

    glGenTextures(1, &spriteTexture);
    glBindTexture(GL_TEXTURE_2D, spriteTexture);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);

    stbi_image_free(data);
    textureLoaded = true;
}

void Platform::defaultDrawFunc(float x, float y)
{
    if (!textureLoaded)
        loadTexture();

    if (!textureLoaded)
    {
        glBegin(GL_QUADS);
        glColor3f(PLATFORM_COLOR_R, PLATFORM_COLOR_G, PLATFORM_COLOR_B);
        glVertex2f(x - PLATFORM_WIDTH / 2.0f, y - PLATFORM_HEIGHT / 2.0f);
        glVertex2f(x + PLATFORM_WIDTH / 2.0f, y - PLATFORM_HEIGHT / 2.0f);
        glVertex2f(x + PLATFORM_WIDTH / 2.0f, y + PLATFORM_HEIGHT / 2.0f);
        glVertex2f(x - PLATFORM_WIDTH / 2.0f, y + PLATFORM_HEIGHT / 2.0f);
        glEnd();
        return;
    }

    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, spriteTexture);
    glColor4f(1.0f, 1.0f, 1.0f, 1.0f);

    int row = PLATFORM_SPRITE_INDEX / PLATFORM_SPRITE_COLS;
    int col = PLATFORM_SPRITE_INDEX % PLATFORM_SPRITE_COLS;

    float texLeft = (float)col / PLATFORM_SPRITE_COLS;
    float texRight = (float)(col + 1) / PLATFORM_SPRITE_COLS;
    float texTop = (float)row / PLATFORM_SPRITE_ROWS;
    float texBottom = (float)(row + 1) / PLATFORM_SPRITE_ROWS;

    float spriteWidth = PLATFORM_WIDTH / 7.0f;

    for (int i = 0; i < 7; i++)
    {
        float leftX = x - PLATFORM_WIDTH / 2.0f + i * spriteWidth;
        float rightX = leftX + spriteWidth;

        glBegin(GL_QUADS);
        glTexCoord2f(texLeft, texBottom);
        glVertex2f(leftX, y - PLATFORM_HEIGHT / 2.0f);
        glTexCoord2f(texRight, texBottom);
        glVertex2f(rightX, y - PLATFORM_HEIGHT / 2.0f);
        glTexCoord2f(texRight, texTop);
        glVertex2f(rightX, y + PLATFORM_HEIGHT / 2.0f);
        glTexCoord2f(texLeft, texTop);
        glVertex2f(leftX, y + PLATFORM_HEIGHT / 2.0f);
        glEnd();
    }

    glDisable(GL_TEXTURE_2D);
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

void Platform::cleanupTexture()
{
    if (textureLoaded)
    {
        glDeleteTextures(1, &spriteTexture);
        textureLoaded = false;
    }
}
