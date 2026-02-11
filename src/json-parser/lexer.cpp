#include "lexer.hpp"

#include <iostream>

Lexer::Lexer(std::string const& input)
{
    read(input);
}

void Lexer::read(std::string const& input)
{
    tokens_.resize(0);
    current_ = 0;

    for (int i = 0; i < input.length(); ) {
        char c = input[i];

        switch (c) {
        case ' ':
            break;

        case '\n':
            break;

        case '{':
            tokens_.emplace_back(TokenType::BRACE_OPEN, "{");
            break;

        case '}':
            tokens_.emplace_back(TokenType::BRACE_CLOSE, "}");
            break;

        case '[':
            tokens_.emplace_back(TokenType::BRACKET_OPEN, "[");
            break;

        case ']':
            tokens_.emplace_back(TokenType::BRACKET_CLOSE, "]");
            break;

        case ':':
            tokens_.emplace_back(TokenType::COLON, ":");
            break;

        case ',':
            tokens_.emplace_back(TokenType::COMMA, ",");
            break;

        case 'n': {
            std::cout << "null: " << input.substr(i, 4) << std::endl;
            if (input.substr(i, 4) == std::string("null")) {
                tokens_.emplace_back(TokenType::NULL_VALUE, "null");
            }
            else {
                tokens_.emplace_back(TokenType::ERROR, "");
            }

            i += 4;
            continue;
            break;
        }

        case 't': {
            // std::cout << "computed boolen: " << input.substr(i, 4) << std::endl;
            if (input.substr(i, 4) == std::string("true")) {
                tokens_.emplace_back(TokenType::TRUE, "true");
            }
            else {
                tokens_.emplace_back(TokenType::ERROR, "");
            }

            i += 4;
            continue;
            break;
        }

        case 'f': {
            // std::cout << "computed boolen: " << input.substr(i, 5) << std::endl;
            if (input.substr(i, 5) == std::string("false")) {
                tokens_.emplace_back(TokenType::FALSE, "false");
            }
            else {
                tokens_.emplace_back(TokenType::ERROR, "");
            }

            i += 5;
            continue;
            break;
        }

        case '"': {
            ++i;     // Skip '"'
            int j = i;
            while (input[j] != '"' && input[j] != '\0' ) {
                if (static_cast<unsigned char>(input[j]) < 0x20) {
                    tokens_.emplace_back(TokenType::ERROR, "Error");
                    return;
                }

                ++j;
            }

            // std::cout << "computed string: " <<  input.substr(i, j - i) << std::endl;
            tokens_.emplace_back(TokenType::STRING, input.substr(i, j - i));
            i = j + 1;     // Skip '"'

            const auto& string = tokens_.back().value;
            for (int i = 0; i < string.size(); ++i) {
                if ((string[i] == '\\') && (string.size() > 1)) {
                    if (i + 1 >= string.size()) {
                        std::cout << "size: " << string.size() << std::endl;
                        tokens_.emplace_back(TokenType::ERROR, "ERROR");
                    }

                    char c = string[i + 1];
                    switch (c) {
                    case '"':
                        break;

                    case '\\':
                        break;

                    case 'n':
                        break;

                    case 't':
                        break;

                    default:
                        tokens_.back().type = TokenType::ERROR;
                    }
                }
            }

            continue;
            break;
        }

        default: {
            if (input[i] == '0') {
                tokens_.emplace_back(TokenType::ERROR, "ERROR");
                return;
            }

            auto is_valid = [] (char c) {
                    return std::isdigit(c) || (c == '-') || (c == '+') || (c == '.') || (c == 'E') || (c == 'e');
                };

            if (!is_valid(input[i])) {
                tokens_.emplace_back(TokenType::ERROR, "ERROR");
                return;
            }

            int j = i;
            while (is_valid(input[j])) {
                ++j;
            }

            // std::cout << "computed number: " <<  input.substr(i, j - i) << std::endl;
            tokens_.emplace_back(TokenType::NUMBER, input.substr(i, j - i));
            i = j;
            continue;
            break;
        }
        }

        ++i;
    }

    tokens_.emplace_back(TokenType::END, "");
}
