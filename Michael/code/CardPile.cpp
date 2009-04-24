#include "CardPile.h"

namespace SimModels {
// CardPile methods

// constructor
CardPile::CardPile()
{
	return;
}

// Add a card to the pile
void CardPile::Add(const Card & inserted)
{
	vC_Pile.push_back(inserted);
}

// draw a card from the pile
Card * CardPile::Draw()
{
	Card* temp;
	temp = (Card *)&(vC_Pile.back());
	vC_Pile.pop_back();
	return temp;
}

}
