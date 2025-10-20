#ifndef JETPACK_H
#define JETPACK_H

#include "generators/powerups/powerups.h"

#define JETPACK_SPAWN_RATE 0.15f
#define JETPACK_DURATION 3.0f
#define JETPACK_SPEED 3.0f
#define JETPACK_COLOR_R 0.2f
#define JETPACK_COLOR_G 0.6f
#define JETPACK_COLOR_B 1.0f

class Player;
class Jetpack : public Powerup
{
private:
    Player *player;
    static void defaultDrawFunc(float x, float y);

public:
    Jetpack(float x, float y, Player *player);
    Jetpack(float x, float y, Player *player, void (*drawFunc)(float, float));
    ~Jetpack();

    void activate() override;
    void deactivate() override;
};

#endif
