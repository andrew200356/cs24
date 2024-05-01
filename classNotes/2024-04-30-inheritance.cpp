#include <iostream>
#include <string>

struct Animal {
    virtual void speak() = 0;
};

struct Cat : public Animal {
    void speak() {
        std::cout << "Meow!\n";
    }
};

struct Dog : public Animal {
    void speak() {
        std::cout << "Woof!\n";
    }
};

struct Worm : public Animal {
    // Do worms even speak?
    // Still an abstract class!
};

struct Person {
    std::string name;
    int age;

    Person() {
        std::cout << "Person()\n";
    }

    Person(const std::string& name, int age) {
        this->name = name;
        this->age = age;
    }

    virtual void print() const {
        std::cout << this->name << " is a "
                  << this->age
                  << "-year old Person.\n";
    }
};

struct Student : public Person {
    std::string school;
    float gpa;

    Student() {
        std::cout << "Student()\n";
    }

    Student(
        const std::string& name,
        int age,
        const std::string& school,
        float gpa) : Person(name, age), school(school), gpa(gpa) {
        // Everything is initialized before we get here!
        // this->school = school;
        // this->gpa    = gpa;
    }

    void print() const {
        Person::print();
        std::cout << this->name << " is a " << this->age << "-year old Student.\n";
    }

    void hey() const {
        std::cout << "Hey!\n";
    }
};

struct GradStudent : public Student {
    std::string lab;

    GradStudent() {
        std::cout << "GradStudent()\n";
    }

    void print() const {
        std::cout << this->name << " is a"
                  << " grad student at "
                  << this->school << '\n';
    }
};

void printInfo(const Person* p) {
    std::cout << p->name << " is "
              << p->age << " years old.\n";
}

void printInfo2(const Person* p) {
    p->print();
}

void printInfo3(const Student* s) {
    // s->hey();
    // std::cout << s->school << '\n';
    s->print();
}

void saySomething(Animal& animal) {
    animal.speak();
}

int main() {
    // Animal animal;
    // Cat cat;
    // Dog dog;

    // saySomething(cat);
    // saySomething(dog);
    // return 0;

    Person alice;
    alice.name = "Alice";
    alice.age = 12;

    Person twin("Alice's Evil Twin", 12);

    Student bob;
    bob.name = "Bob";
    bob.age = 42;
    bob.school = "UCLA";
    bob.gpa = 3.76;

    GradStudent carol;
    carol.name = "Carol";
    carol.age = 29;
    carol.school = "UCSB";
    carol.gpa = 4.00;
    carol.lab = "4Eyes";

    // printInfo(&alice);
    // printInfo(&bob);

    // alice.print();
    // bob.print();

    // printInfo2(&alice);
    // printInfo2(&bob);
    // printInfo2(&carol);

    // printInfo3(&alice);
    printInfo3(&bob);
    printInfo3(&carol);
}
