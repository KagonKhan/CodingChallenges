#include <filesystem>
#include <fstream>
#include <functional>
#include <iostream>
#include <print>
#include <set>
#include <unordered_map>

int manpage() {
    std::print("\nwc program, but probably worse :)\n"
               "\t -c byte size of a file\n"
               "\t -l line count of a file\n"
               "\t -w word count of a file\n"
               "Usage: .\\wc.exe (flag) file\n"
               "If flag is omitted, all info about the file will be printed.\n\n");
    return 0;
}

void parseWC(std::istream& file) {
    std::string word;
    word.reserve(100);

    int word_count{0};
    while (file >> word) {
        ++word_count;
    }
    std::print("\t{}", word_count);
}

void parseLC(std::istream& file) {
    std::string line;
    line.reserve(5000);
    int line_count{0};
    while (std::getline(file, line)) {
        ++line_count;
    }

    std::print("\t{}", line_count);
}

void parseBC(std::istream& file) {
    file.seekg(0, std::ios::end);
    std::print("\t{}", (int)file.tellg());
}

enum class Option {
    l,
    w,
    c,
};

const std::unordered_map<std::string, Option> AvailableOptions{
    {"-l", Option::l},      {"--lines", Option::l}, {"-w", Option::w},
    {"--words", Option::w}, {"-c", Option::c},      {"-characters", Option::c},
};


int main(int argc, char* argv[]) {
    std::set<Option>         options;
    std::vector<std::string> inputs;

    {
        int i = 1;

        // Flags
        for (; i < argc; ++i) {
            std::string arg_input = argv[i];

            if (arg_input.starts_with('-')) {
                if (AvailableOptions.contains(arg_input)) {
                    options.insert(AvailableOptions.at(arg_input));
                } else {
                    manpage();
                    return -1;
                }
            } else {
                break;
            }
        }

        if (options.empty()) {
            options.insert_range(std::vector{Option::c, Option::l, Option::w});
        }

        // Inputs
        for (; i < argc; ++i) {
            std::string arg_input = argv[i];
            if (std::filesystem::is_regular_file(arg_input)) {
                inputs.push_back(arg_input);
            } else {
                manpage();
                return -1;
            }
        }
    }

    if(inputs.empty()) {
        for (auto option : options) {
            switch (option) {
            case Option::l: parseLC(std::cin); break;
            case Option::c: parseBC(std::cin); break;
            case Option::w: parseWC(std::cin); break;
            }
        }
        return 0 ; 
    }

    for (auto const& filename : inputs) {
        std::ifstream input{filename};


        for (auto option : options) {
            switch (option) {
            case Option::l: parseLC(input); break;
            case Option::c: parseBC(input); break;
            case Option::w: parseWC(input); break;
            }
        }

        std::cout << "\t" << filename << "\n";
    }

    return 0;
}