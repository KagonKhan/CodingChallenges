#include "json.hpp"

#include <filesystem>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>


#include "spdlog/spdlog.h"

#include "lexer.hpp"
#include "parser.hpp"


class JSON
{
    Lexer  lexer_;
    Parser parser_ {lexer_};

public:
    bool parse(std::string string)
    {
        std::cout << string << std::endl << std::endl;
        lexer_.read(string);
        return parser_.parse();
    }
};

#include <filesystem>
int main()
{
//     JSON json;

//     json.parse(
//         R"({
//   "key": "value",
//   "key-n": 101,
//   "key-b": false,
//   "key-o": {
//     "inner key": "inner value",
//     "simple value": true,
//     "key-l": ["list value", true, 5],
//     "key-o": {
//         "inner key": "inner value",
//         "simple value": true,
//         "key-l": ["list value", true, 5]
//     }
//   },
//   "key-l": ["list value", true, 5]
// })"
//     );

    int good {0}, bad {0};

    for (auto entry :
        std::filesystem::directory_iterator {"/home/sszynk/projects/CodingChallenges/src/json-parser/test"}) {
        std::cout << "entry: " << entry.path() << std::endl;

        std::string name = entry.path().filename().string();
        name = name.substr(0, 4);


        std::ifstream     file(entry.path());
        std::stringstream sstream;
        sstream << file.rdbuf();


        if (name == "fail") {
            JSON json;

            auto result = json.parse(sstream.str());

            if (result == true) {
                std::cout << "Expected to fail!\n";
                bad++;
            }
            else {
                good++;
                std::cout << "Success! \n";
            }
        }
        else if (name == "pass") {
            JSON json;

            auto result = json.parse(sstream.str());

            if (result == false) {
                std::cout << "Expected to Succeed!\n";
                bad++;
            }
            else {
                good++;
                std::cout << "Success! \n";
            }
        }
        else {
            std::cout << "err parsing input file\n";
        }

        std::cout << "\n--------------------------------------------------------\n";
    }

    std::cout << "Fin!\n";

    std::cout << good << "/" << (good + bad) << " correct [" << 100.0 * good / (good + bad) << "%]\n";
}
