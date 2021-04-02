#include <exception>
#include "BagIterator.h"
#include "Bag.h"

using namespace std;


BagIterator::BagIterator(const Bag& c): bag(c)
{
	current = 0;
}

void BagIterator::first() {
	current = 0;
} // All Cases: Theta(1)


void BagIterator::next() {
	if (!valid()) {
		throw exception();
	}
	else {
		current++;
	}
} // All Cases: Theta(1)


bool BagIterator::valid() const {
	if (current < bag.lengthP) {
		return true;
	}
	return false;
} // All Cases: Theta(1)


TElem BagIterator::getCurrent() const
{
	if (!this->valid()) {
		throw exception();
	}
	return bag.U[bag.P[current]]; //returns the element from current position
} // All Cases: Theta(1)
