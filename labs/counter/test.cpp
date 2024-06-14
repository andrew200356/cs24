#include <iostream>
#include <string>

#include "Counter.h"
#include "Index.h"
#include "List.h"
using namespace std;
int main() {
    Counter counter = Counter();
    counter.set("red", 1);
    counter.set("orange", 2);
    counter.set("yellow", 3);
    counter.set("green", 4);
    counter.set("blue", 5);
    counter.set("purple", 6);
    cout << counter.count() << endl;
    counter.set("red", 7);
    cout << counter.get("red") << endl;
    counter.inc("orange", 4);
    cout << counter.get("orange") << endl;
    counter.dec("yellow");
    cout << counter.get("yellow") << endl;
    counter.del("blue");
    cout << counter.count();
    return 0;
}
