#include "GinRummy.h"
#include <time.h>

namespace SimModels {
// GinRummy methods


GinRummy::~GinRummy()
{

}
// Constructor
GinRummy::GinRummy()
{
	ostream& simlog = simOutMgr.getStream();
	ifstream& fin = simInMgr.getStream();

			time_t rawtime;
		struct tm * timeinfo;
		char TimeStamp[80];
		
		time ( &rawtime );
		timeinfo = localtime ( &rawtime );
		
		strftime (TimeStamp,80,"%a %b %d %X %Y",timeinfo);

		simlog << "Date and time of run : " << TimeStamp << endl;
		simlog << "Project : Gin Rummy Simulator" << endl;

		
		for(int k = 1; k < 53; k++) {
                SP_Deck.Add(Card(k));
        }



		string token;

		// Parse opening token
		fin >> token;
		if ( token != "GinRummy{" ) 
		   throw AppError(string("Incorrect Token '" + token + "', excpected token 'GinRummy{' !"),
				string("GinRummy::GinRummy())"));
		
		// Parse secondspertick
		fin >> token;
		if ( token != "SecondsPerTick:" ) 
		   throw AppError(string("Incorrect Token '" + token + "', excpected token 'SecondsPerTick:' !"),
				string("GinRummy::GinRummy())"));
		fin >> i_SecondsPerTick;

		// Parse numberofrounds
		fin >> token;
		if ( token != "Rounds:" ) 
		   throw AppError(string("Incorrect Token '" + token + "', excpected token 'Rounds:' !"),
				string("GinRummy::GinRummy())"));
		fin >> i_NumberOfRounds;

		// Parse player
		fin >> token;
		if ( token != "Player:" ) 
		   throw AppError(string("Incorrect Token '" + token + "', excpected token 'Player:' !"),
				string("GinRummy::GinRummy())"));
		apP_Players[0] = new Player(fin);
		//apP_Players[0]->Extract();

		// Parse dealer
		fin >> token;
		if ( token != "Dealer:" ) 
		   throw AppError(string("Incorrect Token '" + token + "', excpected token 'Dealer:' !"),
				string("GinRummy::GinRummy())"));
		apP_Players[1] = new Dealer(fin, &SP_Deck);
		//apP_Players[1]->Extract();

		// Parse closing token
		fin >> token;
		if ( token != "}GinRummy" ) 
			throw AppError(string("Incorrect Token '" + token + "', excpected token '}GinRummy' !"),
				string("GinRummy::GinRummy())"));
		
}

void GinRummy::Initialize()
{
	ostream& simlog = simOutMgr.getStream();

		// Construct new Players object
		PlayersMsg *playersmessage = new PlayersMsg(0,"Initialize Players",apP_Players);
		

		//playersmessage->setAgent( apP_Players[0]->NameOf(), apP_Players[0] );
		//playersmessage->setAgent( apP_Players[1]->NameOf(), apP_Players[1] );
		
		apP_Players[0]->Initialize( playersmessage );
		apP_Players[1]->Initialize( playersmessage );

        simOutMgr.newLine();
		simlog << *playersmessage;
        simOutMgr.newLine();

		delete playersmessage;
}

void GinRummy::Simulate()
{
	Event    e;
        Message *msg;
		string   token;
		ostream& simlog = simOutMgr.getStream();
		bool firstPlayerWin = true;
		bool firstDealerWin = true;
		bool firstGame = true;
		int numEvents;
		int lastGameTickCount = 0;
		
		for(int i = 0; i < i_NumberOfRounds; i++) {
			
			((Dealer*)apP_Players[1])->StartGame();
			
			simOutMgr.newLine();
			simOutMgr.advToMargin();
			simlog << "Game" << (i+1) << "{";
			numEvents = 0;
			
			while( theEventMgr.moreEvents() )
			{
				//retrive next event and message
				e   = theEventMgr.getNextEvent();
				msg = e.getMsg();
			
				// Output to simlog
				simOutMgr.newLine();
				simlog << e;
				simOutMgr.newLine();

				// Dispatch
				e.getRecvr()->Dispatch( msg );  
				
				// destruct message
				delete msg; 

				// Update statistical data
				numEvents++;
			}
			
			int PlayerScore = ( ((Player*)apP_Players[0])->GetScore() );
			int DealerScore = ( ((Player*)apP_Players[1])->GetScore() );
			int gameTicks = theEventMgr.clock() - lastGameTickCount;
			lastGameTickCount = theEventMgr.clock();
				
				// Fill in all fields of StatisticalData with initial values
			if (firstGame) {
				StatisticalData.minEvents = numEvents;
				StatisticalData.totalEvents = numEvents;
				StatisticalData.maxEvents = numEvents;
				StatisticalData.minTicks = gameTicks;
				StatisticalData.maxTicks = gameTicks;
				
				StatisticalData.minPlayerTicks = 0;
				StatisticalData.totalPlayerTicks = 0;
				StatisticalData.maxPlayerTicks = 0;
				
				StatisticalData.minDealerTicks = 0;
				StatisticalData.totalDealerTicks = 0;
				StatisticalData.maxDealerTicks = 0;
				
				StatisticalData.playerWinCount = 0;
				StatisticalData.dealerWinCount = 0;
				
				firstGame = false;
			} else {
				if ( numEvents < StatisticalData.minEvents )
					StatisticalData.minEvents = numEvents;
					
				StatisticalData.totalEvents += numEvents;
				
				if ( numEvents > StatisticalData.maxEvents )
					StatisticalData.maxEvents = numEvents;
					
					
				if ( gameTicks < StatisticalData.minTicks )
					StatisticalData.minTicks = gameTicks;
					
				if ( gameTicks > StatisticalData.maxTicks )
					StatisticalData.maxTicks = gameTicks;
			}
			
			if (firstPlayerWin &&  (PlayerScore < DealerScore) ) { //Player never won, but he has no
				StatisticalData.minPlayerTicks = gameTicks;
				StatisticalData.totalPlayerTicks = gameTicks;
				StatisticalData.maxPlayerTicks = gameTicks;
				
				StatisticalData.playerWinCount = 1;
			} else if (firstDealerWin &&  (PlayerScore > DealerScore) ) {
				StatisticalData.minDealerTicks = gameTicks;
				StatisticalData.totalDealerTicks = gameTicks;
				StatisticalData.maxDealerTicks = gameTicks;
				
				StatisticalData.dealerWinCount = 1;
			} else if (PlayerScore < DealerScore) {
				
				if ( gameTicks < StatisticalData.minPlayerTicks )
					StatisticalData.minPlayerTicks = gameTicks;
					
				StatisticalData.totalPlayerTicks += gameTicks;
				
				if ( gameTicks > StatisticalData.maxPlayerTicks )
					StatisticalData.maxPlayerTicks = gameTicks;
				
				StatisticalData.playerWinCount++;
				
			} else if (PlayerScore > DealerScore) {
				
				if ( gameTicks < StatisticalData.minDealerTicks )
					StatisticalData.minDealerTicks = gameTicks;
					
				StatisticalData.totalDealerTicks += gameTicks;
				
				if ( gameTicks > StatisticalData.maxDealerTicks )
					StatisticalData.maxDealerTicks = gameTicks;
				
				StatisticalData.dealerWinCount++;
				
			}
			
			simOutMgr.newLine();
			simOutMgr.advToMargin();
			simlog << "}Game" << (i+1);
		
		}
		
		StatisticalData.totalTicks = theEventMgr.clock();
}

void GinRummy::WrapUp()
{

	ostream& simlog = simOutMgr.getStream();


	//JACOB - I started writing commented calculations but I really
	// am not 100% certain where you want me to access all of this data
	// from. I'll try to figure it out monday morn, but I figured you
	// might already know making it easier to just talk to you.
	int time;
	int hour, min, sec;

	simlog << endl << "Simulation Statistics:" << endl;
	simlog << "Minimum number of events : "
			<< StatisticalData.minEvents << endl; //15
	simlog << "Average number of events : "
			<< ((double)StatisticalData.totalEvents / (double)i_NumberOfRounds)  << endl; //60
	simlog << "Maximum number of events : "
			<< StatisticalData.maxEvents << endl; //140
	simlog << "Minimum game length in ticks: "
			<< StatisticalData.minTicks << endl; //72
	simlog << "Average game length in ticks: "
			<< ((double)StatisticalData.totalTicks / (double)i_NumberOfRounds) << endl; //1081
	simlog << "Maximum game length in ticks: "
			<< StatisticalData.maxTicks << endl; //2712
	
	
	time = StatisticalData.minTicks * i_SecondsPerTick;
	hour = time / (3600);
	min = ( time % (3600) ) / 60;
	sec = (time % 60);
	simlog << "Minimum game length in time: " 
			<< hour << ":" << min << ":" << sec << endl; //0:01:12
			
	time = (StatisticalData.totalTicks / i_NumberOfRounds) * i_SecondsPerTick;
	hour = time / (3600);
	min = ( time % (3600) ) / 60;
	sec = (time % 60);
	simlog << "Average game length in time: " 
			<< hour << ":" << min << ":" << sec << endl; //0:18:01
	
	time = StatisticalData.maxTicks * i_SecondsPerTick;
	hour = time / (3600);
	min = ( time % (3600) ) / 60;
	sec = (time % 60);
	simlog << "Maximum game length in time: " 
			<< hour << ":" << min << ":" << sec << endl; //0:45:12
			
			
	simlog << "Minimum winning game length of Player in ticks: "
			<< StatisticalData.minPlayerTicks << endl; //72
	simlog << "Average winning game length of Player in ticks: "
			<< ((double)StatisticalData.totalPlayerTicks / (double)StatisticalData.playerWinCount) << endl; //902
	simlog << "Maximum winning game length of Player in ticks: "
			<< StatisticalData.maxPlayerTicks << endl; //2201
	
	time = StatisticalData.minPlayerTicks * i_SecondsPerTick;
	hour = time / (3600);
	min = ( time % (3600) ) / 60;
	sec = (time % 60);
	simlog << "Minimum winning game length of Player in time: " 
			<< hour << ":" << min << ":" << sec << endl; //0:01:12
	
	time = (StatisticalData.totalPlayerTicks / playerWinCount) * i_SecondsPerTick;
	hour = time / (3600);
	min = ( time % (3600) ) / 60;
	sec = (time % 60);
	simlog << "Average winning game length of Player in time: " 
			<< hour << ":" << min << ":" << sec << endl; //0:15:02
	
	time = StatisticalData.maxPlayerTicks * i_SecondsPerTick;
	hour = time / (3600);
	min = ( time % (3600) ) / 60;
	sec = (time % 60);
	simlog << "Maximum winning game length of Player in time: " 
			<< hour << ":" << min << ":" << sec << endl; //0:36:41
			
			
	simlog << "Minimum winning game length of Dealer in ticks: "
			<< StatisticalData.minDealerTicks << endl; //91
	simlog << "Average winning game length of Dealer in ticks: "
			<< ((double)StatisticalData.totalDealerTicks / (double)StatisticalData.dealerWinCount) << endl; //1204
	simlog << "Maximum winning game length of Dealer in ticks: "
			<< StatisticalData.maxDealerTicks << endl; //2712
			
	time = StatisticalData.minDealerTicks * i_SecondsPerTick;
	hour = time / (3600);
	min = ( time % (3600) ) / 60;
	sec = (time % 60);
	simlog << "Minimum winning game length of Dealer in time: " 
			<< hour << ":" << min << ":" << sec << endl; //0:01:31
	
	time = (StatisticalData.totalDealerTicks / dealerWinCount) * i_SecondsPerTick;
	hour = time / (3600);
	min = ( time % (3600) ) / 60;
	sec = (time % 60);
	simlog << "Average winning game length of Dealer in time: " 
			<< hour << ":" << min << ":" << sec << endl; //0:20:04
	
	time = StatisticalData.maxDealerTicks * i_SecondsPerTick;
	hour = time / (3600);
	min = ( time % (3600) ) / 60;
	sec = (time % 60);
	simlog << "Maximum winning game length of Dealer in time: " 
			<< hour << ":" << min << ":" << sec << endl; //0:45:12
			
			
						/*
 * struct StatData {
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
 */
			
	
	simlog << "Player wins per hour: " << StatisticalData.playerWinCount / ( (totalTicks * i_SecondsPerTick) / 3600) << endl; //3.991
	simlog << "Dealer wins per hour: " << StatisticalData.dealerWinCount / ( (totalTicks * i_SecondsPerTick) / 3600) << endl; //2.990
	simlog << "Percentage Player wins: " << (StatisticalData.playerWinCount / i_NumberOfRounds) << endl; //57.169
	simlog << "Percentage Dealer wins: " << (StatisticalData.dealerWinCount / i_NumberOfRounds) << endl; // 42.831
	simlog << "Percentage Draws: " << ((i_NumberOfRounds - (StatisticalData.dealerWinCount + StatisticalData.playerWinCount)) / i_NumberOfRounds) << endl; // 42.831

}

void GinRummy::Insert()
{
	ostream& simlog = simOutMgr.getStream();

	// opening token
    simOutMgr.newLine();
	simOutMgr.pushMargin();
	simOutMgr.advToMargin();
	simlog << "GinRummy{ ";
    simOutMgr.pushMargin();

	// insert SecondsPerTick
	simOutMgr.advToMargin();
	simlog << "SecondsPerTick: " << i_SecondsPerTick;

	// insert Rounds
	simOutMgr.advToMargin();
	simlog << "Rounds: " << i_NumberOfRounds;

	// insert Player
	simOutMgr.advToMargin();
	simlog << "Player: ";
	simOutMgr.pushMargin();
	simOutMgr.advToMargin();
	((Player *)apP_Players[0])->Insert(simlog);
	simOutMgr.popMargin();

	// insert Dealer
	simOutMgr.advToMargin();
	simlog << "Dealer: ";
	simOutMgr.pushMargin();
	simOutMgr.advToMargin();
	((Dealer *)apP_Players[1])->Insert(simlog);
	simOutMgr.popMargin();
	simOutMgr.popMargin();

	// insert closing token
	simOutMgr.advToMargin();
	simlog << "}GinRummy ";
	simOutMgr.popMargin();
	simOutMgr.newLine();
}

}
