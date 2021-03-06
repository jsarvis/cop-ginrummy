#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <cstdlib> 
#include <ctime> 


#include "Card.h"
#include "Melds.h"

using namespace std;

bool reverse(Card const& a, Card const& b);
vector<Card> shuffle(vector<Card> a);
int main()
{
	srand((unsigned)time(0));
	string symbols[4] = {"H", "D", "C", "S"};
	vector<Card> deck;
	vector<Card> hand;
	vector<Card> hand2;
	vector<Card> toDiscard;
	
	Melds testMeld;
	
	
	for(int k = 1; k < 53; k++) {
		deck.push_back(Card(k));
	}
	
	deck = shuffle(deck);
	
	for(int k = 0; k < 11; k++) {
		hand.push_back(deck[k]);	
	}
	for(int k = 11; k < 22; k++) {
		hand2.push_back(deck[k]);
	}
	
	sort(hand.begin(), hand.end());
	cout << "Hand: " << endl;
	for(int k = 0; k < hand.size(); k++) {
		cout << "   C" << k << ": " << hand[k].toString() << endl;
	}
	
	toDiscard = testMeld.updateMelds(hand);
	
	sort(toDiscard.begin(), toDiscard.end());
	cout << "Discards: " << endl;
	for(int k = 0; k < toDiscard.size(); k++) {
		cout << "   C" << k << ": " << toDiscard[k].toString() << endl;
	}
	
	sort(hand2.begin(), hand2.end());
	cout << "Hand2: " << endl;
	for(int k = 0; k < hand2.size(); k++) {
		cout << "   C" << k << ": " << hand2[k].toString() << endl;
	}
	
	toDiscard = testMeld.layOff(hand2);
	
	sort(toDiscard.begin(), toDiscard.end());
	cout << "Discards: " << endl;
	for(int k = 0; k < toDiscard.size(); k++) {
		cout << "   C" << k << ": " << toDiscard[k].toString() << endl;
	}
	
	return 0;
}

// Modify this function and then use it to sort however you want. 
// to sort w/ it use sort(deck.begin(), deck.end(), reverse);
bool reverse(Card const& a, Card const& b) { 
	
	return (a.getFaceValue() < b.getFaceValue());
}

vector<Card> shuffle(vector<Card> a){
	srand(time(0));
	for(int k = (a.size() - 1); k > 0; k--) {
		int swapIndex = (rand() % k);
		Card temp = a[k];
		a[k] = a[swapIndex];
		a[swapIndex] = temp;
	}
	return a;
}
