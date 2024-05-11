#include "Person.h"

#include <iostream>

#include "GenePool.h"

// Person Member Functions

Person::Person(const std::string& name, Gender gender, Person* mother, Person* father) : mName(name), mGender(gender), mMother(mother), mFather(father) {
    if (mMother != nullptr) {
        mMother->mChildren.insert(this);
    }
    if (mFather != nullptr) {
        mFather->mChildren.insert(this);
    }
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

std::string PModToString(PMod pmod) {
    switch (pmod) {
        case PMod::MATERNAL:
            return "MATERNAL";
        case PMod::PATERNAL:
            return "PATERNAL";
        case PMod::ANY:
            return "ANY";
        default:
            return "UNKNOWN";
    }
}

std::set<Person*> Person::ancestors(PMod pmod) {
    // Your ancestors are your parents, your parents' parents, and so on.

    // Your maternal ancestors are your mother and all of her ancestors.
    // Your paternal ancestors are your father and all of his ancestors.

    std::set<Person*> result;

    if ((pmod == PMod::MATERNAL || pmod == PMod::ANY) && mMother != nullptr) {
        result.insert(mMother);
        std::set<Person*> maternalAncestors = mMother->ancestors(PMod::ANY);
        result.insert(maternalAncestors.begin(), maternalAncestors.end());
    }

    if ((pmod == PMod::PATERNAL || pmod == PMod::ANY) && mFather != nullptr) {
        result.insert(mFather);
        std::set<Person*> paternalAncestors = mFather->ancestors(PMod::ANY);
        result.insert(paternalAncestors.begin(), paternalAncestors.end());
    }

    return result;
}

std::set<Person*> Person::aunts(PMod pmod, SMod smod) {
    // Your aunts are your parents' sisters

    // Your maternal aunts are your mother's sisters.
    // Your paternal aunts are your father's sisters.
    // Your full aunts your parents' full sisters.
    // Your half aunts your parents' half sisters.

    std::set<Person*> result;

    // first check maternal aunts
    if (pmod == PMod::MATERNAL || pmod == PMod::ANY) {
        if (mMother != nullptr) {
            // get mother's siblings
            std::set<Person*> motherSiblings = mMother->siblings(PMod::ANY, smod);
            for (Person* aunt : motherSiblings) {
                if (aunt->gender() == Gender::FEMALE) {
                    result.insert(aunt);
                }
            }
        }
    }

    // then check paternal aunts
    if (pmod == PMod::PATERNAL || pmod == PMod::ANY) {
        if (mFather != nullptr) {
            // get father's siblings
            std::set<Person*> fatherSiblings = mFather->siblings(PMod::ANY, smod);
            for (Person* aunt : fatherSiblings) {
                if (aunt->gender() == Gender::FEMALE) {
                    result.insert(aunt);
                }
            }
        }
    }

    return result;
}

std::set<Person*> Person::brothers(PMod pmod, SMod smod) {
    // Your brothers are your male siblings
    std::set<Person*> result;
    for (Person* sibling : this->siblings(pmod, smod)) {
        if (sibling->gender() == Gender::MALE) {
            result.insert(sibling);
        }
    }
    return result;
}

std::set<Person*> Person::children() {
    // Your children is those who have you as a parent
    std::set<Person*> result;
    result.insert(mChildren.begin(), mChildren.end());
    return result;
}

std::set<Person*> Person::cousins(PMod pmod, SMod smod) {
    // Your cousins are the children of your aunts and uncles.

    // Your maternal cousins are the children of your mother's siblings.
    // Your paternal cousins are the children of your father's siblings.
    // Your full cousins are the children of your parents' full siblings.
    // Your half cousins are the children of your parents' half siblings.

    std::set<Person*> result;
    // first check maternal cousins, which is the children of maternal aunts and uncles
    if (pmod == PMod::MATERNAL || pmod == PMod::ANY) {
        if (mMother != nullptr) {
            // get maternal aunts and uncles
            std::set<Person*> maternalAunts = mMother->aunts(PMod::ANY, smod);
            std::set<Person*> maternalUncles = mMother->uncles(PMod::ANY, smod);
            for (Person* maternalAunt : maternalAunts) {
                std::set<Person*> maternalAuntChildren = maternalAunt->children();
                result.insert(maternalAuntChildren.begin(), maternalAuntChildren.end());
            }
            for (Person* maternalUncle : maternalUncles) {
                std::set<Person*> maternalUncleChildren = maternalUncle->children();
                result.insert(maternalUncleChildren.begin(), maternalUncleChildren.end());
            }
        }
    }

    // then check paternal cousins, which is the children of paternal aunts and uncles
    if (pmod == PMod::PATERNAL || pmod == PMod::ANY) {
        if (mFather != nullptr) {
            // get paternal aunts and uncles
            std::set<Person*> paternalAunts = mFather->aunts(PMod::ANY, smod);
            std::set<Person*> paternalUncles = mFather->uncles(PMod::ANY, smod);
            for (Person* paternalAunt : paternalAunts) {
                std::set<Person*> paternalAuntChildren = paternalAunt->children();
                result.insert(paternalAuntChildren.begin(), paternalAuntChildren.end());
            }
            for (Person* paternalUncle : paternalUncles) {
                std::set<Person*> paternalUncleChildren = paternalUncle->children();
                result.insert(paternalUncleChildren.begin(), paternalUncleChildren.end());
            }
        }
    }

    return result;
}

std::set<Person*> Person::daughters() {
    // Your daughters are your female children
    std::set<Person*> result;
    for (Person* child : mChildren) {
        if (child->gender() == Gender::FEMALE) {
            result.insert(child);
        }
    }
    return result;
}

std::set<Person*> Person::descendants() {
    // Your descendants are your children, your children's children, and so on.
    std::set<Person*> result;
    for (Person* child : mChildren) {
        result.insert(child);
        std::set<Person*> childDescendants = child->descendants();
        result.insert(childDescendants.begin(), childDescendants.end());
    }
    return result;
}

std::set<Person*> Person::grandchildren() {
    // Your grandchildren are the children of your children
    std::set<Person*> result;
    for (Person* child : mChildren) {
        std::set<Person*> childChildren = child->children();
        result.insert(childChildren.begin(), childChildren.end());
    }
    return result;
}

std::set<Person*> Person::granddaughters() {
    // Your grand daughters are your female grandchildren
    std::set<Person*> result;
    for (Person* grandchild : this->grandchildren()) {
        if (grandchild->gender() == Gender::FEMALE) {
            result.insert(grandchild);
        }
    }
    return result;
}

std::set<Person*> Person::grandfathers(PMod pmod) {
    std::set<Person*> result;
    // Parent Modifiers determine which grandparents to return
    if (pmod == PMod::MATERNAL && mMother != nullptr && mMother->father() != nullptr) {
        result.insert(mMother->father());
    } else if (pmod == PMod::PATERNAL && mFather != nullptr && mFather->father() != nullptr) {
        result.insert(mFather->father());
    } else if (pmod == PMod::ANY) {
        if (mMother != nullptr && mMother->father() != nullptr) {
            result.insert(mMother->father());
        }
        if (mFather != nullptr && mFather->father() != nullptr) {
            result.insert(mFather->father());
        }
    }
    return result;
}

std::set<Person*> Person::grandmothers(PMod pmod) {
    std::set<Person*> result;
    // Parent Modifiers determine which grandparents to return
    if (pmod == PMod::MATERNAL && mMother != nullptr && mMother->mother() != nullptr) {
        result.insert(mMother->mother());
    } else if (pmod == PMod::PATERNAL && mFather != nullptr && mFather->mother() != nullptr) {
        result.insert(mFather->mother());
    } else if (pmod == PMod::ANY) {
        if (mMother != nullptr && mMother->mother() != nullptr) {
            result.insert(mMother->mother());
        }
        if (mFather != nullptr && mFather->mother() != nullptr) {
            result.insert(mFather->mother());
        }
    }
    return result;
}

std::set<Person*> Person::grandparents(PMod pmod) {
    std::set<Person*> result;
    auto grandfathers = this->grandfathers(pmod);
    result.insert(grandfathers.begin(), grandfathers.end());

    auto grandmothers = this->grandmothers(pmod);
    result.insert(grandmothers.begin(), grandmothers.end());
    return result;
}

std::set<Person*> Person::grandsons() {
    // Your grandsons are your male grandchildren
    std::set<Person*> result;
    for (Person* grandchild : this->grandchildren()) {
        if (grandchild->gender() == Gender::MALE) {
            result.insert(grandchild);
        }
    }
    return result;
}

std::set<Person*> Person::nephews(PMod pmod, SMod smod) {
    // Your nephews are the sons of your siblings.

    // Your maternal nephews are the sons of your maternal siblings.
    // Your paternal nephews are the sons of your paternal siblings.
    // Your full nephews are the sons of your full siblings.
    // Your half nephews are the sons of your half siblings.

    std::set<Person*> result;
    for (Person* sibling : this->siblings(pmod, smod)) {
        std::set<Person*> siblingSons = sibling->sons();
        result.insert(siblingSons.begin(), siblingSons.end());
    }
    return result;
}

std::set<Person*> Person::nieces(PMod pmod, SMod smod) {
    // Your nieces are the daughters of your siblings.

    // Your maternal nieces are the daughters of your maternal siblings.
    // Your paternal nieces are the daughters of your paternal siblings.
    // Your full nieces are the daughters of your full siblings.
    // Your half nieces are the daughters of your half siblings.

    std::set<Person*> result;
    for (Person* sibling : this->siblings(pmod, smod)) {
        std::set<Person*> siblingDaughters = sibling->daughters();
        result.insert(siblingDaughters.begin(), siblingDaughters.end());
    }
    return result;
}

std::set<Person*> Person::parents(PMod pmod) {
    // Your parents are your mother and your father.
    // Your maternal parent is your mother.
    // Your paternal parent is your father.
    std::set<Person*> result;
    if (pmod == PMod::MATERNAL) {
        if (mMother != nullptr) {
            result.insert(mMother);
        }
    } else if (pmod == PMod::PATERNAL) {
        if (mFather != nullptr) {
            result.insert(mFather);
        }
    } else if (pmod == PMod::ANY) {
        if (mMother != nullptr) {
            result.insert(mMother);
        }
        if (mFather != nullptr) {
            result.insert(mFather);
        }
    }
    return result;
}

std::set<Person*> Person::siblings(PMod pmod, SMod smod) {
    // Your siblings are people who share a parent with you, but are not you.
    // Your maternal siblings have the same mother as you.
    // Your paternal siblings have the same father as you.
    // Your full siblings have the same mother and father as you.
    // Your half siblings share only one parent with you.
    std::set<Person*> result;

    // determine which parent to return
    if (pmod == PMod::MATERNAL) {
        // Add maternal siblings
        if (mMother != nullptr) {
            for (Person* sibling : mMother->children()) {
                if (sibling != this) {
                    if (smod == SMod::FULL) {
                        if (sibling->father() == mFather) {
                            result.insert(sibling);
                        }
                    } else if (smod == SMod::HALF) {
                        if (sibling->father() != mFather) {
                            result.insert(sibling);
                        }
                    } else if (smod == SMod::ANY) {
                        result.insert(sibling);
                    }
                }
            }
        }
    } else if (pmod == PMod::PATERNAL) {
        // Add paternal siblings
        if (mFather != nullptr) {
            for (Person* sibling : mFather->children()) {
                if (sibling != this) {
                    if (smod == SMod::FULL) {
                        if (sibling->mother() == mMother) {
                            result.insert(sibling);
                        }
                    } else if (smod == SMod::HALF) {
                        if (sibling->mother() != mMother) {
                            result.insert(sibling);
                        }
                    } else if (smod == SMod::ANY) {
                        result.insert(sibling);
                    }
                }
            }
        }
    } else if (pmod == PMod::ANY) {
        // Add maternal siblings
        if (mMother != nullptr) {
            for (Person* sibling : mMother->children()) {
                if (sibling != this && result.find(sibling) == result.end()) {
                    if (smod == SMod::FULL) {
                        // if sibling does not have father
                        if (sibling->father() == nullptr) {
                        } else if (sibling->father() == mFather) {
                            result.insert(sibling);
                        }
                    } else if (smod == SMod::HALF) {
                        if (sibling->father() != mFather) {
                            result.insert(sibling);
                        }
                    } else if (smod == SMod::ANY) {
                        result.insert(sibling);
                    }
                }
            }
        }

        // Add paternal siblings
        if (mFather != nullptr) {
            for (Person* sibling : mFather->children()) {
                if (sibling != this && result.find(sibling) == result.end()) {
                    if (smod == SMod::FULL) {
                        if (sibling->mother() == nullptr) {
                        } else if (sibling->mother() == mMother) {
                            result.insert(sibling);
                        }
                    } else if (smod == SMod::HALF) {
                        if (sibling->mother() != mMother) {
                            result.insert(sibling);
                        }
                    } else if (smod == SMod::ANY) {
                        result.insert(sibling);
                    }
                }
            }
        }
    }

    return result;
}

std::set<Person*> Person::sisters(PMod pmod, SMod smod) {
    // Your sisters are your female siblings
    std::set<Person*> result;
    for (Person* sibling : this->siblings(pmod, smod)) {
        if (sibling->gender() == Gender::FEMALE) {
            result.insert(sibling);
        }
    }
    return result;
}

std::set<Person*> Person::sons() {
    // Your sons are your male children
    std::set<Person*> result;
    for (Person* child : mChildren) {
        if (child->gender() == Gender::MALE) {
            result.insert(child);
        }
    }
    return result;
}

std::set<Person*> Person::uncles(PMod pmod, SMod smod) {
    // Your uncles are your parents' brothers

    // Your maternal uncles are your mother's brothers.
    // Your paternal uncles are your father's brothers.
    // Your full uncles are your parents' full brothers.
    // Your half uncles are your parents' half brothers.

    std::set<Person*> result;

    // first check maternal uncles
    if (pmod == PMod::MATERNAL || pmod == PMod::ANY) {
        if (mMother != nullptr) {
            // get mother's siblings
            std::set<Person*> motherSiblings = mMother->siblings(PMod::ANY, smod);
            for (Person* uncle : motherSiblings) {
                if (uncle->gender() == Gender::MALE) {
                    result.insert(uncle);
                }
            }
        }
    }

    // then check paternal uncles
    if (pmod == PMod::PATERNAL || pmod == PMod::ANY) {
        if (mFather != nullptr) {
            // get father's siblings
            std::set<Person*> fatherSiblings = mFather->siblings(PMod::ANY, smod);
            for (Person* uncle : fatherSiblings) {
                if (uncle->gender() == Gender::MALE) {
                    result.insert(uncle);
                }
            }
        }
    }

    return result;
}