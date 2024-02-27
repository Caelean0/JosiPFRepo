//
// Created by keanu on 25.01.2024.
//

#include "Sprite.h"



Sprite::Sprite(Vector2 pPosition, float pWidth, float pHeight, Texture2D pTexture): width(pWidth), height(pHeight), texture(pTexture)
{
    this -> internalCounter = 0;
    this -> position = pPosition;
    this -> hitbox = {pPosition.x, pPosition.y, pWidth, pHeight};
    this -> velocity = {0.0f, 0.0f};
    this -> collisionMap = std::vector<std::vector<bool>>(this -> texture.height, std::vector<bool>(this -> texture.width));
    this -> renderCollisionMap();
}

Sprite::~Sprite()
{

}

Color Sprite::UpdatePosition(Sprite **sprite, Texture2D texture2D)
{
    static Color color = WHITE;

    this -> position.x += this -> velocity.x;
    this -> position.y += this -> velocity.y;

    if (this -> position.x + this -> width >= GetScreenWidth() || this -> position.x <= 0)
    {
        velocity.x *= -1;
        color = YELLOW;

    }
    if (this -> position.y + this -> height >= GetScreenHeight() || this -> position.y <= 0)
    {
        velocity.y *= -1;
        color = RED;
    }

    updateHitbox();
    /*this -> internalCounter++;
    if (this -> internalCounter == 120)
    {
        die(sprite, texture2D);
    }*/
    return color;

}

void Sprite::Draw()
{
    DrawTextureV(this -> texture, this -> position, Fade(WHITE, 0.5f));


}

void Sprite::updateHitbox()
{
    this -> hitbox.x = this -> position.x;
    this -> hitbox.y = this -> position.y;
}

bool Sprite::checkCollision()
{
    Vector2 mousePos = GetMousePosition();

    if (!CheckCollisionPointRec(mousePos, this -> hitbox))
    {
        return false;
    }

    int pixelX = static_cast<int>(mousePos.x - this -> position.x);
    int pixelY = static_cast<int>( mousePos.y - this -> position.y);
    if (collisionMap[pixelY][pixelX])
    {
        return true;
    }
    return false;


}

void Sprite::renderCollisionMap()
{
    Image renderImage = LoadImageFromTexture(this -> texture);
    for (int y = 0; y < renderImage.height; ++y)
    {
        for (int x = 0; x < renderImage.width; ++x)
        {
            Color pixel = GetImageColor(renderImage, x, y);
            if (pixel.a > 0)
            {
                this -> collisionMap[y][x] = true;
            } else {
                this -> collisionMap[y][x] = false;
            }
        }
    }

}

void Sprite::die(Sprite **sprite, Texture2D texture2D)
{
    delete *sprite;
    *sprite = nullptr;
    float posX = GetRandomValue(0, GetScreenWidth()-120);
    float posY = GetRandomValue(0, GetScreenHeight()-120);
    *sprite = new Sprite({posX, posY}, 120, 120, texture2D);
}
