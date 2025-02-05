#include <filesystem>
#include <fstream>
#include <iostream>

int manpage() {
    std::cout << "Some bullshit explanation\n";
    return 0;
}

int parseWC(std::ifstream& file) {
    std::string word;
    word.reserve(100);

    int word_count{0};
    while (file >> word) {
        ++word_count;
    }
    std::cout << word_count;
    return word_count;
}

int parseLC(std::ifstream& file) {
    std::string line;
    line.reserve(5000);

    int line_count{0};
    while (std::getline(file, line)) {
        ++line_count;
    }
    std::cout << line_count;
    return line_count;
}


int main(int argc, char* argv[]) {
    if (argc != 2) {
        return manpage();
    }


    std::ifstream file{argv[1]};

    if (!file) {
        // error
        return -1;
    }
    std::cout << std::filesystem::file_size(argv[1]);
    return std::filesystem::file_size(argv[1]);
}