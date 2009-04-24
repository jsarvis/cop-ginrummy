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
		PlayersMsg *playersmessage = new PlayersMsg(apP_Players);
		

		playersmessage->setAgent( apP_Players[0]->NameOf(), apP_Players[0] );
		playersmessage->setAgent( apP_Players[1]->NameOf(), apP_Players[1] );
		
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
			lastEvent = e.getTime(); 
			numEvents++;
		}
		//code to terminate all players
		for( int i = 0; i < 2; i++)
		{
			apP_Players[i]->Dispatch(((apP_Players *)apP_Players[i])->AcceptTerminate());
		}
}

void GinRummy::WrapUp()
{

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
	simlog << *((Player *)apP_Players[0];
	simOutMgr.advToMargin();

	// insert Dealer
	simlog << "Dealer: ";
	simOutMgr.advToMargin();
	simlog << *((Dealer *)apP_Players[1];
	simOutMgr.popMargin();
	simOutMgr.advToMargin();

	// insert closing token
	simlog << "}GinRummy ";
	simOutMgr.popMargin();
	simOutMgr.advToMargin();
}

}
