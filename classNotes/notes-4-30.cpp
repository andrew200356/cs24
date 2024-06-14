// interitance demo
// Date: 04/30/2024

#include <iostream>
#include <string>

class Person {
   public:
    Person(std::string name, int age) : name(name), age(age){};

    // if parent class has a virtual function, child class must have a virtual function
    // if you have a virtual function, you must have a virtual destructor
    virtual void print() const {
        std::cout << name << " is a " << age << " years old person. " << std::endl;
    }

    std::string name;
    int age;
};

class Student : public Person {
   public:
    Student(std::string name, int age, std::string major) : Person(name, age), major(major){};

    // constructor with default view
    Student(std::string name, int age, std::string major) : Person(name, age) {
        this->major = major;
    }

    void print() const {
        std::cout << name << " is a " << age << " years old student majoring in " << major << ". " << std::endl;
    }

    std::string major;
    float gpa;
};

class GradStudent : public Student {
   public:
    GradStudent(std::string name, int age, std::string major, std::string research) : Student(name, age, major), research(research){};
    void print() const {
        std::cout << name << " is a " << age << " years old grad student majoring in " << major << " researching " << research << ". " << std::endl;
    }

    std::string research;
};

int main() {
    Person p("Alice", 20);
    Student s("Bob", 21, "CS");
    p.print();
    s.print();
    return 0;
}