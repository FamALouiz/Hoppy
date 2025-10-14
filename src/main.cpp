#include "game_window/game_window.h"
#include <GL/glut.h>
#include <stdio.h>

int main(int argc, char **argv)
{
    GameWindow *window = GameWindow::getInstance();

    bool startFullscreen = true;
    window->create(argc, argv, 800, 600, "Hoppy - OpenGL Game", startFullscreen);

    window->setDisplayCallback(display);
    window->setKeyboardCallback(keyboard);
    window->setSpecialCallback(specialKeys);

    window->run();

    GameWindow::destroy();

    return 0;
}
