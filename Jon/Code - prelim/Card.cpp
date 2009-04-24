//Test Modification
#include "Card.h"

namespace SimModels {
	//Card methods

	Card::Card() {
	
	}

	Card::Card(int a) {
		faceValue = ((a-1)%13) + 1;
		suitIndex = ((a-1)/13);
		pointValue = setPointValue();
	}

	Card::Card(int a, int b) {
		faceValue = a;
		suitIndex = b;
		pointValue = setPointValue();
	}

	int Card::getFaceValue() const {
		return faceValue;
	}

	int Card::getPointValue() const {
		return pointValue;
	}

	int Card::getSuitIndex() const {
		return suitIndex;
	}

	int Card::setPointValue() {
		if(faceValue > 10) return 10;
		else return faceValue;
	}

	string Card::toString() const {
		string retValue;
		string symbols[4] = {"H", "D", "C", "S"};
		string values[13] = {"A", "2", "3", "4", "5", "6", "7", "8", "9", "10", "J", "Q", "K"};
		retValue = symbols[suitIndex] + " " + values[faceValue-1];
	
		return retValue;
	}

	//Overloaded Operations
	bool operator< (Card const& a, Card const& b) {
		int aTotal = (a.getFaceValue() + (a.getSuitIndex() * 13));
		int bTotal = (b.getFaceValue() + (b.getSuitIndex() * 13));

		return (aTotal < bTotal);
	}

	//End of Overloaded Operations
}
