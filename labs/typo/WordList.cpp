#include "WordList.h"

#include <cctype>
#include <cmath>
#include <stdexcept>
#include <vector>

#include "Point.h"

// Function to get the index of a character in the QWERTY array
int getIndex(char c) {
    return c - 'a';  // 'a' is at index 0, 'b' at index 1, ..., 'z' at index 25
}

WordList::WordList(std::istream& stream) {
    // The constructor creates a word list from an input stream.
    // Each line of this stream is a single word. Ignore words that are not entirely lower case ASCII.
    std::string word;
    while (stream >> word) {
        // Check if the word is entirely lower case ASCII
        bool isLowercase = true;
        for (char c : word) {
            if (!std::islower(c)) {
                isLowercase = false;
                break;
            }
        }
        if (isLowercase)
            mWords.push_back(word);
    }
}

Heap WordList::correct(const std::vector<Point>& points, size_t maxcount, float cutoff) const {
    // The correct() function is where the important stuff happens.
    // It takes in a sequence of points; these are the points where the user touched the screen.
    // It then finds all the words of the correct length, scores them according to the scoring algorithm
    // below, and uses a Heap with capacity maxcount to collect the most likely words.
    // Words with scores lower than cutoff are not included in the output.

    Heap heap(maxcount);

    for (const auto& word : mWords) {
        if (word.size() != points.size()) {
            continue;
        }

        float totalScore = 0.0f;
        for (size_t i = 0; i < word.size(); ++i) {
            char c = word[i];
            int index = getIndex(c);
            Point keyPos = QWERTY[index];
            float dx = points[i].x - keyPos.x;
            float dy = points[i].y - keyPos.y;
            float distance = std::sqrt(dx * dx + dy * dy);
            float score = 1 / (10 * distance * distance + 1);
            totalScore += score;
        }

        float averageScore = totalScore / word.size();
        if (averageScore >= cutoff) {
            if (heap.count() < maxcount) {
                heap.push(word, averageScore);
            } else if (averageScore > heap.top().score) {
                heap.pushpop(word, averageScore);
            }
        }
    }

    return heap;
}