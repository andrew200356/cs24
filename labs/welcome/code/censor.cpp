// In this file, write a program that takes one integer as a command line argument. Your program should then read one line of text, then print that line back to the console, but all words that are the length given as command line argument should be removed.

#include <iostream>
#include <string>
#include <sstream>

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        std::cout << "USAGE: censor [length]" << std::endl;
        return 1;
    }

    size_t wordLength;
    std::istringstream iss(argv[1]);
    if (!(iss >> wordLength))
    {
        std::cout << "Invalid word length" << std::endl;
        return 1;
    }

    std::string line;
    std::getline(std::cin, line);

    std::istringstream lineStream(line);
    std::string word;
    while (lineStream >> word)
    {
        if (word.length() != wordLength)
        {
            std::cout << word << " ";
        }
    }

    std::cout << std::endl;

    return 0;
}
