#include "MeldsMsg.h"
namespace SimModels {
// MeldsMsg Methods

// constructor
MeldsMsg::MeldsMsg(int handler, string description, Melds* inputMelds)
			:Message(handler, description)
{
	pM_Contents = inputMelds;
}

void MeldsMsg::Insert()
{
	int delta = 10;
	ostream& simlog = simOutMgr.getStream();


    simOutMgr.pushMargin();
	simlog << "MeldsMsg{ ";

	Put();

	simOutMgr.advToMargin();
	simlog << "}MeldsMsg ";
	simOutMgr.popMargin();
}


void MeldsMsg::Put()
{
	ostream& simlog = simOutMgr.getStream();

	simOutMgr.pushMargin();
	Message::Put();
	simOutMgr.advToMargin();
	simlog << " **Melds** ";
	simOutMgr.popMargin();
}

}
