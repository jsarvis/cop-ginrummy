#include "DiscardPile.h"

// DiscardPile Methods

namespace SimModels {

	//constructor
	DiscardPile::DiscardPile()
		:CardPile()
	{

	}

	Card * DiscardPile::getTopCard()
	{
		Card* temp;
		temp = (Card *)&(vC_Pile.back());
		return temp;
	}

	bool DiscardPile::isEmpty()
	{
		return vC_Pile.empty();
	}

}
