#ifndef CARDMSG_H
#define CARDMSG_H

#include <string>
#include <vector>

#include "SimMgmt.h"
#include "Card.h"

using namespace std;
using namespace SimMgmt;

namespace SimModels {
          
class CardMsg : public Message {
  public:
    Card* pC_Contents;
    CardMsg(int handler, string description, Card* targetcard);

  protected:
  //Inherited as virtual and must be redefined:
	virtual void Insert(); //Must write to the default program output stream
    virtual void Put();    //Must write to the default program output stream


};
  
}
#endif
