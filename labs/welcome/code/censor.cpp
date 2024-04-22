// In this file, write a program that takes one integer as a command line argument. Your program should then read one line of text, then print that line back to the console, but all words that are the length given as command line argument should be removed.

#include <iostream>
#include <numeric>
#include <sstream>
#include <string>
#include <vector>

int main(int argc, char *argv[]) {
    if (argc != 2) {
        std::cout << "USAGE: censor [length]" << std::endl;
        return 1;
    }

    size_t wordLength;
    std::istringstream iss(argv[1]);
    if (!(iss >> wordLength)) {
        std::cout << "Invalid word length" << std::endl;
        return 1;
    }

    std::string line;
    std::getline(std::cin, line);

    std::istringstream lineStream(line);
    std::string word;
    std::vector<std::string> words;
    while (lineStream >> word) {
        if (word.length() != wordLength) {
            words.push_back(word);
        }
    }

    // Join the words with spaces and print the result
    std::cout << std::accumulate(std::next(words.begin()), words.end(), words[0],
                                 [](std::string a, std::string b) {
                                     return a + ' ' + b;
                                 })
              << std::endl;

    return 0;
}
