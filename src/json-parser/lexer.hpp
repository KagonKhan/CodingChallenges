#ifndef CODING_CHALLENGES_JSON_PARSER_LEXER_HPP
#define CODING_CHALLENGES_JSON_PARSER_LEXER_HPP

#include <string>
#include <vector>

enum class TokenType
{
    BRACE_OPEN, BRACE_CLOSE,
    BRACKET_OPEN, BRACKET_CLOSE,
    COLON, COMMA,

    TRUE, FALSE,
    STRING,
    NUMBER,
    NULL_VALUE,

    ERROR, END,
};

struct Token
{
    TokenType type;
    std::string value;
};


class Lexer
{
public:
    explicit Lexer() = default;
    explicit Lexer(std::string const& input);

    void read(std::string const& input);

    Token peek() const { return (current_ >= tokens_.size())? Token {TokenType::ERROR, ""} : tokens_[current_];  }
    Token next()       { return (current_ >= tokens_.size())? Token {TokenType::ERROR, ""} : tokens_[current_++]; }

private:
    std::size_t        current_ = {0};
    std::vector<Token> tokens_  = {};
};

#endif // CODING_CHALLENGES_JSON_PARSER_LEXER_HPP
