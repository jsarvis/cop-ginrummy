#include "MeldsMsg.h"

// MeldsMsg Methods

// constructor
MeldsMsg::MeldsMsg(int handler, string description, Melds* targetmelds)
			:Message(handler, description)
{
	pM_Contents = targetmelds;
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
	simlog << " pM_Contents: " << pM_Contents;
	simOutMgr.popMargin();
}
