#include "CardMsg.h"

// CardMsg Methods

// constructor
CardMsg::CardMsg(int handler, string description, Card* targetcard)
			:Message(handler, description)
{
	pC_Contents = targetcard;
}

void CardMsg::Insert()
{
	int delta = 10;
	ostream& simlog = simOutMgr.getStream();


    simOutMgr.pushMargin();
	simlog << "CardMsg{ ";

	Put();

	simOutMgr.advToMargin();
	simlog << "}CardMsg ";
	simOutMgr.popMargin();
}


void CardMsg::Put()
{
	ostream& simlog = simOutMgr.getStream();

	simOutMgr.pushMargin();
	Message::Put();
	simOutMgr.advToMargin();
	simlog << " pC_Contents: " << pC_Contents;
	simOutMgr.popMargin();
}
