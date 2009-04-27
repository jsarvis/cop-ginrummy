#ifndef PLAYER_H
#define PLAYER_H

#include <string>
#include <vector>

#include "SimMgmt.h"

#include "Melds.h"
#include "MeldsMsg.h"
#include "Card.h"
#include "CardMsg.h"
#include "PlayersMsg.h"
//#include "Dealer.h"

using namespace std;
using namespace SimMgmt;

namespace SimModels {

    //Foward declaration
    class Dealer;


    struct SpeedSettingIndex {enum SpeedSettingIndex1 { Speed_InitialSort =0, Speed_Draw, Speed_Discard, Speed_DecisionPickup, Speed_DecisionDiscard}; }; 
    struct StrategyIndex {enum StrategyIndex1 { Type =0};};
    struct StrategyType {enum StrategyType1 { Beginner =0, Advanced};};

class Player: public Agent {
private:

	vector<Card> vC_Hand;

	int SpeedSettings[5];

	int Strategy[1];

	vector<Card> vC_CardMemory;

	Melds M_Melds;

	vector<Card> vC_DeadWood;

    int i_score;

protected:

    Player * pP_OtherPlayer;

	Dealer * pD_Dealer;

	virtual void Get(ifstream& fin) throw (TokenError);

	virtual void Put(ostream& fout);

    Player();

public:
	Player(ifstream& fin);

	void Initialize(Message * IncomingPlayersMsg);

	void Dispatch(Message * IncomingMsg);

	virtual void Extract(ifstream& fin) throw (TokenError);

	virtual void Insert(ostream& fout);

	int GetScore() { return i_score; }

	Message * AcceptYourTurn();

	MeldsMsg * AcceptKnock(Melds * inputMelds);

	CardMsg * AcceptDrawnCard(Card * inputCard);

	CardMsg * AcceptDealtCard(Card * inputCard);

	Message * AcceptDealComplete();

	Message * AcceptReturnHand();

	CardMsg * AcceptTopCard(Card * inputCard);

private:
	void doAcceptYourTurn();

	void doAcceptKnock(Melds * inputMelds);

	void doAcceptDrawnCard(Card * inputCard);

	void doAcceptDealtCard(Card * inputCard);

	void doAcceptDealComplete();

	void doAcceptReturnHand();

	void doAcceptTopCard(Card * inputCard);

};

}

#endif

