#ifndef STOCKPILE_H
#define STOCKPILE_H

#include <string>
#include <vector>

#include "SimMgmt.h"
#include "Card.h"

using namespace std;
using namespace SimMgmt;

namespace SimModels {

	class StockPile: public CardPile {

	public:
		StockPile();
		//~StockPile();
		
		vector<Card> shuffle(vector<Card> a);
		
	protected:
	
	private:

	};

}
#endif

