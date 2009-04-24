#include "CardMsg.h"

namespace SimModels {
// CardMsg Methods

// constructor
CardMsg::CardMsg(int handler, string description, Card* inputCard)
			:Message(handler, description)
{
	pC_Contents = inputCard;
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
	simlog << " Card: " << pC_Contents->toString();
	simOutMgr.popMargin();
}

}
