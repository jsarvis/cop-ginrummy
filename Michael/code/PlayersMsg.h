#ifndef PLAYERSMSG_H
#define PLAYERSMSG_H

#include <string>
#include <vector>

#include "SimMgmt.h"

using namespace std;
using namespace SimMgmt;

namespace SimModels {

class PlayersMsg : public Message {
  public:
    AGENTPTR * apP_Contents;

    PlayersMsg(AGENTPTR * inputplayers);

	protected:
  //Inherited as virtual and must be redefined:
	virtual void Insert(); //Must write to the default program output stream
    virtual void Put();    //Must write to the default program output stream

};
  
}
#endif
