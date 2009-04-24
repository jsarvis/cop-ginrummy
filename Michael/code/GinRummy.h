#ifndef GINRUMMY_H
#define GINRUMMY_H

#include <string>
#include <vector>

#include "SimMgmt.h"

//#include "Player.h"
//#include "Dealer.h"
#include "StockPile.h"

using namespace std;
using namespace SimMgmt;

namespace SimModels {

class GinRummy {
public:
	GinRummy();
	~GinRummy();
	void Initialize();

	void Simulate();

	void WrapUp();

	//Writes to the default program output stream
	void Insert();

    void signalGameOver();

private:
	int i_NumberOfRounds;

    int i_SecondsPerTick;

	//dynamic array of Agent*
	AGENTPTR * apP_Players;

	void * StatisticalData;

	StockPile SP_Deck;

    bool b_onGoingGame;

};

}

#endif

