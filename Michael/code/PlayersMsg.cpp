#include "PlayersMsg.h"

//PlayersMsg methods

// constructor
PlayersMsg::PlayersMsg(int handler, string description, AGENTPTR* inputplayers)
			:Message(handler, description)
{
	apP_Contents = inputplayers;
}

void PlayersMsg::Insert()
{
	int delta = 10;
	ostream& simlog = simOutMgr.getStream();


    simOutMgr.pushMargin();
	simlog << "PlayersMsg{ ";

	Put();

	simOutMgr.advToMargin();
	simlog << "}PlayersMsg ";
	simOutMgr.popMargin();
}


void PlayersMsg::Put()
{
	ostream& simlog = simOutMgr.getStream();

	simOutMgr.pushMargin();
	Message::Put();
	simOutMgr.advToMargin();
	simlog << " apP_Contents: " << apP_Contents;
	simOutMgr.popMargin();
}
