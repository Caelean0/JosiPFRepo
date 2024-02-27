//
// Created by keanu on 25.01.2024.
//

#ifndef RAYLIBSTARTER_SPRITE_H
#define RAYLIBSTARTER_SPRITE_H


#include <algorithm>
#include <vector>
#include "raylib.h"

class Sprite
{
private:
    int internalCounter;
    Vector2 position;
    Vector2 velocity;
    const float width;
    const float height;
    const Texture2D texture;
    Rectangle hitbox;
    std::vector<std::vector<bool>> collisionMap;


    void updateHitbox();
    void die(Sprite **sprite, Texture2D texture2D);

    void renderCollisionMap();

public:
    Sprite();
    Sprite(Vector2 pPosition, float pWidth, float pHeight, Texture2D pTexture);
    ~Sprite();
    void Draw();

    bool checkCollision();

    Color UpdatePosition(Sprite **sprite, Texture2D texture2D);

};


#endif //RAYLIBSTARTER_SPRITE_H
