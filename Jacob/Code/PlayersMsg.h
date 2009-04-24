#ifndef PLAYERSMSG_H
#define PLAYERSMSG_H

#include <string>
#include <vector>

#include "SimMgmt.h"

using namespace std;
using namespace SimMgmt;

namespace SimModels {

class PlayersMsg: public Message {
protected:
	virtual void Put(ostream& fout);

public:
	AGENTPTR * apP_Contents;

	PlayersMsg(AGENTPTR * inputplayers);

	virtual void Insert(ostream& fout);

};

}
#endif

