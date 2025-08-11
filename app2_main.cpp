#include <filesystem>
#include <vector>
#include "raylib.h"
#include "raymath.h"

#define WINDOW_WIDTH 1280
#define WINDOW_HEIGHT 1280
#define FONT_SIZE 25

typedef struct
{
    Vector2 position;
    Vector2 velocity;
    float radius;
    Color color;
} Ball;

int main()
{
    std::vector<Ball> balls{};
    const int moveSpeed = 100.f;
    float tx = 0;
    float ty = 0;
    std::filesystem::path path = std::filesystem::current_path();
    // SetConfigFlags(FLAG_WINDOW_RESIZABLE); // Make the window resizable
    InitWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "Balls!!!");
    Texture pig = LoadTexture("data/pig.jpg");

    while (!WindowShouldClose())
    {
        float dt = GetFrameTime();

        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
        {
            int x = GetMouseX();
            int y = GetMouseY();
            Vector2 dir = Vector2Rotate(Vector2(GetRandomValue(300, 800), 0.f), GetRandomValue(0, 360) * DEG2RAD);
            float radius = GetRandomValue(10, 50);
            Color color = ColorFromHSV(GetRandomValue(0, 360), 1.f, 1.f);
            balls.push_back(Ball{.position = Vector2(x, y), .velocity = dir, .radius = radius, .color = color});
        }
        if (IsKeyDown(KEY_W))
        {
            ty -= moveSpeed * dt;
        }
        if (IsKeyDown(KEY_S))
        {
            ty += moveSpeed * dt;
        }
        if (IsKeyDown(KEY_A))
        {
            tx -= moveSpeed * dt;
        }
        if (IsKeyDown(KEY_D))
        {
            tx += moveSpeed * dt;
        }
        BeginDrawing();
        ClearBackground(BLACK);
        DrawTexture(pig, static_cast<int>(tx), static_cast<int>(ty), WHITE);

        for (auto& ball : balls)
        {
            DrawCircle(ball.position.x, ball.position.y, ball.radius, ball.color);
            Vector2 newPosition = ball.position + ball.velocity * dt;
            if (ball.velocity.x > 0)
            {
                if (newPosition.x + ball.radius >= WINDOW_WIDTH)
                {
                    newPosition.x = WINDOW_WIDTH - ball.radius;
                    ball.velocity.x *= -1;
                }
            }
            if (ball.velocity.x < 0)
            {
                if (newPosition.x - ball.radius < 0)
                {
                    newPosition.x = ball.radius;
                    ball.velocity.x *= -1;
                }
            }
            if (ball.velocity.y > 0)
            {
                if (newPosition.y + ball.radius >= WINDOW_HEIGHT)
                {
                    newPosition.y = WINDOW_HEIGHT - ball.radius;
                    ball.velocity.y *= -1;
                }
            }
            if (ball.velocity.y < 0)
            {
                if (newPosition.y - ball.radius < 0)
                {
                    newPosition.y = ball.radius;
                    ball.velocity.y *= -1;
                }
            }
            ball.position = newPosition;
        }
        EndDrawing();
    }

    CloseWindow();

    return 0;
}

// DrawText("Congrats! You created your first window!", 190, 200, 20, LIGHTGRAY);
