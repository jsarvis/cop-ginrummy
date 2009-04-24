//Test Modification
#include "Card.h"

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

//Overloaded Operations
bool operator< (Card const& a, Card const& b) {
	int aTotal = (a.getFaceValue() + (a.getSuitIndex() * 13));
	int bTotal = (b.getFaceValue() + (b.getSuitIndex() * 13));

	return (aTotal < bTotal);
}

bool operator> (Card const& a, Card const& b) {
	int aTotal = (a.getFaceValue() + (a.getSuitIndex() * 13));
	int bTotal = (b.getFaceValue() + (b.getSuitIndex() * 13));

	return (aTotal > bTotal);
}

bool operator<= (Card const& a, Card const& b) {
	int aTotal = (a.getFaceValue() + (a.getSuitIndex() * 13));
	int bTotal = (b.getFaceValue() + (b.getSuitIndex() * 13));

	return (aTotal <= bTotal);
}

bool operator>= (Card const& a, Card const& b) {
	int aTotal = (a.getFaceValue() + (a.getSuitIndex() * 13));
	int bTotal = (b.getFaceValue() + (b.getSuitIndex() * 13));

	return (aTotal >= bTotal);
}

//Overloaded operators - used for meld comparisons

//used to find cards with the same face value for 3-of-a-kind
bool operator== (Card const& a, Card const& b) {
	int aTotal = a.getFaceValue();
	int bTotal = b.getFaceValue();

	return (aTotal == bTotal);
}

bool operator!= (Card const& a, Card const& b) {
	int aTotal = a.getFaceValue();
	int bTotal = b.getFaceValue();

	return (aTotal != bTotal);
}

//used to find difs for runs/straights
int operator- (Card const& a, Card const& b) {
	int aTotal = (a.getFaceValue() + (a.getSuitIndex() * 13));
	int bTotal = (b.getFaceValue() + (b.getSuitIndex() * 13));

	return (aTotal - bTotal);
}


//End of Overloaded Operations
