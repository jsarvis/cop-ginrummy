#ifndef RECIPIENTMSG_H
#define RECIPIENTMSG_H

#include <string>
#include <vector>

#include "SimMgmt.h"

using namespace std;
using namespace SimMgmt;

namespace SimModels {

class RecipientMsg: public Message {
protected:
	virtual void Put(ostream& fout);

public:
	Player * pP_Requester;
	RecipientMsg(int Handler, string Description, Player * pP_Requester);
	virtual void Insert(ostream& fout);
};

}
#endif
