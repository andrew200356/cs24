#include "WordList.h"

WordList::WordList(std::istream& stream) {
    // The constructor creates a word list from an input stream.
    // Each line of this stream is a single word. Ignore words that are not entirely lower case ASCII.
    std::string word;
    while (stream >> word) {
        // Check if the word is entirely lower case ASCII
        bool isLowercase = true;
        for (char c : word) {
            if (c < 'a' || c > 'z') {
                isLowercase = false;
                break;
            }
        }
        mWords.push_back(word);
    }
}

Heap WordList::correct(const std::vector<Point>& points, size_t maxcount, float cutoff) const {
    // The correct() function is where the important stuff happens.
    // It takes in a sequence of points; these are the points where the user touched the screen.
    // It then finds all the words of the correct length, scores them according to the scoring algorithm
    // below, and uses a Heap with capacity maxcount to collect the most likely words.
    // Words with scores lower than cutoff are not included in the output.
}