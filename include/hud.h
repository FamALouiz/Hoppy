#ifndef HUD_H
#define HUD_H

#include <GL/glut.h>
#include "player.h"
#include "lava.h"

#define HUD_SPRITE_PATH "C:\\Users\\fam\\OneDrive\\Desktop\\GIU\\Semester 7\\Graphics\\Hoppy\\assets\\sprites\\hud.png"
#define LAVA_WARNING_SPRITE_PATH "C:\\Users\\fam\\OneDrive\\Desktop\\GIU\\Semester 7\\Graphics\\Hoppy\\assets\\sprites\\lava_warning"
#define HUD_SPRITE_COLS 16
#define HUD_SPRITE_ROWS 16
#define HUD_HEART_FILLED_ROW 6
#define HUD_HEART_FILLED_COL 8
#define HUD_HEART_EMPTY_ROW 6
#define HUD_HEART_EMPTY_COL 12
#define HUD_KEY_ROW 0
#define HUD_KEY_COL 0
#define HUD_WARNING_LOW_ROW 8
#define HUD_WARNING_LOW_COL 0
#define HUD_WARNING_MED_ROW 8
#define HUD_WARNING_MED_COL 1
#define HUD_WARNING_HIGH_ROW 8
#define HUD_WARNING_HIGH_COL 2
#define HUD_HEART_SIZE 0.12f
#define HUD_ICON_SIZE 0.08f
#define HUD_BACKGROUND_COLOR_R 0.1f
#define HUD_BACKGROUND_COLOR_G 0.1f
#define HUD_BACKGROUND_COLOR_B 0.15f
#define HUD_BACKGROUND_ALPHA 0.4f
#define HUD_WIDTH 0.5f
#define HUD_HEIGHT 0.25f
#define HUD_PADDING 0.02f
#define HUD_SPACING 0.015f
#define LAVA_CRITICAL_DISTANCE 0.2f
#define LAVA_WARNING_DISTANCE 0.9f

class HUD
{
private:
    Player *player;
    Lava *lava;
    static GLuint spriteTexture;
    static GLuint lavaWarningTexture;
    static bool textureLoaded;
    static void loadTexture();
    void drawHeart(float x, float y, bool filled);
    void drawIcon(float x, float y, int row, int col, float size);
    void drawWarningLevel(float x, float y, int row, int col, float size, int warningLevel);
    void drawBackground(float camY);
    void drawNumber(float x, float y, int number);
    int getLavaWarningLevel(float camY);

public:
    HUD(Player *player, Lava *lava);
    ~HUD();

    void draw(float camY);
    static void cleanupTexture();
};

#endif
