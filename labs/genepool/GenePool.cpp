#include "GenePool.h"

#include <sstream>

// GenePool Member Functions
GenePool::GenePool(std::istream& stream) {
    // The gene pool is a collection of people.
    // Read the people from the stream and store them in the gene pool.
    // The stream is a TSV-like file

    // Read the people from the stream and store them in the gene pool.
    std::string line;
    while (std::getline(stream, line)) {
        // Ignore comments and empty lines

        if (line.empty() || line[0] == '#') {
            continue;
        }

        std::istringstream iss(line);
        std::string name, genderStr, mother, father;

        // Extract the four fields from the line
        std::getline(iss, name, '\t');
        std::getline(iss, genderStr, '\t');
        std::getline(iss, mother, '\t');
        std::getline(iss, father, '\t');

        // Convert the gender string to a Gender enum value
        Gender gender;
        if (genderStr == "male") {
            gender = Gender::MALE;
        } else if (genderStr == "female") {
            gender = Gender::FEMALE;
        } else {
            throw std::runtime_error("Invalid gender: " + genderStr);
        }

        // Create a new Person object and add it to the map
        Person* person = new Person(name, gender, find(mother), find(father));
        tree[name] = person;
    }
}

GenePool::~GenePool() {
    // Clean up the gene pool.
    // Don't forget to delete all the people.
    for (auto& pair : tree) {
        delete pair.second;
    }

    // Clear the map after deleting the people
    tree.clear();
}

std::set<Person*> GenePool::everyone() const {
    // Return a set of all the people in the gene pool.
    std::set<Person*> result;
    for (auto& pair : tree) {
        result.insert(pair.second);
    }

    return result;
}

Person* GenePool::find(const std::string& name) const {
    // Find a person by name in the gene pool.
    // Return a pointer to the person if found, or nullptr if not found or name is ???.
    // Use the tree map to look up the person by name.
    if (name == "???") {
        return nullptr;
    }

    auto it = tree.find(name);
    if (it != tree.end()) {
        // Person found
        return it->second;
    }

    // Person not found in the gene pool
    return nullptr;
}