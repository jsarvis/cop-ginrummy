#ifndef GINRUMMY_H
#define GINRUMMY_H

#include <string>
#include <vector>

#include "SimMgmt.h"

#include "Player.h"
#include "Dealer.h"
#include "StockPile.h"

using namespace std;
using namespace SimMgmt;

namespace SimModels {

struct StatData {
	int minEvents;
	int totalEvents;
	int maxEvents;
	int minTicks;
	int totalTicks;
	int maxTicks;
	
	int minPlayerTicks;
	int totalPlayerTicks;
	int maxPlayerTicks;
	
	int minDealerTicks;
	int totalDealerTicks;
	int maxDealerTicks;
	
	int playerWinCount;
	int dealerWinCount;
};

class GinRummy {
public:
	GinRummy();
	~GinRummy();
	void Initialize();

	void Simulate();

	void WrapUp();

	//Writes to the default program output stream
	void Insert();

private:
	int i_NumberOfRounds;

    int i_SecondsPerTick;

	AGENTPTR apP_Players[2];

	void * StatisticalData;

	StockPile SP_Deck;


};

}

#endif

