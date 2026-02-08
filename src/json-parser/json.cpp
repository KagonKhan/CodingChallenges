#include "json.hpp"

#include <string>
#include <iostream>


#include "spdlog/spdlog.h"


enum class TokenType {
    BRACE_OPEN, BRACE_CLOSE,
    BRACKET_OPEN, BRACKET_CLOSE,
    COLON, COMMA,

    TRUE, FALSE,
    STRING,
    NUMBER,
    NULL_VALUE,

    END, ERROR
};

struct Token {
    TokenType type;
    std::string value;
};


class JSON {
public:
void parse(std::string string) {
    std::vector<Token> tokens;

    int column = 1;
    int row = 1;

    std::cout << string << std::endl << std::endl;

    for(int i = 0; i < string.length(); ) {
        char c = string[i];



        switch(c) {
            case ' ' : break;
            case '\n': break;
            case '{': tokens.emplace_back(TokenType::BRACE_OPEN, "{");    break;
            case '}': tokens.emplace_back(TokenType::BRACE_CLOSE, "}");   break;
            case '[': tokens.emplace_back(TokenType::BRACKET_OPEN, "[");  break;
            case ']': tokens.emplace_back(TokenType::BRACKET_CLOSE, "]"); break;
            case ':': tokens.emplace_back(TokenType::COLON, ":");         break;
            case ',': tokens.emplace_back(TokenType::COMMA, ",");         break;\
            case 'n': {
                std::cout << "null: " << string.substr(i, 4) << std::endl;
                if(string.substr(i, 4) == std::string("null")) {
                    tokens.emplace_back(TokenType::NULL_VALUE, "null");
                } else {
                    std::cout << "Error parsing null";
                }
                i+=4; continue;
                break;
            }
            case 't': {
                std::cout << "computed boolen: " << string.substr(i, 4) << std::endl;
                if(string.substr(i, 4) == std::string("true")) {
                    tokens.emplace_back(TokenType::TRUE, "true");
                } else {
                    std::cout << "Error parsing bool";
                }
                i+=4; continue;
                break;
            }
            case 'f': {
                std::cout << "computed boolen: " << string.substr(i, 5) << std::endl;
                if(string.substr(i, 5) == std::string("false")) {
                    tokens.emplace_back(TokenType::FALSE, "false");
                } else {
                    std::cout << "Error parsing bool";
                }
                i+=5; continue;
                break;
            }
            case '"': {
                ++i; // Skip '"'
                int j = i;
                while(string[j] != '"' && string[j] != '\0') { ++j; }
                std::cout << "computed string: " <<  string.substr(i, j - i) << std::endl;
                tokens.emplace_back(TokenType::STRING, string.substr(i, j - i));
                i = j + 1; // Skip '"'
                continue;
                break;
            }
            default: 
            {
                int j = i;
                while(std::isdigit(string[j]) || string[j] == '.') { ++j; }
                std::cout << "computed number: " <<  string.substr(i, j - i) << std::endl;
                tokens.emplace_back(TokenType::NUMBER, string.substr(i, j - i));
                i = j;
                continue;
                break;
            }

        }
        ++i;
    }

    tokens.emplace_back(TokenType::END, "");


    std::cout << "\n\n\n";

    for(auto token : tokens) {
        std::cout << token.value;
    }

    std::cout << std::endl;
}
};

int main() { 
    JSON json;

    json.parse(
R"(
{
  "key": "value",
  "key-n": 101,
  "key-b": false,
  "key-o": {
    "inner key": "inner value"
  },
  "key-l": ["list value"]
}

)"
    );
}