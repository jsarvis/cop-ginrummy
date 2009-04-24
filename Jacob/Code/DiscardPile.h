#ifndef DISCARDPILE_H
#define DISCARDPILE_H

#include <string>

#include "SimMgmt.h"
#include "Card.h"
#include "CardPile.h"

using namespace std;
using namespace SimMgmt;

namespace SimModels {

class DiscardPile: public CardPile {
public:
	Card * getTopCard();

	DiscardPile();

    void Add(const Card & inserted);

	bool isEmpty();

};
}
#endif

