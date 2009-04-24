#ifndef _CARD
#define _CARD

#include<string>

#include "SimMgmt.h"


using namespace std;
using namespace SimMgmt;

namespace SimModels {

	class Card {
	public:
		//Constructors
		Card();
		Card(int a);
		Card(int a, int b);

		int getFaceValue() const;
		int getPointValue() const;
		int getSuitIndex() const;
		string toString() const;

		//Overloaded operators - used for sort()
		friend bool operator< (Card const& a, Card const& b);

	protected:
		int setPointValue();

	private:
		int faceValue;
		int pointValue;
		int suitIndex; //0 = Hearts, 1 = Diamonds, 2 = Clubs, 3 = Spades

	};//Card

}
#endif
