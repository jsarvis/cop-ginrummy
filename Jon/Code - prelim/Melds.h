#ifndef _MELDS
#define _MELDS

#include <algorithm>
#include <cstdlib> 
#include<vector>
#include <iostream>

#include "Card.h"

using namespace std;

class Melds {
public:
	//Constructors
	Melds();
	vector<Card> updateMelds(vector<Card> a);
	vector<Card> layOff(vector<Card> a);
protected:
	

private:
	vector< vector<Card> > v_vC_individualMelds;
	
	vector< vector<Card> > recGetMelds(vector< vector<Card> > a); 
	bool isMeld(vector<Card> a);

};//Card
#endif
