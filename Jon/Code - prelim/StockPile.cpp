#include "StockPile.h"


namespace SimModels {
	//Stockpile Methods

	//Constructor
	StockPile::StockPile() :CardPile() {
		srand(time(0));
	}

	/*
	StockPile::~StockPile() :~CardPile() {

	}
	*/
	bool StockPile::hasTwo() {
		return (vC_Pile.size() > 1 );
	}

	vector<Card> StockPile::Shuffle(){
		
		for(int k = (vC_Pile.size() - 1); k > 0; k--) {
			int swapIndex = (rand() % k);
			Card temp = vC_Pile[k];
			vC_Pile[k] =vC_Pile a[swapIndex];
			vC_Pile[swapIndex] = temp;
		}
	}
}
