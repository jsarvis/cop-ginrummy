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
	double avgEvents;
	int maxEvents;
	int minTicks;
	double avgTicks;
	int maxTicks;
	
	int minPlayerTicks;
	double avgPlayerTicks;
	int maxPlayerTicks;
	
	int minDealerTicks;
	double avgDealerTicks;
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

