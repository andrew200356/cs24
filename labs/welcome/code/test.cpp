// C++ program to print words in a sentence
// Using Temporary String

#include <iostream>
#include <string>
#include <vector>

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        std::cout << "USAGE: censor [length]" << std::endl;
        return 1;
    }
    std::vector<std::string> words;
    std::string sentence;
    std::getline(std::cin, sentence);

    // Create a temporary string to hold each word
    std::string tempWord;

    // Iterate over each character in the sentence
    for (char c : sentence)
    {
        // Check if the character is a whitespace character
        if (isspace(c))
        {
            // If the temporary string is not empty, add it to the list of words
            if (!tempWord.empty())
            {
                words.push_back(tempWord);
                tempWord.clear();
            }
        }
        else
        {
            // If the character is not a whitespace character, add it to the temporary string
            tempWord.push_back(c);
        }
    }

    // Add the last word to the list of words (if there is one)
    if (!tempWord.empty())
    {
        words.push_back(tempWord);
    }

    // Print the list of words
    for (std::string word : words)
    {
        std::cout << word << std::endl;
    }

    return 0;
}

// This code is contributed by Susobhan Akhuli
