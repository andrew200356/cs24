#include <fstream>
#include <iomanip>
#include <iostream>
#include <string>

#include "Counter.h"

// This is the main function for the Character Count test cases.
// It runs through a list of files, reads whitespace-separated words,
// normalizes them by upcasing and stripping punctuation, and counts them.
// It prints per-file results, and the cumulative result for all files.
// You can modify this, but Gradescope will use the original.

std::string sanitize(const std::string& word) {
    std::string result;
    std::cout << "Sanitizing word: " << word << '\n';  // Debug line
    for (char c : word) {
        // std::cout << "Sanitizing character: " << c << '\n';  // Debug line
        if (isalpha(c)) {
            result += toupper(c);
        }
    }

    return result;
}

void print_header() {
    std::cout << "  Tokens   Words  Unique  Filename\n";
}

void print_results(const char* filename, const Counter& counter) {
    int tokens = counter.get("[tokens]");
    int words = counter.total() - tokens;
    int unique = counter.count() - 1;

    std::cout << std::setw(8) << tokens;
    std::cout << std::setw(8) << words;
    std::cout << std::setw(8) << unique;
    std::cout << "  " << filename << std::endl;
}

int main(int argc, char** argv) {
    if (argc < 2) {
        std::cerr << "USAGE: " << argv[0] << "[filename] [...]\n";
        return 1;
    }

    Counter totals;

    print_header();
    for (int i = 1; i < argc; ++i) {
        std::cout << "Processing file: " << argv[i] << '\n';  // Debug line

        std::ifstream stream(argv[i]);
        if (stream.fail()) {
            std::cerr << "ERROR: Could not open file: " << argv[i] << '\n';
            continue;
        }

        Counter counter;
        std::string token;

        while (stream >> token) {
            std::cout << "Processing token: " << token << '\n';  // Debug line
            counter.inc("[tokens]");

            std::string word = sanitize(token);
            if (word.length() == 0) {
                continue;
            }
            std::cout << "before get: " << word << '\n';  // Debug line

            int count = counter.get(word);
            std::cout << "Count of " << word << " is " << count << '\n';  // Debug line
            counter.set(word, count + 1);
        }

        print_results(argv[i], counter);
        for (auto itr = counter.begin(); itr != counter.end(); ++itr) {
            totals.inc(itr.key(), itr.value());
        }
    }

    print_results("TOTAL", totals);
    return 0;
}
