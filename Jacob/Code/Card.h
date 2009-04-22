#ifndef CARD_H
#define CARD_H

#include <string>

#include "SimMgmt.h"

using namespace std;
using namespace SimMgmt;

namespace SimModels {

class Card {
private:
	int i_faceValue;

	int i_suitIndex;

	int i_pointValue;

	string as_suitIndexToString;

public:

	Card();
	Card(int a);
	Card(int a, b);
	Card(int a, string b);

	string toString();

	int getFaceValue();

	int getPointValue();

	int getSuitIndex();

	string getSuitString();

	bool operator<(Card const& a, Card const& b);

	virtual void Insert(ostream& fout);

protected:
	virtual void Put(ostream& fout);

};
}
#endif
