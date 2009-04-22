#ifndef STOCKPILE_H
#define STOCKPILE_H

#include <string>

#include "SimMgmt.h"
#include "Card.h"
#include "CardPile.h"

using namespace std;
using namespace SimMgmt;

namespace SimModels {

class StockPile: public CardPile {
public:
	StockPile();Shuffle();

	bool hasTwo();

};
}
#endif

