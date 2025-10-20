#include "hud.h"
#include "stb_image.h"
#include <iostream>
#include <cmath>

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

HUD::HUD(Player *player, Lava *lava) : player(player), lava(lava)
{
    loadTexture();
}

HUD::~HUD()
{
}

void HUD::drawBackground(float camY)
{
    glDisable(GL_TEXTURE_2D);

    float screenTop = camY + 1.0f;
    float hudRight = 1.0f;
    float hudLeft = hudRight - HUD_WIDTH;
    float hudTop = screenTop;
    float hudBottom = hudTop - HUD_HEIGHT;

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

void HUD::drawIcon(float x, float y, int row, int col, float size)
{
    if (!textureLoaded)
        return;

    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, spriteTexture);

    float texLeft = (float)col / HUD_SPRITE_COLS;
    float texRight = (float)(col + 1) / HUD_SPRITE_COLS;
    float texTop = (float)row / HUD_SPRITE_ROWS;
    float texBottom = (float)(row + 1) / HUD_SPRITE_ROWS;

    glBegin(GL_QUADS);
    glColor4f(0.0f, 1.0f, 0.0f, 1.0f);
    glTexCoord2f(texLeft, texBottom);
    glVertex2f(x, y);
    glTexCoord2f(texRight, texBottom);
    glVertex2f(x + size, y);
    glTexCoord2f(texRight, texTop);
    glVertex2f(x + size, y + size);
    glTexCoord2f(texLeft, texTop);
    glVertex2f(x, y + size);
    glEnd();

    glDisable(GL_TEXTURE_2D);
}

void HUD::drawNumber(float x, float y, int number)
{
    if (!textureLoaded)
        return;

    glDisable(GL_TEXTURE_2D);
    glColor4f(1.0f, 1.0f, 1.0f, 1.0f);

    std::string numStr = std::to_string(number);
    float charWidth = 0.04f;
    float charHeight = 0.06f;

    for (size_t i = 0; i < numStr.length(); i++)
    {
        char c = numStr[i];
        float offsetX = x + i * charWidth;

        glRasterPos2f(offsetX, y);
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, c);
    }
}

int HUD::getLavaWarningLevel(float camY)
{
    if (!player || !lava)
        return 2;

    float playerY = player->getY();
    float lavaY = lava->getY() + LAVA_HEIGHT / 2.0f;
    float distance = playerY - lavaY;

    std::cout << "Lava Y: " << lavaY << " player y " << playerY << " Distance: " << distance << std::endl;
    if (distance <= LAVA_CRITICAL_DISTANCE)
    {
        return 0;
    }
    else if (distance <= LAVA_WARNING_DISTANCE)
    {
        return 1;
    }
    else
    {
        return 2;
    }
}

void HUD::draw(float camY)
{
    if (!player)
        return;

    drawBackground(camY);

    float screenTop = camY + 1.0f;
    float hudRight = 1.0f;
    float startX = hudRight - HUD_WIDTH + HUD_PADDING;
    float currentY = screenTop - HUD_PADDING;

    int maxLives = 3;
    int currentLives = player->getLives();

    for (int i = 0; i < maxLives; i++)
    {
        float heartX = startX + i * (HUD_HEART_SIZE + HUD_SPACING);
        bool filled = i < currentLives;
        drawHeart(heartX, currentY - HUD_HEART_SIZE, filled);
    }

    currentY -= HUD_HEART_SIZE + HUD_SPACING * 2.0f;

    drawIcon(startX, currentY - HUD_ICON_SIZE, HUD_KEY_ROW, HUD_KEY_COL, HUD_ICON_SIZE);
    drawNumber(startX + HUD_ICON_SIZE + HUD_SPACING, currentY - HUD_ICON_SIZE + 0.01f, player->getKeys());

    currentY -= HUD_ICON_SIZE + HUD_SPACING * 2.0f;

    int warningLevel = getLavaWarningLevel(camY);
    std::cout << "Lava Warning Level: " << warningLevel << std::endl;
    int warningRow = HUD_WARNING_LOW_ROW;
    int warningCol = HUD_WARNING_LOW_COL;

    if (warningLevel == 1)
    {
        warningRow = HUD_WARNING_MED_ROW;
        warningCol = HUD_WARNING_MED_COL;
    }
    else if (warningLevel == 2)
    {
        warningRow = HUD_WARNING_HIGH_ROW;
        warningCol = HUD_WARNING_HIGH_COL;
    }

    drawIcon(startX, currentY - HUD_ICON_SIZE, warningRow, warningCol, HUD_ICON_SIZE);
}

void HUD::cleanupTexture()
{
    if (textureLoaded)
    {
        glDeleteTextures(1, &spriteTexture);
        textureLoaded = false;
    }
}
