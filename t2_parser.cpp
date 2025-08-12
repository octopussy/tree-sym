#include "t2_parser.h"

T2Node* T2Parser::parse(const std::string& inputStr) {
    this->input       = inputStr;
    this->inputLength = inputStr.length();
    this->ptr         = 0;
    return parseNode();
}

T2Node* T2Parser::parseNode() {
    std::string value;
    if (!consumeLiteral(value)) {
        return nullptr;
    }
    T2Node* node = new T2Node{.value = value};
    if (consumeToken(T2Token::L_Brace)) {
        T2Token nextToken;
        while (lookupToken(nextToken, true)) {
            switch (nextToken) {
            case T2Token::L_Brace: return nullptr; // TODO: return T2ParseResult::Failure
            case T2Token::R_Brace: return node;
            case T2Token::NodeLeft:
                node->left = parseNode();
                break;
            case T2Token::NodeRight:
                node->right = parseNode();
                break;
                default: return nullptr;
            }
        }
        if (!consumeToken(T2Token::R_Brace)) {
            return nullptr;
        }
    }

    return node;
}

static T2Token charToToken(char ch) {
    switch (ch) {
    case '{': return T2Token::L_Brace;
    case '}': return T2Token::R_Brace;
    case '<': return T2Token::NodeLeft;
    case '>': return T2Token::NodeRight;
    default: return T2Token::Unknown;
    }
}

bool T2Parser::consumeToken(T2Token token) {
    consumeWhitespace();
    if (charToToken(input[ptr]) != token) {
        return false;
    }
    ++ptr;
    return true;
}

bool T2Parser::lookupToken(T2Token& out, bool consume) {
    consumeWhitespace();
    T2Token token = charToToken(input[ptr]);
    if (token == T2Token::Unknown) {
        return false;
    }
    if (consume) {
        ++ptr;
    }
    out = token;
    return true;
}

bool T2Parser::consumeLiteral(std::string& out) {
    out.clear();
    consumeWhitespace();
    while (ptr < inputLength && std::isalnum(input[ptr])) {
        out.push_back(input[ptr]);
        ++ptr;
    }

    return !out.empty();
}

void T2Parser::consumeWhitespace() {
    while (ptr < inputLength && std::isspace(input[ptr++])) {
    }
    if (ptr > 0) {
        --ptr;
    }
}
