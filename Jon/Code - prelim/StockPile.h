#ifndef STOCKPILE_H
#define STOCKPILE_H

#include <string>
#include <vector>
#include <ctime>

#include "SimMgmt.h"
#include "CardPile.h"
#include "Card.h"

using namespace std;
using namespace SimMgmt;

namespace SimModels {

	class StockPile: public CardPile {

	public:
		StockPile();

        bool hasTwo();
		//~StockPile();
		
		vector<Card> Shuffle();
		
	protected:
	
	private:

	};

}
#endif

