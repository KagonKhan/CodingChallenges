#include "parser.hpp"

#include <iostream>


bool Parser::parse()
{
    try {
        if (lexer_.peek().type == TokenType::BRACE_OPEN) {
            parseObject();
        }
        else if (lexer_.peek().type == TokenType::BRACKET_OPEN) {
            parseArray();
        }
        else {
            throw std::runtime_error("json error");
        }

        expect(TokenType::END);
    }
    catch (std::runtime_error const& e) {
        return false;
    }

    return true;
}

void Parser::expect(TokenType expected)
{
    const TokenType type = lexer_.next().type;
    if (type != expected) {
        throw std::runtime_error("Unexpected token type");
    }
}

void Parser::parseValue()
{
    Token token = lexer_.peek();

    switch (token.type) {
    case TokenType::STRING:
    case TokenType::NUMBER:
    case TokenType::TRUE:
    case TokenType::FALSE:
    case TokenType::NULL_VALUE:
        lexer_.next();
        break;

    case TokenType::BRACE_OPEN:
        parseObject();
        break;

    case TokenType::BRACKET_OPEN:
        parseArray();
        break;

    default:
        throw std::runtime_error("Unexpected token type");
    }
}

void Parser::parseObject()
{
    if (++currentDepth_ > maxDepth_) {
        throw std::runtime_error("yoyur mom");
    }

    expect(TokenType::BRACE_OPEN);

    if (lexer_.peek().type == TokenType::BRACE_CLOSE) {
        lexer_.next();
        return;
    }

    while (true) {
        expect(TokenType::STRING);
        expect(TokenType::COLON);
        parseValue();

        if (lexer_.peek().type == TokenType::COMMA) {
            lexer_.next();
        }
        else {
            break;
        }
    }

    expect(TokenType::BRACE_CLOSE);
    --currentDepth_;
}

void Parser::parseArray()
{
    std::cout << "depth: " << currentDepth_ << std::endl;
    if (++currentDepth_ > maxDepth_) {
        throw std::runtime_error("yoyur mom");
    }

    expect(TokenType::BRACKET_OPEN);

    if (lexer_.peek().type == TokenType::BRACKET_CLOSE) {
        lexer_.next();
        return;
    }

    while (true) {
        parseValue();

        if (lexer_.peek().type == TokenType::COMMA) {
            lexer_.next();
        }
        else {
            break;
        }
    }

    expect(TokenType::BRACKET_CLOSE);
    --currentDepth_;
}
