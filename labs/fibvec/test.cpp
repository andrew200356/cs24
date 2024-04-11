#include "FibVec.h"
#include <iostream>

// Use this file to test your FibVec class!
// This file won't be graded - do whatever you want.

int main()
{
    FibVec fibvec;

    fibvec.insert(1, 0);

    // print: [1/1]: 1
    std::cout << fibvec.lookup(0) << std::endl;
    return 0;
}
