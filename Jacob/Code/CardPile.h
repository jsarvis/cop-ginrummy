#ifndef CARDPILE_H
#define CARDPILE_H

#include <string>

#include "SimMgmt.h"
#include "Card.h"

using namespace std;
using namespace SimMgmt;

namespace SimModels {

class CardPile {
public:
	CardPile();Add(const Card & inserted);

	Card Draw();

protected:
	vector<Card> vC_Pile;

};
}
#endif

