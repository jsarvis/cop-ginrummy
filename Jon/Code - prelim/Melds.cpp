#include "Melds.h"


Melds::Melds() {
	
}

bool Melds::isMeld(vector<Card> a) {
	bool trip = true;
	bool straight = true;
	
	sort(a.begin(), a.end());
	
	int curSuit = a.front().getSuitIndex();
	int curFaceValue = a.front().getFaceValue();
	
	
	for(int i = 1; i < a.size(); i++) {
		if(a[i].getSuitIndex() != curSuit) {
			straight = false;
		}
		if(a[i].getFaceValue() != curFaceValue+i) {
			straight = false;
		}
		if(a[i].getFaceValue() != curFaceValue) {
			trip = false;
		}
	}
	
	return (trip || straight);
}

vector< vector<Card> > Melds::recGetMelds(vector<vector<Card> > a) {
	vector< vector<Card> > minDeadwood = a;
	vector< vector<Card> > testDeadwood;
	vector<Card> leftoverCards = a.back();
	vector< vector<Card> > newMeldsSoFar;
	
	int minValue = 999;
	int toCompareValue;
	
	for(int i = 0; i < a.size() - 1; i++) { //iterate through all known melds
		for(int j = 0; j < leftoverCards.size(); j++) { // iterate through leftover cards
			vector<Card> tempMeld = a[i]; // copy over the current meld 
														// being tested
			tempMeld.push_back(leftoverCards[j]); // insert current test card;
			
			if(isMeld(tempMeld)) { //if test meld + test card = real meld
				
				newMeldsSoFar = a;
				
				
				newMeldsSoFar[i].push_back(leftoverCards[j]); // insert test card into
															  // correct meld location
															  
				newMeldsSoFar.back().erase(newMeldsSoFar.back().begin()+j); // erase test card
													     // from the leftover card list
			    
				
				testDeadwood = recGetMelds(newMeldsSoFar); // recursive test w/ new melds
				
				
				//test the new deadwood with the current deadwood
				vector<Card> testLeftoverCards = testDeadwood.back(); // get the list of leftover cards
				toCompareValue = 0; // reset toCompareValue
				for(int z = 0; z < testLeftoverCards.size(); z++) {
					toCompareValue += testLeftoverCards[z].getPointValue();
				}
				if(toCompareValue < minValue) { // if test is better, copy the values
					minDeadwood = testDeadwood;
					minValue = toCompareValue;
				} else if(toCompareValue == minValue) {
					//do something about ==
				}		
				
				
			} // end if isMeld()
		} // end of for(int j)
	} // end of for(int i)
	
	if(leftoverCards.size() < 3) return minDeadwood;
	
	//sort(leftoverCards.begin(), leftoverCards.end());
	for(int i = 0; i < leftoverCards.size() - 2; i++) {
		for(int j = i+1; j < leftoverCards.size() - 1; j++) {
			for(int k = j+1; k < leftoverCards.size(); k++) {
				vector<Card> tempMeld;
				vector<Card> tempLeftover = leftoverCards;
				newMeldsSoFar = a;
				newMeldsSoFar.pop_back();
				
				
				tempMeld.push_back(leftoverCards[i]);
				tempMeld.push_back(leftoverCards[j]);
				tempMeld.push_back(leftoverCards[k]);
				
				if(isMeld(tempMeld)) {
					newMeldsSoFar.push_back(tempMeld);
					
					tempLeftover.erase(tempLeftover.begin() + k);
					tempLeftover.erase(tempLeftover.begin() + j);
					tempLeftover.erase(tempLeftover.begin() + i);
					
					newMeldsSoFar.push_back(tempLeftover);
				
					newMeldsSoFar = recGetMelds(newMeldsSoFar);
					tempLeftover = newMeldsSoFar.back();
					toCompareValue = 0;
					for(int z = 0; z < tempLeftover.size(); z++) {
						toCompareValue += tempLeftover[z].getPointValue();
					}
					if(toCompareValue < minValue) { // if test is better, copy the values
						minDeadwood = newMeldsSoFar;
						minValue = toCompareValue;
					} else if(toCompareValue == minValue) {
						//do something about ==
					}
				}
					
		
			} // end of for(int k)
		} // end of for(int j)
	}// end of for(int i)
	
	
	return minDeadwood;
}// end of Melds::recGetMelds()

vector<Card> Melds::updateMelds(vector<Card> a){
	vector<vector<Card> > bestMelds;
	bestMelds.push_back(a);
	
	bestMelds = recGetMelds(bestMelds);
	
	v_vC_individualMelds = bestMelds;
	v_vC_individualMelds.pop_back();
	
	return bestMelds.back();
}

vector<Card> Melds::layOff(vector<Card> a){
	vector<vector<Card> > bestMelds;
	
	bestMelds = v_vC_individualMelds;
	bestMelds.push_back(a);
	
	bestMelds = recGetMelds(bestMelds);

	return bestMelds.back();
}

