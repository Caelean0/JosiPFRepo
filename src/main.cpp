#include <cstdlib>
#include <string>

#include "raylib.h"

#include "config.h"
#include "Sprite.h"

int main() {
    // Raylib initialization
    // Project name, screen size, fullscreen mode etc. can be specified in the config.h.in file
    InitWindow(Game::ScreenWidth, Game::ScreenHeight, Game::PROJECT_NAME);
    SetTargetFPS(60);

#ifdef GAME_START_FULLSCREEN
    ToggleFullscreen();
#endif

    // Your own initialization code here
    // ...
    // ...
    Texture2D myTexture = LoadTexture("assets/graphics/testimage.png");
    Texture2D backgroundTexture = LoadTexture("assets/graphics/backgrounds/testimageW.png");

    Sprite *mySprite = new Sprite({10, 10}, 120, 120, myTexture);
    Sprite *mySprite2 = new Sprite({120, 210}, 120, 120, myTexture);
    Color backgroundColor = WHITE;
    std::string message = "Startup successful!";
    Color textColor = BLACK;
    int counterTime = 0;



    // Main game loop
    while (!WindowShouldClose()) // Detect window close button or ESC key
    {
        // Updates that are made by frame are coded here
        // ...
        // ...

        backgroundColor = mySprite -> UpdatePosition(&mySprite, myTexture);
        mySprite2 -> UpdatePosition(&mySprite2, myTexture);
       if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
       {
           if (mySprite -> checkCollision() || mySprite2 -> checkCollision())
           {
               message = "HIT!";
               textColor = PURPLE;
           }
       }
       if (message == "HIT!")
       {
            counterTime++;
            if (counterTime > 45)
            {
                message = "Back to normal...";
                textColor = BLACK;
                counterTime = 0;
            }
       }



        BeginDrawing();
            // You can draw on the screen between BeginDrawing() and EndDrawing()
            // ...
            // ...


            ClearBackground(backgroundColor);
        DrawTexturePro(backgroundTexture, {0, 0, (float)backgroundTexture.width, (float)backgroundTexture.height}, {0, 0, (float)GetScreenWidth(), (float)GetScreenHeight()}, {0, 0}, 0,
                       MAROON);

        DrawText(message.c_str(), 10, 10, 60, textColor);
            mySprite -> Draw();
            mySprite2 -> Draw();

        EndDrawing();
    } // Main game loop end

    // De-initialization here
    // ...
    // ...
    UnloadTexture(myTexture);

    // Close window and OpenGL context
    CloseWindow();

    return EXIT_SUCCESS;
}
