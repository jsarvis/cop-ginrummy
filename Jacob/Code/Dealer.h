#ifndef DEALER_H
#define DEALER_H

#include <string>
#include <vector>

#include "SimMgmt.h"

#include "Melds.h"
#include "MeldsMsg.h"
#include "Card.h"
#include "CardMsg.h"
#include "Player.h"
#include "StockPile.h"
#include "DiscardPile.h"

using namespace std;
using namespace SimMgmt;

namespace SimModels {


    //Foward declaration
    //class Player;

    struct SpeedSettingIndexDealer {enum SpeedSettingIndexDealer1 { Speed_Shuffle =0, Speed_Deal};};

class Dealer: public Player {
private:

	StockPile * pSP_StockPile;

	DiscardPile DP_Discard;

	int State;

	int SpeedSettings[2];

protected:
	virtual void Get(ifstream& fin) throw (TokenError);

	virtual void Put(ostream& fout);

public:
	Dealer(ifstream& fin, StockPile * deck);

	void Initialize(Message * IncomingPlayersMsg);

	void Dispatch(Message * IncomingMsg);

	virtual void Extract(ifstream& fin) throw (TokenError);

	virtual void Insert(ostream& fout);

	void StartGame();

	Message * AcceptDrawStockPile();

	Message * AcceptDrawDiscardPile();

	Message * AcceptSorted();

	CardMsg * AcceptReceiveDiscard(Card * inputCard);

	CardMsg * AcceptReceiveReturnedCard(Card * inputCard);

	Message * AcceptHandEmpty();

	Message * AcceptShuffle();

	Message * AcceptShuffleComplete();

	Message * AcceptQueryTopCard();

private:
	void doAcceptDrawStockPile(Player * pP_Requester);

	void doAcceptDrawDiscardPile(Player * pP_Requester);

	void doAcceptSorted();

	void doAcceptReceiveDiscard(Card * inputCard);

	void doAcceptReceiveReturnedHand(Card * inputCard);

	void doAcceptHandEmpty();

	void doAcceptShuffle();

	void doAcceptShuffleComplete();

	void doAcceptQueryTopCard(Player * pP_Requester);

};

}

#endif

