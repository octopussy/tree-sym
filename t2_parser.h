#ifndef T2_PARSER_H
#define T2_PARSER_H

#include <string>

#include "t2.h"

enum class T2Token {
    Unknown,
    L_Brace,
    R_Brace,
    NodeLeft,
    NodeRight
};

class T2Parser
{
    std::string input;
    int inputLength;
    int ptr = 0;
public:
    T2Parser() = default;

    T2Node* parse(const std::string& inputStr);

private:
    T2Node* parseNode();
    bool consumeToken(T2Token token);
    bool lookupToken(T2Token& out, bool consume);
    bool consumeLiteral(std::string& out);
    void consumeWhitespace();
};

#endif //T2_PARSER_H
