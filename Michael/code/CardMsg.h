#ifndef CARDMSG_H
#define CARDMSG_H

#include <string>
#include <vector>

#include "SimMgmt.h"
#include "Card.h"

using namespace std;
using namespace SimMgmt;

namespace SimModels {

class CardMsg: public Message {
protected:
	virtual void Put();//ostream& fout);

public:
	Card * pC_Contents;
	CardMsg(int Handler, string Description, Card * inputCard);
	virtual void Insert();//ostream& fout);
};

}
#endif

