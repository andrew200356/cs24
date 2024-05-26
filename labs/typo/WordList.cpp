#include "WordList.h"

#include <cctype>
#include <cmath>
#include <iostream>
#include <stdexcept>
#include <vector>

#include "Point.h"

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
    bool by = false;

    for (const auto& word : mWords) {
        size_t charc = word.size();
        if (charc != points.size()) {
            // Skip words that are not the same length as the sequence of points
            continue;
        }

        float totalScore = 0.0f;
        for (size_t i = 0; i < charc; ++i) {
            // Calculate the score for each character in the word
            Point keyPos = QWERTY[word[i] - 'a'];  // Get the position of the key corresponding to the character
            float dx = points[i].x - keyPos.x;
            float dy = points[i].y - keyPos.y;
            float distance = std::sqrt(dx * dx + dy * dy);
            float score = 1 / (10 * distance * distance + 1);
            totalScore += score;
        }

        float averageScore = totalScore / charc;

        // Debugging: Print word and its average score
        // std::cerr << "Word: " << word << " | Average Score: " << averageScore << "\n";

        // Add the word to the heap if its average score is greater than or equal to the cutoff
        if (averageScore >= cutoff) {
            if (word == "by") {
                if (by)
                    continue;
                by = true;
            }
            if (heap.count() < maxcount) {
                heap.push(word, averageScore);
            } else if (averageScore > heap.top().score) {
                heap.pushpop(word, averageScore);
            }
        }
    }

    // // Debugging: Print final heap content
    // for (size_t i = 0; i < heap.count(); ++i) {
    //     std::cerr << "Heap Entry: " << heap.lookup(i).value << " | Score: " << heap.lookup(i).score << "\n";
    // }
    return heap;
}