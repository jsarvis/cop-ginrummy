#include "StockPile.h"

namespace SimModels {
	//Stockpile Methods

	//Constructor
	StockPile::StockPile() :CardPile() {
	
	}

	/*
	StockPile::~StockPile() :~CardPile() {

	}
	*/

	vector<Card> StockPile::shuffle(vector<Card> a){
		srand(time(0));
		for(int k = (a.size() - 1); k > 0; k--) {
			int swapIndex = (rand() % k);
			Card temp = a[k];
			a[k] = a[swapIndex];
			a[swapIndex] = temp;
		}
		return a;
	}
}
