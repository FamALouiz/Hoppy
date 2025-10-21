#include "meteor.h"
#include "stb_image.h"
#include <iostream>
#include <cmath>

GLuint Meteor::texture = 0;
bool Meteor::textureLoaded = false;
Meteor *Meteor::currentDrawingMeteor = nullptr;

void Meteor::loadTexture()
{
    if (textureLoaded)
        return;

    int width, height, channels;
    unsigned char *data = stbi_load(METEOR_SPRITE_PATH, &width, &height, &channels, 4);

    if (!data)
    {
        std::cerr << "Failed to load meteor texture: " << stbi_failure_reason() << std::endl;
        return;
    }

    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
    stbi_image_free(data);
    textureLoaded = true;
}

void Meteor::defaultDrawFunc(float x, float y)
{
    if (!currentDrawingMeteor)
        return;

    float rotation = currentDrawingMeteor->rotation;
    float meteorSize = currentDrawingMeteor->meteorSize;

    if (!textureLoaded)
        loadTexture();

    glPushMatrix();
    glTranslatef(x, y, 0.0f);
    glRotatef(rotation, 0.0f, 0.0f, 1.0f);

    if (textureLoaded)
    {
        glEnable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D, texture);
        glColor4f(1.0f, 1.0f, 1.0f, 1.0f);

        glBegin(GL_QUADS);
        glTexCoord2f(0.0f, 1.0f);
        glVertex2f(-meteorSize, -meteorSize);
        glTexCoord2f(1.0f, 1.0f);
        glVertex2f(meteorSize, -meteorSize);
        glTexCoord2f(1.0f, 0.0f);
        glVertex2f(meteorSize, meteorSize);
        glTexCoord2f(0.0f, 0.0f);
        glVertex2f(-meteorSize, meteorSize);
        glEnd();

        glDisable(GL_TEXTURE_2D);
    }
    else
    {
        const int segments = 16;
        glBegin(GL_TRIANGLE_FAN);
        glColor3f(0.8f, 0.2f, 0.1f);
        glVertex2f(0.0f, 0.0f);
        for (int i = 0; i <= segments; i++)
        {
            float angle = 2.0f * 3.14159f * i / segments;
            float cx = meteorSize * cos(angle);
            float cy = meteorSize * sin(angle);
            glVertex2f(cx, cy);
        }
        glEnd();
    }

    glPopMatrix();
}

Meteor::Meteor(float x, float y, float size, float terminalVelocityX, float terminalVelocityY, float gravity)
    : PhysicsObject(x, y, terminalVelocityX, terminalVelocityY, defaultDrawFunc),
      rotation(0.0f), meteorSize(size), showWarning(true), warningX(x), warningTimer(0.0f)
{
    setVelocity(0.0f, 0.0f);
    setAcceleration(0.0f, gravity);
    setCollisionCircle(meteorSize);
}

Meteor::~Meteor()
{
}

void Meteor::draw()
{
    currentDrawingMeteor = this;
    PhysicsObject::draw();
    currentDrawingMeteor = nullptr;
}

void Meteor::update(float deltaTime)
{
    PhysicsObject::update(deltaTime);
    rotation += METEOR_ROTATION_SPEED * deltaTime;
    if (rotation >= 360.0f)
        rotation -= 360.0f;

    if (showWarning)
        warningTimer += deltaTime;
}

void Meteor::cleanupTexture()
{
    if (textureLoaded)
    {
        glDeleteTextures(1, &texture);
        textureLoaded = false;
    }
}
