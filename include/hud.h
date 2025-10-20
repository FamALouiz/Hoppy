#ifndef HUD_H
#define HUD_H

#include <GL/glut.h>
#include "player.h"

#define HUD_SPRITE_PATH "C:\\Users\\fam\\OneDrive\\Desktop\\GIU\\Semester 7\\Graphics\\Hoppy\\assets\\sprites\\hud.png"
#define HUD_SPRITE_COLS 16
#define HUD_SPRITE_ROWS 16
#define HUD_HEART_FILLED_ROW 6
#define HUD_HEART_FILLED_COL 8
#define HUD_HEART_EMPTY_ROW 6
#define HUD_HEART_EMPTY_COL 12
#define HUD_HEART_SIZE 0.12f
#define HUD_BACKGROUND_COLOR_R 0.1f
#define HUD_BACKGROUND_COLOR_G 0.1f
#define HUD_BACKGROUND_COLOR_B 0.15f
#define HUD_BACKGROUND_ALPHA 0.4f
#define HUD_WIDTH 0.6f
#define HUD_HEIGHT 0.2f
#define HUD_PADDING 0.02f

class HUD
{
private:
    Player *player;
    static GLuint spriteTexture;
    static bool textureLoaded;
    static void loadTexture();
    void drawHeart(float x, float y, bool filled);
    void drawBackground(float camY);

public:
    HUD(Player *player);
    ~HUD();

    void draw(float camY);
    static void cleanupTexture();
};

#endif
