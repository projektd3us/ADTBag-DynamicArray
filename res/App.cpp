#include "Bag.h"
#include "ShortTest.h"
#include "ExtendedTest.h"
#include <iostream>

using namespace std;

int main() {
	testAll();
	testAllExtended();

	cout << "All test over" << endl;
}