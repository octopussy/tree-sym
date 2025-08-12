#include "raylib.h"
#include "raymath.h"
#include "t2.h"
#include "t2_parser.h"
#include <fstream>
#include <iostream>
#include <memory>

#define WINDOW_WIDTH  1280
#define WINDOW_HEIGHT 1000
#define FONT_SIZE     20

static float angleFalloff = 0.95f;

void drawTree(const T2Node* root, Vector2 from, Vector2 axisDir, float sideAngle) {
    static char buf[255];
    snprintf(buf, 255, "%s", root->value.c_str());
    Vector2 dirLeft  = Vector2Rotate(axisDir, sideAngle);
    Vector2 dirRight = Vector2Rotate(axisDir, -sideAngle);
    Vector2 toLeft   = from + dirLeft;
    Vector2 toRight  = from + dirRight;
    if (root->left != nullptr) {
        DrawLine(from.x, from.y, toLeft.x, toLeft.y, GREEN);
    }
    if (root->right != nullptr) {
        DrawLine(from.x, from.y, toRight.x, toRight.y, RED);
    }

    DrawCircle(from.x, from.y, 30, Color(255, 255, 255, 200));
    int textWidth = MeasureText(buf, FONT_SIZE);
    DrawText(buf, from.x - textWidth / 2, from.y - FONT_SIZE / 2, FONT_SIZE, BLACK);

    if (root->left != nullptr) {
        drawTree(root->left, toLeft, dirLeft, sideAngle * angleFalloff);
    }
    if (root->right != nullptr) {
        drawTree(root->right, toRight, dirRight, sideAngle * angleFalloff);
    }
}

T2Node* loadTree(std::string fileName) {
    std::ifstream inputFile(fileName);
    if (!inputFile.is_open()) {
        return nullptr;
    }
    std::string fileContent;
    std::string line;
    while (std::getline(inputFile, line)) {
        fileContent += line;
    }
    auto parser = std::make_unique<T2Parser>();
    inputFile.close();
    return parser->parse(fileContent);
}

T2Node* tree01 = nullptr;
T2Node* tree02 = nullptr;

void loadTrees() {
    tree01 = loadTree("data/test.t2");
    tree02 = loadTree("data/test2.t2");
}

int main() {
    const float cameraSpeed = 200.f;

    loadTrees();
    InitWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "Draw!!!");

    Camera2D camera = Camera2D{.zoom = 1.f};
    while (!WindowShouldClose()) {
        float frameTime = GetFrameTime();
        if (IsKeyDown(KEY_MINUS)) {
            angleFalloff -= frameTime;
        }
        if (IsKeyDown(KEY_EQUAL)) {
            angleFalloff += frameTime;
        }
        if (IsKeyDown(KEY_W)) {
            camera.offset.y += frameTime * cameraSpeed;
        }
        if (IsKeyDown(KEY_S)) {
            camera.offset.y -= frameTime * cameraSpeed;
        }
        if (IsKeyDown(KEY_A)) {
            camera.offset.x += frameTime * cameraSpeed;
        }
        if (IsKeyDown(KEY_D)) {
            camera.offset.x -= frameTime * cameraSpeed;
        }
        if (IsKeyPressed(KEY_SPACE)) {
            loadTrees();
        }
        BeginDrawing();
        BeginMode2D(camera);
        ClearBackground(BLACK);
        if (tree01 != nullptr) {
            drawTree(tree01, Vector2{WINDOW_WIDTH / 2, 200}, Vector2{0, 100}, 30 * DEG2RAD * angleFalloff);
        }
        if (tree02 != nullptr) {
            drawTree(tree02, Vector2{WINDOW_WIDTH / 2, 500}, Vector2{0, 100}, 30 * DEG2RAD * angleFalloff);
        }
        EndMode2D();
        EndDrawing();
    }

    CloseWindow();

    return 0;
}
