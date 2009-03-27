#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <cstdlib> 
#include <ctime> 


#include "Card.h"

using namespace std;

bool reverse(Card const& a, Card const& b);
bool shuffle(Card const& a, Card const& b);

int main()
{
	int i;
	string symbols[4] = {"H", "D", "C", "S"};
	vector<Card> deck;
	vector<Card>::iterator it;
	Card a(1,0);
	Card d(13, 3);
	srand((unsigned)time(0));


	for(int k = 13; k >= 1; k--) {
		for(int j = 0; j <= 3; j++) {
			Card temp(k, j);
			deck.push_back(temp);
		}
	}
	
	sort(deck.begin(), deck.end(), shuffle);

	//iterator through deck and print cards.
	i = 0;
	for(it = deck.begin(); it != deck.end(); ++it) {
		cout << it->getFaceValue() << "\t" 
			<< symbols[it->getSuitIndex()] << endl;
	}


	//Card 1 - Card 52 = -51 dif
	cout << endl << "1 H - K S = " << a - d << endl;

	cin >> i;
	return 0;
}

// Modify this function and then use it to sort however you want. 
// to sort w/ it use sort(deck.begin(), deck.end(), reverse);
bool reverse(Card const& a, Card const& b) { 
	int aTotal = a.getFaceValue() + (a.getSuitIndex() * 13);
	int bTotal = b.getFaceValue() + (b.getSuitIndex() * 13);
	
	return (aTotal > bTotal);
}

bool shuffle(Card const& a, Card const& b) {  
	if( (rand() % 2) == 0 ) return true;
	else return false;
}
