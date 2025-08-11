//
// Created by user on 8/11/2025.
//
#include <vector>
#include "t2.h"

void collectChildren(std::vector<T2Node*>& nodes, bool rightFirst)
{
    std::vector<T2Node*> collected;
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

bool isTreeSymmetric(const T2Node& root)
{
    std::vector<T2Node*> leftNodes;
    std::vector<T2Node*> rightNodes;
    leftNodes.push_back(root.left);
    rightNodes.push_back(root.right);

    while (true)
    {
        if (rightNodes.size() != leftNodes.size())
        {
            return false;
        }
        for (int i = 0; i < leftNodes.size(); i++)
        {
            T2Node* l = leftNodes[i];
            T2Node* r = rightNodes[i];
            if ((l == nullptr && r != nullptr) || (l != nullptr && r == nullptr) || (l != nullptr && r != nullptr && l->value != r->value))
            {
                return false;
            }
        }
        collectChildren(leftNodes, false);
        collectChildren(rightNodes, true);

        if (leftNodes.empty() && rightNodes.empty())
        {
            return true;
        }
    }
}
