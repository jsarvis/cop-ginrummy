#ifndef MELDSMSG_H
#define MELDSMSG_H

#include <string>
#include <vector>

#include "SimMgmt.h"
#include "Melds.h"

using namespace std;
using namespace SimMgmt;

namespace SimModels {

class MeldsMsg: public Message {
protected:
	virtual void Put(ostream& fout);

public:
	Melds * pM_Contents;
	MeldsMsg();
	virtual void Insert(ostream& fout);
};

}
#endif
