#ifndef CODING_CHALLENGES_JSON_PARSER_PARSER_HPP
#define CODING_CHALLENGES_JSON_PARSER_PARSER_HPP

#include "lexer.hpp"

class Parser
{
public:
    explicit Parser(Lexer& lexer)
        : lexer_(lexer) {}

    bool parse();

private:
    Lexer& lexer_;

    std::size_t currentDepth_ = {0};
    std::size_t maxDepth_     = 19;

    void parseArray();
    void parseObject();
    void parseValue();
    void expect(TokenType expected);
};

#endif // CODING_CHALLENGES_JSON_PARSER_PARSER_HPP
