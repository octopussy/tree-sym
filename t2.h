#ifndef T2_H
#define T2_H

#include <string>

struct T2Node
{
    std::string value;
    T2Node* left;
    T2Node* right;
};

T2Node* parseT2(const std::string& input);

#endif //T2_H
