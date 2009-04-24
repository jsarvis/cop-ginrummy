#ifndef MELDS_H
#define MELDS_H

#include <algorithm>
#include <cstdlib> 
#include <vector>
#include <iostream>

#include "SimMgmt.h"
#include "Card.h"

using namespace std;
using namespace SimMgmt;

namespace SimModels {

	class Melds {
	public:
		//Constructors
		Melds();
		~Melds();
		vector<Card> updateMelds(vector<Card> a);
		vector<Card> layOff(vector<Card> a);
	protected:
	

	private:
		vector< vector<Card> > *v_vC_individualMelds;
	
		vector< vector<Card> > recGetMelds(vector< vector<Card> > a); 
		bool isMeld(vector<Card> a);

	};//Card

}
#endif
