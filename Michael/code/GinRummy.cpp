#include "GinRummy.h"

namespace SimModels {
// GinRummy methods

// Constructor
GinRummy::GinRummy()
{
	ifstream& fin = simInMgr.getStream();

		
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
		apP_Players[1] = new Dealer(fin, &SP_Deck, this);
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
			//lastEvent = e.getTime(); 
			//numEvents++;
		}

}

void GinRummy::WrapUp()
{

	ostream& simlog = simOutMgr.getStream();


	//JACOB - I started writing commented calculations but I really
	// am not 100% certain where you want me to access all of this data
	// from. I'll try to figure it out monday morn, but I figured you
	// might already know making it easier to just talk to you.
	int i_value;
	int time;
	double d_value;
	int hour, min, sec;

	

	simlog << "Simulation Statistics:" << endl;
	simlog << "Minimum number of events : "
			<< i_value << endl; //15
	simlog << "Average number of events : "
			<< i_value << endl; //60
	simlog << "Maximum number of events : "
			<< i_value << endl; //140
	simlog << "Minimum game length in ticks: "
			<< i_value << endl; //72
	simlog << "Average game length in ticks: "
			<< i_value << endl; //1081
	simlog << "Maximum game length in ticks: "
			<< i_value << endl; //2712
	
	
	//time = ticks * secPerTick;
	//hour = time / (3600);
	//min = ( time % (3600) ) / 60;
	//sec = (time % 60);
	simlog << "Minimum game length in time: " 
			<< hour << ":" << min << ":" << sec << endl; //0:01:12
			
	//time = ticks * secPerTick;
	//hour = time / (3600);
	//min = ( time % (3600) ) / 60;
	//sec = (time % 60);
	simlog << "Average game length in time: " 
			<< hour << ":" << min << ":" << sec << endl; //0:18:01
	
	//time = ticks * secPerTick;
	//hour = time / (3600);
	//min = ( time % (3600) ) / 60;
	//sec = (time % 60);
	simlog << "Maximum game length in time: " 
			<< hour << ":" << min << ":" << sec << endl; //0:45:12
	simlog << "Minimum winning game length of Player in ticks: "
			<< i_value << endl; //72
	simlog << "Average winning game length of Player in ticks: "
			<< i_value << endl; //902
	simlog << "Maximum winning game length of Player in ticks: "
			<< i_value << endl; //2201
	
	//time = ticks * secPerTick;
	//hour = time / (3600);
	//min = ( time % (3600) ) / 60;
	//sec = (time % 60);
	simlog << "Minimum winning game length of Player in time: " 
			<< hour << ":" << min << ":" << sec << endl; //0:01:12
	
	//time = ticks * secPerTick;
	//hour = time / (3600);
	//min = ( time % (3600) ) / 60;
	//sec = (time % 60);
	simlog << "Average winning game length of Player in time: " 
			<< hour << ":" << min << ":" << sec << endl; //0:15:02
	
	//time = ticks * secPerTick;
	//hour = time / (3600);
	//min = ( time % (3600) ) / 60;
	//sec = (time % 60);
	simlog << "Maximum winning game length of Player in time: " 
			<< hour << ":" << min << ":" << sec << endl; //0:36:41
	simlog << "Minimum winning game length of Dealer in ticks: "
			<< i_value << endl; //91
	simlog << "Average winning game length of Dealer in ticks: "
			<< i_value << endl; //1204
	simlog << "Maximum winning game length of Dealer in ticks: "
			<< i_value << endl; //2712
	
	//time = ticks * secPerTick;
	//hour = time / (3600);
	//min = ( time % (3600) ) / 60;
	//sec = (time % 60);
	simlog << "Minimum winning game length of Dealer in time: " 
			<< hour << ":" << min << ":" << sec << endl; //0:01:31
	
	//time = ticks * secPerTick;
	//hour = time / (3600);
	//min = ( time % (3600) ) / 60;
	//sec = (time % 60);
	simlog << "Average winning game length of Dealer in time: " 
			<< hour << ":" << min << ":" << sec << endl; //0:20:04
	
	//time = ticks * secPerTick;
	//hour = time / (3600);
	//min = ( time % (3600) ) / 60;
	//sec = (time % 60);
	simlog << "Maximum winning game length of Dealer in time: " 
			<< hour << ":" << min << ":" << sec << endl; //0:45:12
	
	simlog << "Player wins per hour: " << d_value << endl; //3.991
	simlog << "Dealer wins per hour: " << d_value << endl; //2.990
	simlog << "Percentage Player wins: " << d_value << endl; //57.169
	simlog << "Percentage Dealer wins: " << d_value << endl; // 42.831

}

void GinRummy::Insert()
{
	ostream& simlog = simOutMgr.getStream();

	// opening token
    simOutMgr.newLine();
	simOutMgr.pushMargin();
	simlog << "GinRummy{ ";
    simOutMgr.pushMargin();

	// insert SecondsPerTick
	simlog << "SecondsPerTick: " << i_SecondsPerTick;
	simOutMgr.advToMargin();

	// insert Rounds
	simlog << "Rounds: " << i_NumberOfRounds;
	simOutMgr.advToMargin();

	// insert Player
	simlog << "Player: ";
	simOutMgr.advToMargin();
	simlog << *((Player *)apP_Players[0]);
	simOutMgr.advToMargin();

	// insert Dealer
	simlog << "Dealer: ";
	simOutMgr.advToMargin();
	simlog << *((Dealer *)apP_Players[1]);
	simOutMgr.popMargin();
	simOutMgr.advToMargin();

	// insert closing token
	simlog << "}GinRummy ";
	simOutMgr.popMargin();
	simOutMgr.advToMargin();
}

}
