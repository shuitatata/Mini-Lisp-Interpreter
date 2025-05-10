#include "parser.h"

#include <format>
#include <memory>

#include "./error.h"
#include "token.h"
#include "value.h"

ValuePtr Parser::parseModifier(std::string modifierName) {
    return std::make_shared<PairValue> (
        std::make_shared<SymbolValue>(modifierName),
        std::make_shared<PairValue>(
            this->parse(),
            std::make_shared<NilValue>()
        )
    );
}

ValuePtr Parser::parse() {
    auto token = std::move(tokens.front());
    tokens.pop_front();

    if (token->getType() == TokenType::NUMERIC_LITERAL) {
        auto value = static_cast<NumericLiteralToken&>(*token).getValue();
        return std::make_shared<NumericValue>(value);
    } else if (token->getType() == TokenType::STRING_LITERAL) {
        auto value = static_cast<StringLiteralToken&>(*token).getValue();
        return std::make_shared<StringValue>(value);
    } else if (token->getType() == TokenType::BOOLEAN_LITERAL) {
        auto value = static_cast<BooleanLiteralToken&>(*token).getValue();
        return std::make_shared<BooleanValue>(value);
    } else if (token->getType() == TokenType::IDENTIFIER) {
        auto value = static_cast<IdentifierToken&>(*token).getName();
        return std::make_shared<SymbolValue>(value);
    } else if (token->getType() == TokenType::LEFT_PAREN) {
        return this->parseTails();
    } else if (token->getType() == TokenType::QUOTE) {
        return this->parseModifier("quote");
    } else if (token->getType() == TokenType::QUASIQUOTE) {
        return this->parseModifier("quasiquote");
    } else if (token->getType() == TokenType::UNQUOTE) {
        return this->parseModifier("unquote");
    }

    // unimplement
    throw SyntaxError("Unimplemented");
}

ValuePtr Parser::parseTails() {
    if (tokens.front()->getType() == TokenType::RIGHT_PAREN) {
        tokens.pop_front();
        return std::make_shared<NilValue>();
    }
    // 左边的值
    auto car = this->parse();
    if (tokens.front()->getType() == TokenType::DOT) {  // 点右侧为右值
        tokens.pop_front();
        auto cdr = this->parse();
        if (tokens.empty()) {
            throw SyntaxError("EOF");
        }
        tokens.front()->getType();
        if (tokens.front()->getType() == TokenType::RIGHT_PAREN) {
            tokens.pop_front();
            return std::make_shared<PairValue>(car, cdr);
        } else {
            throw SyntaxError(std::format("There should be ')', but it is {}",
                                          tokens.front()->toString()));
        }
    } else {  // 右侧仍是列表
        auto cdr = this->parseTails();
        return std::make_shared<PairValue>(car, cdr);
    }
}
