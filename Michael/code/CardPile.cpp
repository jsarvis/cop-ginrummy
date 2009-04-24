#include "CardPile.h"

// CardPile methods

// constructor
CardPile::CardPile()
{
	return;
}

// Add a card to the pile
void CardPile::Add(const card & inserted)
{
	vC_pile.push_back(Card);
}

// draw a card from the pile
Card * CardPile::Draw()
{
	Card* temp;
	temp = vC_Pile.back();
	vC_Pile.pop_back();
	return temp;
}
