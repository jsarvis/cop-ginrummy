#include "PlayersMsg.h"
namespace SimModels {
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
    simOutMgr.advToMargin();
	Message::Put();
	simOutMgr.advToMargin();
	simlog << " Players: ";
    simOutMgr.pushMargin();
    simOutMgr.advToMargin();
    simlog << " agent[ 0 ] = Player: " << apP_Contents[0]->NameOf();
    simOutMgr.advToMargin();
    simlog << " agent[ 1 ] = Dealer: " << apP_Contents[1]->NameOf();
	simOutMgr.popMargin();
    simOutMgr.popMargin();
}
}
