#include <fstream>
#include <iostream>
#include <sstream>

// Enums

enum class Gender : unsigned char {
    MALE,    // 0
    FEMALE,  // 1
    OTHER    // 2
};

struct Person {
    Gender gender;
};

int main() {
    Person person;

    person.gender = Gender::MALE;    // Assigning the gender as MALE
    person.gender = Gender::FEMALE;  // Assigning the gender as FEMALE

    if (person.gender == Gender::MALE) {
        // Code block for male gender
    } else if (person.gender == Gender::FEMALE) {
        // Code block for female gender
    } else {
        // Code block for other genders
    }

    // Default arguments

    struct Vector {
        Vector(size_t capacity = 8);  // Constructor with default capacity of 8
        // only works in .h
    };

    Vector v1();   // Creating a Vector object with default capacity of 8
    Vector v2(2);  // Creating a Vector object with capacity of 2

    // Implementing Vector constructor

    // std::istream &

    // The istream is an abstract base type
    std::istream& input_stream = std::cin;        // Standard input stream
    std::ifstream file_stream("file.txt");        // File input stream
    std::istringstream string_stream("example");  // String input stream

    // Virtual Destructors
    // when you have a subclass with dif destructor, make sure the parent destrcutor is virtual
    // so the destuctor will run throught even level bottom to top

    // V tables
    // V tables are used to implement polymorphism in C++
    // V tables are used to implement virtual functions in C++

    return 0;
}
