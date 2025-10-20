#include "hud.h"
#include "stb_image.h"
#include <iostream>

GLuint HUD::spriteTexture = 0;
bool HUD::textureLoaded = false;

void HUD::loadTexture()
{
    if (textureLoaded)
        return;

    int width, height, channels;
    unsigned char *data = stbi_load(HUD_SPRITE_PATH, &width, &height, &channels, 4);

    if (!data)
    {
        std::cerr << "Failed to load HUD texture: " << HUD_SPRITE_PATH << std::endl;
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

HUD::HUD(Player *player) : player(player)
{
    loadTexture();
}

HUD::~HUD()
{
}

void HUD::drawBackground(float camY)
{
    glDisable(GL_TEXTURE_2D);

    float screenBottom = camY - 1.0f;
    float hudLeft = -1.0f;
    float hudRight = hudLeft + HUD_WIDTH;
    float hudBottom = screenBottom;
    float hudTop = hudBottom + HUD_HEIGHT;

    glBegin(GL_QUADS);
    glColor4f(HUD_BACKGROUND_COLOR_R, HUD_BACKGROUND_COLOR_G, HUD_BACKGROUND_COLOR_B, HUD_BACKGROUND_ALPHA);
    glVertex2f(hudLeft, hudBottom);
    glVertex2f(hudRight, hudBottom);
    glVertex2f(hudRight, hudTop);
    glVertex2f(hudLeft, hudTop);
    glEnd();
}

void HUD::drawHeart(float x, float y, bool filled)
{
    if (!textureLoaded)
        return;

    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, spriteTexture);
    glColor4f(1.0f, 1.0f, 1.0f, 1.0f);

    int row = filled ? HUD_HEART_FILLED_ROW : HUD_HEART_EMPTY_ROW;
    int col = filled ? HUD_HEART_FILLED_COL : HUD_HEART_EMPTY_COL;

    float texLeft = (float)col / HUD_SPRITE_COLS;
    float texRight = (float)(col + 2) / HUD_SPRITE_COLS;
    float texTop = (float)row / HUD_SPRITE_ROWS;
    float texBottom = (float)(row + 2) / HUD_SPRITE_ROWS;

    glBegin(GL_QUADS);
    glTexCoord2f(texLeft, texBottom);
    glVertex2f(x, y);
    glTexCoord2f(texRight, texBottom);
    glVertex2f(x + HUD_HEART_SIZE, y);
    glTexCoord2f(texRight, texTop);
    glVertex2f(x + HUD_HEART_SIZE, y + HUD_HEART_SIZE);
    glTexCoord2f(texLeft, texTop);
    glVertex2f(x, y + HUD_HEART_SIZE);
    glEnd();

    glDisable(GL_TEXTURE_2D);
}

void HUD::draw(float camY)
{
    if (!player)
        return;

    drawBackground(camY);

    int maxLives = 3;
    int currentLives = player->getLives();

    float screenBottom = camY - 1.0f;
    float heartY = screenBottom + HUD_PADDING;
    float startX = -1.0f + HUD_PADDING;

    for (int i = 0; i < maxLives; i++)
    {
        float heartX = startX + i * (HUD_HEART_SIZE + HUD_PADDING / 2.0f);
        bool filled = i < currentLives;
        drawHeart(heartX, heartY, filled);
    }
}

void HUD::cleanupTexture()
{
    if (textureLoaded)
    {
        glDeleteTextures(1, &spriteTexture);
        textureLoaded = false;
    }
}
