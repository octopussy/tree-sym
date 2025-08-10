#include <iostream>
#include <vector>
#include "raylib.h"

struct Node
{
    int value;
    Node* left;
    Node* right;
};

void collectChildren(std::vector<Node*>& nodes, bool rightFirst)
{
    std::vector<Node*> collected;
    for (const auto& node : nodes)
    {
        if (node == nullptr) continue;
        if (rightFirst)
        {
            collected.push_back(node->right);
            collected.push_back(node->left);
        }
        else
        {
            collected.push_back(node->left);
            collected.push_back(node->right);
        }
    }
    nodes = collected;
}

bool isTreeSymmetric(const Node& root)
{
    std::vector<Node*> leftNodes;
    std::vector<Node*> rightNodes;
    leftNodes.push_back(root.left);
    rightNodes.push_back(root.right);

    while (!leftNodes.empty() && !rightNodes.empty())
    {
        if (rightNodes.size() != leftNodes.size())
        {
            return false;
        }
        for (int i = 0; i < leftNodes.size(); i++)
        {
            Node* l = leftNodes[i];
            Node* r = rightNodes[i];
            if ((l == nullptr && r != nullptr) || (l != nullptr && r == nullptr) || (l != nullptr && r != nullptr && l->value != r->value))
            {
                return false;
            }
        }
        collectChildren(leftNodes, false);
        collectChildren(rightNodes, true);
    }
    return true;
}

bool sample0();
bool sample1();

#define WINDOW_WIDTH 1280
#define WINDOW_HEIGHT 1280

int main()
{
    std::cout << "Sample0: " << sample0() << std::endl;
    std::cout << "Sample1: " << sample1() << std::endl;
    InitWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "Draw!!!");

    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(BLACK);
        DrawLine()
        // DrawText("Congrats! You created your first window!", 190, 200, 20, LIGHTGRAY);
        EndDrawing();
    }

    CloseWindow();

    return 0;
}

bool sample0()
{
    const auto root = Node{
        .value = 0,
        .left = new Node{
            .value = 1,
            .left = new Node{
                .value = 2,
            }
        },
        .right = new Node{
            .value = 1,
            .right = new Node{
                .value = 2,
            }
        },
    };

    return isTreeSymmetric(root);
}

bool sample1()
{
    const auto root = Node{
        .value = 0,
        .left = new Node{
            .value = 1,
            .left = new Node{
                .value = 2,
                .left = new Node{
                    .value = 3,
                    .left = new Node{
                        .value = 4,
                    },
                }
            },
            .right = new Node{
                .value = 2,
            }
        },
        .right = new Node{
            .value = 1,
            .left = new Node{
                .value = 2,
            },
            .right = new Node{
                .value = 2,
                .right = new Node{
                    .value = 3,
                    .right = new Node{
                        .value = 4,
                    },
                }
            }
        },
    };

    return isTreeSymmetric(root);
}
