#ifndef PARSER_H
#define PARSER_H
#include <deque>

#include "token.h"
#include "value.h"

class Parser {
private:
    std::deque<TokenPtr> tokens;
    ValuePtr parseModifier(std::string modifierType);

public:
    Parser(std::deque<TokenPtr> tokens) : tokens(std::move(tokens)) {}
    ValuePtr parse();
    ValuePtr parseTails();
};

#endif