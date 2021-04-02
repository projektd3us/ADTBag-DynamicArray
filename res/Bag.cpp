#include "Bag.h"
#include "BagIterator.h"
#include <exception>
#include <iostream>
using namespace std;


int Bag::searchPos(TElem e) const {
	for (int i = 0; i < lengthU; i++) {
		if (U[i] == e) {
			return i; // found
		}
	}
	return -1; // case not found
} // Best case: Theta(1), Worst Case: Theta(n) = Average Case, General Case: O(n)


Bag::Bag() {
	capacityU = 2;
	capacityP = 2;
	lengthU = 0;
	lengthP = 0;
	U = (TElem*)malloc(capacityU * sizeof(TElem)); // realloc is ok
	P = (TElem*)malloc(capacityP * sizeof(TElem)); // samesies
}


void Bag::add(TElem elem) {
	//capacity is not enough
	if (capacityP == lengthP) { // P is always increased
		if (capacityP == 0) {
			capacityP = 1;
		}
		else {
			capacityP *= 2;
		}
		P = (TElem*)realloc(P, capacityP * sizeof(TElem)); // use of realloc is ok
	}

	int pos = searchPos(elem);
	if (pos == -1) { // not found
		// check for U full
		if (capacityU == lengthU) { // U is inc if not found
			if (capacityU == 0) {
				capacityU = 1;
			}
			else {
				capacityU *= 2;
			}
			U = (TElem*)realloc(U, capacityU * sizeof(TElem)); // use of realloc is ok
		}

		U[lengthU] = elem; // add to end of U
		P[lengthP] = lengthU; // add last pos of U in P
		lengthU++; // increase el count
		lengthP++; // increase position count
	}
	else { // found
		P[lengthP] = pos;
		lengthP++;
	}
} // All Cases: Theta(1) - added to complexity of used function searchPos


bool Bag::remove(TElem elem) {
	int pos = searchPos(elem);
	if (pos == -1) { // not found
		return false;
	}
	for (int i = lengthP - 1; i >= 0; i--) { // find last occ
		if (P[i] == pos) { // found in P - not for good
			for (int j = i; j < lengthP - 1; j++) {
				P[j] = P[j + 1]; // shift left
			}
			lengthP--;
			if (lengthP == capacityP / 2) { // P is dec - always called
				capacityP /= 2;
				P = (TElem*)realloc(P, capacityP * sizeof(TElem)); // use of realloc is ok
			}

			if (nrOccurrences(elem) == 0) { // case removed for good

				for (int j = 0; j < lengthP; j++) { // iterate for fixing P
					if (P[j] > pos) {
						P[j]--; //  decrease Ps bigger than pos
					}
				}

				for (int j = pos; j < lengthU - 1; j++) {
					U[j] = U[j + 1]; // shift left
				}
				lengthU--;

				if (lengthU == capacityU / 2) { // U is dec
					capacityU /= 2;
					U = (TElem*)realloc(U, capacityU * sizeof(TElem)); // use of realloc is ok
				}
			}
			return true;
		}
	}
	return false;
} // Best case: Theta(1), Worst Case: Theta(n*n) = Average Case, General Case: O(n*n)


bool Bag::search(TElem elem) const {
	for (int i = 0; i < lengthU; i++) {
		if (U[i] == elem) {
			return true; // found
		}
	}
	return false; // case not found
} // Best case: Theta(1), Worst Case: Theta(n) = Average Case, General Case: O(n)

int Bag::nrOccurrences(TElem elem) const {
	int count = 0;
	int pos = searchPos(elem); //  get pos of elem
	if (pos == -1) { // if not found
		return 0;
	}
	for (int i = 0; i < lengthP; i++) { // iterate pos to find occ
		if (pos == P[i]) {
			count++;
		}
	}
	return count;
} // Best case: Theta(1), Worst Case: Theta(n) = Average Case, General Case: O(n)


int Bag::size() const {
	return lengthP; // length keeps len of P
} // All Cases: Theta(1)


bool Bag::isEmpty() const {
	return lengthU == 0 ? true : false;
} // All Cases: Theta(1)

BagIterator Bag::iterator() const {
	return BagIterator(*this);
}


Bag::~Bag() {
	free(U);
	free(P);
} // All Cases: Theta(1)

