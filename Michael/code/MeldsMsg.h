#ifndef MELDSMSG_H
#define MELDSMSG_H

#include <string>
#include <vector>

#include "SimMgmt.h"
#include "Melds.h"

using namespace std;
using namespace SimMgmt;

namespace SimModels {
          


class MeldsMsg : public Message {
  public:
    Melds* pM_Contents;
    MeldsMsg(int handler, string description, Melds* meldstarget);

  protected:
  //Inherited as virtual and must be redefined:
	virtual void Insert(); //Must write to the default program output stream
    virtual void Put();    //Must write to the default program output stream

};

}  
#endif
