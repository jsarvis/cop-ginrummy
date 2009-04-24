#include "DiscardPile.h"

// DiscardPile Methods

namespace SimModels {

	//constructor
	DiscardPile::DiscardPile()
		:CardPile()
	{

	}

	DiscardPile::getTopCard()
	{
		Card* temp;
		temp = (Card *)&(vC_Pile.back());
		return temp;
	}

	DiscardPile::isEmpty()
	{
		return vC_Pile.empty();
	}

}
