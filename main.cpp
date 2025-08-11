#include <iostream>
#include <vector>
#include "raylib.h"
#include "raymath.h"
#include "t2.h"

#define WINDOW_WIDTH 1280
#define WINDOW_HEIGHT 1280
#define FONT_SIZE 20

static float angleFalloff = 0.95f;

void drawTree(const T2Node* root, Vector2 from, Vector2 axisDir, float sideAngle)
{
    static char buf[255];
    snprintf(buf, 255, "%s", root->value.c_str());
    Vector2 dirLeft = Vector2Rotate(axisDir, sideAngle);
    Vector2 dirRight = Vector2Rotate(axisDir, -sideAngle);
    Vector2 toLeft = from + dirLeft;
    Vector2 toRight = from + dirRight;
    if (root->left != nullptr)
    {
        DrawLine(from.x, from.y, toLeft.x, toLeft.y, GREEN);
    }
    if (root->right != nullptr)
    {
        DrawLine(from.x, from.y, toRight.x, toRight.y, RED);
    }

    DrawCircle(from.x, from.y, 30, Color(255, 255, 255, 200));
    int textWidth = MeasureText(buf, FONT_SIZE);
    DrawText(buf, from.x - textWidth / 2, from.y - FONT_SIZE / 2, FONT_SIZE, BLACK);

    if (root->left != nullptr)
    {
        drawTree(root->left, toLeft, dirLeft, sideAngle * angleFalloff);
    }
    if (root->right != nullptr)
    {
        drawTree(root->right, toRight, dirRight, sideAngle * angleFalloff);
    }
}

int main()
{
    InitWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "Draw!!!");

    while (!WindowShouldClose())
    {
        float frameTime = GetFrameTime();
        if (IsKeyDown(KEY_MINUS))
        {
            angleFalloff -= frameTime;
        }
        if (IsKeyDown(KEY_EQUAL))
        {
            angleFalloff += frameTime;
        }
        BeginDrawing();
        ClearBackground(BLACK);
        drawTree(&tree01, Vector2{WINDOW_WIDTH / 2, 200}, Vector2{0, 100}, 30 * DEG2RAD * angleFalloff);
        drawTree(&tree02, Vector2{WINDOW_WIDTH / 2, 500}, Vector2{0, 100}, 30 * DEG2RAD * angleFalloff);
        // DrawText("Congrats! You created your first window!", 190, 200, 20, LIGHTGRAY);
        EndDrawing();
    }

    CloseWindow();

    return 0;
}
