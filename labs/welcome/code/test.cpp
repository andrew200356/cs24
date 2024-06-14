#include <iostream>
#include <string>
#include <vector>

// solving problem in traditional way but using vector and string fucntions

int main(int argc, char *argv[]) {
    if (argc != 2) {
        std::cout << "USAGE: censor [length]" << std::endl;
        return 1;
    }
    std::vector<std::string> words;
    std::string sentence;
    std::getline(std::cin, sentence);

    // Create a temporary string to hold each word
    std::string tempWord;

    // Iterate over each character in the sentence
    for (char c : sentence) {
        // Check if the character is a whitespace character
        if (isspace(c)) {
            // If the temporary string is not empty, add it to the list of words
            if (!tempWord.empty()) {
                words.push_back(tempWord);
                tempWord.clear();
            }
        } else {
            // If the character is not a whitespace character, add it to the temporary string
            tempWord.push_back(c);
        }
    }

    // Add the last word to the list of words (if there is one)
    if (!tempWord.empty()) {
        words.push_back(tempWord);
    }

    // Print the list of words, add space in between except for the last word
    for (size_t i = 0; i < words.size(); i++) {
        std::cout << words[i];
        if (i < words.size() - 1) {
            std::cout << " ";
        }
    }

    return 0;
}

// thanks for the help of Susobhan Akhuli
