#ifndef _CARD
#define _CARD

#include<string>

class Card {
public:
	//Constructors
	Card();
	Card(int a);
	Card(int a, int b);

	//setCard(int a);
	//setCard(int a, int b);
	int getFaceValue() const;
	int getPointValue() const;
	int getSuitIndex() const;

	//Overloaded operators - used for sort()
	friend bool operator< (Card const& a, Card const& b);
	friend bool operator> (Card const& a, Card const& b);
	friend bool operator<= (Card const& a, Card const& b);
	friend bool operator>= (Card const& a, Card const& b);

	//Overloaded operators - used for meld comparisons.
	friend bool operator== (Card const& a, Card const& b);
	friend bool operator!= (Card const& a, Card const& b);
	friend int operator- (Card const& a, Card const& b);

protected:
	int setPointValue();

private:
	int faceValue;
	int pointValue;
	int suitIndex; //0 = Hearts, 1 = Diamonds, 2 = Clubs, 3 = Spades

};//Card
#endif