#ifndef GAME_WINDOW_H
#define GAME_WINDOW_H

#include <GL/glut.h>
#include <string>
#include "game_window/utils.h"

class GameWindow
{
private:
    static GameWindow *instance;

    int width;
    int height;
    int windowID;
    bool isFullscreen;
    std::string title;

    int windowedWidth;
    int windowedHeight;
    int windowedPosX;
    int windowedPosY;

    GameWindow();
    GameWindow(const GameWindow &) = delete;
    GameWindow &operator=(const GameWindow &) = delete;

public:
    ~GameWindow();

    static GameWindow *getInstance();

    void create(int argc, char **argv, int w, int h, const char *windowTitle, bool fullscreen = false);

    void toggleFullscreen();
    void setFullscreen(bool fullscreen);
    void resize(int w, int h);
    void setTitle(const char *newTitle);

    int getWidth() const { return width; }
    int getHeight() const { return height; }
    int getWindowID() const { return windowID; }
    bool getIsFullscreen() const { return isFullscreen; }
    float getAspectRatio() const { return static_cast<float>(width) / static_cast<float>(height); }

    void screenToNormalized(int screenX, int screenY, float &normX, float &normY) const;
    void normalizedToScreen(float normX, float normY, int &screenX, int &screenY) const;

    void setDisplayCallback(void (*func)(void));
    void setReshapeCallback(void (*func)(int, int));
    void setKeyboardCallback(void (*func)(unsigned char, int, int));
    void setSpecialCallback(void (*func)(int, int, int));
    void setMouseCallback(void (*func)(int, int, int, int));
    void setMotionCallback(void (*func)(int, int));
    void setIdleCallback(void (*func)(void));
    void setTimerCallback(void (*func)(int), unsigned int milliseconds, int value);

    void run();
    static void destroy();
};

#endif
