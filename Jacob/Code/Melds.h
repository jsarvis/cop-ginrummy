#ifndef MELDS_H
#define MELDS_H

#include <string>
#include <vector>

#include "SimMgmt.h"
#include "Card.h"

using namespace std;
using namespace SimMgmt;

namespace SimModels {

class Melds {
private:

	vector<vector<Card> > v_vC_individualMelds;

	vector<vector<Card> > recGetMelds(vector<vector<Card> > a, vector<Card> b);

	bool isMeld(vector<Card> a);

public:
	Melds();

	vector<Card> updateMelds(vector<Card> a);

	vector<Card> layOff(vector<Card> a);

};

}
#endif
