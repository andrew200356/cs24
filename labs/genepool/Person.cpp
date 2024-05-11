#include "Person.h"

// Person Member Functions

Person::Person(const std::string& name, Gender gender, Person* mother, Person* father) : mName(name), mGender(gender), mMother(mother), mFather(father) {
}

const std::string& Person::name() const {
    return mName;
}

Gender Person::gender() const {
    return mGender;
}

Person* Person::mother() {
    return mMother;
}

Person* Person::father() {
    return mFather;
}

std::set<Person*> Person::ancestors(PMod pmod) {
    std::set<Person*> result;
    if (mMother != nullptr) {
        result.insert(mMother);
        std::set<Person*> motherAncestors = mMother->ancestors(pmod);
        result.insert(motherAncestors.begin(), motherAncestors.end());
    }

    if (mFather != nullptr) {
        result.insert(mFather);
        std::set<Person*> fatherAncestors = mFather->ancestors(pmod);
        result.insert(fatherAncestors.begin(), fatherAncestors.end());
    }

    return result;
}

std::set<Person*> Person::aunts(PMod pmod, SMod smod) {
    std::set<Person*> result;
    if (mMother != nullptr) {
        std::set<Person*> motherSiblings = mMother->siblings(pmod, smod);
        result.insert(motherSiblings.begin(), motherSiblings.end());
    }

    if (mFather != nullptr) {
        std::set<Person*> fatherSiblings = mFather->siblings(pmod, smod);
        result.insert(fatherSiblings.begin(), fatherSiblings.end());
    }

    return result;
}

std::set<Person*> Person::brothers(PMod pmod, SMod smod) {
    return std::set<Person*>();
}

std::set<Person*> Person::children() {
    return std::set<Person*>();
}

std::set<Person*> Person::cousins(PMod pmod, SMod smod) {
    return std::set<Person*>();
}

std::set<Person*> Person::daughters() {
    return std::set<Person*>();
}

std::set<Person*> Person::descendants() {
    return std::set<Person*>();
}

std::set<Person*> Person::grandchildren() {
    return std::set<Person*>();
}

std::set<Person*> Person::granddaughters() {
    return std::set<Person*>();
}

std::set<Person*> Person::grandfathers(PMod pmod) {
    return std::set<Person*>();
}

std::set<Person*> Person::grandmothers(PMod pmod) {
    return std::set<Person*>();
}

std::set<Person*> Person::grandparents(PMod pmod) {
    return std::set<Person*>();
}

std::set<Person*> Person::grandsons() {
    return std::set<Person*>();
}

std::set<Person*> Person::nephews(PMod pmod, SMod smod) {
    return std::set<Person*>();
}

std::set<Person*> Person::nieces(PMod pmod, SMod smod) {
    return std::set<Person*>();
}

std::set<Person*> Person::parents(PMod pmod) {
    return std::set<Person*>();
}

std::set<Person*> Person::siblings(PMod pmod, SMod smod) {
    return std::set<Person*>();
}

std::set<Person*> Person::sisters(PMod pmod, SMod smod) {
    return std::set<Person*>();
}

std::set<Person*> Person::sons() {
    return std::set<Person*>();
}

std::set<Person*> Person::uncles(PMod pmod, SMod smod) {
    return std::set<Person*>();
}