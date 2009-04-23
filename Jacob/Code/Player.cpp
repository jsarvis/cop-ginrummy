#include "Player.h"

namespace SimModels {

    //protected
    void Player::Get(ifstream& fin) throw (TokenError) {
        string token;

        // parse inherited members 
		Agent::Get(); 
		
		// parse token "Speed_InitialSort"
		fin >> token;
		if ( token != "Speed_InitialSort:" ) 
		   throw TokenError(string("Incorrect Token '" + token + "', excpected 'Speed_InitialSort:' !"),
                            string("Player::Get(@1)"));

		// Parse Speed_InitialSort
		fin >> token;
		SpeedSettings[SpeedSettingIndex::Speed_InitialSort] = atoi(token.c_str());  

        // parse token "Speed_Draw"
		fin >> token;
		if ( token != "Speed_Draw:" ) 
		   throw TokenError(string("Incorrect Token '" + token + "', excpected 'Speed_Draw:' !"),
                            string("Player::Get(@2)"));

		// Parse Speed_Draw
		fin >> token;
		SpeedSettings[SpeedSettingIndex::Speed_Draw] = atoi(token.c_str());  

        // parse token "Speed_Discard"
		fin >> token;
		if ( token != "Speed_Discard:" ) 
		   throw TokenError(string("Incorrect Token '" + token + "', excpected 'Speed_Discard:' !"),
                            string("Player::Get(@3)"));

		// Parse Speed_Discard
		fin >> token;
		SpeedSettings[SpeedSettingIndex::Speed_Discard] = atoi(token.c_str());  

        // parse token "Speed_DecisionPickup"
		fin >> token;
		if ( token != "Speed_DecisionPickup:" ) 
		   throw TokenError(string("Incorrect Token '" + token + "', excpected 'Speed_DecisionPickup:' !"),
                            string("Player::Get(@4)"));

		// Parse Speed_DecisionPickup
		fin >> token;
		SpeedSettings[SpeedSettingIndex::Speed_DecisionPickup] = atoi(token.c_str());  

        // parse token "Speed_DecisionDiscard"
		fin >> token;
		if ( token != "Speed_DecisionDiscard:" ) 
		   throw TokenError(string("Incorrect Token '" + token + "', excpected 'Speed_DecisionDiscard:' !"),
                            string("Player::Get(@5)"));

		// Parse Speed_DecisionDiscard
		fin >> token;
		SpeedSettings[SpeedSettingIndex::Speed_DecisionDiscard] = atoi(token.c_str());  
		
    }

	void Player::Put(ostream& fout) {

        simOutMgr.pushMargin();
		Agent::Put();
		simOutMgr.advToMargin();
		fout << " Speed_InitialSort: " << SpeedSettings[SpeedSettingIndex::Speed_InitialSort];
        simOutMgr.advToMargin();
		fout << " Speed_Draw: " << SpeedSettings[SpeedSettingIndex::Speed_Draw];
        simOutMgr.advToMargin();
		fout << " Speed_Discard: " << SpeedSettings[SpeedSettingIndex::Speed_Discard];
        simOutMgr.advToMargin();
		fout << " Speed_DecisionPickup: " << SpeedSettings[SpeedSettingIndex::Speed_DecisionPickup];
        simOutMgr.advToMargin();
		fout << " Speed_DecisionDiscard: " << SpeedSettings[SpeedSettingIndex::Speed_DecisionDiscard];
		simOutMgr.popMargin();

    }

    //public
	void Player::Player(ifstream& fin):Agent() {
        
        Extract(fin);

    }

	void Player::Initialize(Message * IncomingPlayersMsg) {

        // Find other player, IE the player that isnt the same as this
		if (((PlayersMsg *)IncomingPlayersMsg)->apP_Contents[0] == this)
            pP_OtherPlayer = ((PlayersMsg *)IncomingPlayersMsg)->apP_Contents[1];
        else pP_OtherPlayer = ((PlayersMsg *)IncomingPlayersMsg)->apP_Contents[0];

        //Dealer is always second in position
        pD_Dealer = ((PlayersMsg *)IncomingPlayersMsg)->apP_Contents[1];

    }

	void Player::Dispatch(Message * IncomingMsg) {

		switch( IncomingMsg->getHandler() )
		{
		case 1: doAcceptYourTurn(); break;
		case 2: {
					doAcceptKnock( ((MeldsMsg *)IncomingMsg)->pM_Contents );
					break;
				}
        case 3: {
					doAcceptDealtCard( ((CardMsg *)IncomingMsg)->pC_Contents );
					break;
				}
        case 4: {
					doAcceptDrawnCard( ((CardMsg *)IncomingMsg)->pC_Contents );
					break;
				}
		case 5: doAcceptDealComplete(); break;
        case 6: doAcceptReturnHand(); break;
        case 7: {
                doAcceptTopCard( ((CardMsg *)IncomingMsg)->pC_Contents );
                break;
            }
		default: throw AppError("Undefined handler ID!", "Player::Dispatch()");
		}

    }

	void Player::Extract(ifstream& fin) throw (TokenError) {

        string token;

        // Parse opening token
        fin >> token;
        if ( token != "Player{" ) 
            throw TokenError(string("Incorrect Token, '" + token + "', excpected 'Player{' !"),
                             string("Player::Extract(@1)"));
        
        // Parse data members
        Get();

        // Parse closing token
        fin >> token; 
        if ( token != "}Player" ) 
            throw TokenError(string("Incorrect Token '" + token + "', excpected token '}Player' !"),
                             string("Player::Extract(@2)"));

    }

	void Player::Insert(ostream& fout) {

        simOutMgr.pushMargin();
		fout << "Player{ ";
		Put();
		simOutMgr.advToMargin();
		fout << "}Player ";
		simOutMgr.popMargin();

    }

	Message * Player::AcceptYourTurn() {
        return new Message(1,"Your turn");
    }

	MeldsMsg * Player::AcceptKnock(Melds * inputMelds) {
        return new MeldsMsg(2,"Knock",inputMelds);
    }

	CardMsg * Player::AcceptDrawnCard(Card * inputCard) {
        return new CardMsg(4,"Card Drawn",inputCard);
    }

	CardMsg * Player::AcceptDealtCard(Card * inputCard) {
        return new CardMsg(3,"Card Dealt",inputCard);
    }

	Message * Player::AcceptDealComplete() {
        return new Message(5,"The hands are dealt");
    }

	Message * Player::AcceptReturnHand() {
        return new Message(6,"Return hand");
    }

	CardMsg * Player::AcceptTopCard(Card * inputCard) {
        return new CardMsg(7,"Top Card",inputCard);
    }

    //private
	void Player::doAcceptYourTurn() {

        int time = theEventMgr.clock();
		
		// Construct new message
        RecipientMsg *queryMsg = pD_Dealer->AcceptQueryTopCard(this);

		// Construct new Event
		Event e( time , this , pD_Dealer , queryMsg );

		// Post Event
		theEventMgr.postEvent(e);

    }

	void Player::doAcceptKnock(Melds * inputMelds) {
        
        //TODO: Play deadwood and set score


        int time = theEventMgr.clock();
		
		// Construct new message
        //TODO / TEST: Okay to have two pointers to same message in two different events?
        Message *returnhandMsg = AcceptReturnHand();

		// Construct new Event
		Event e1( time  , this , this , returnhandMsg );
        Event e2( time  , this , pP_OtherPlayer , returnhandMsg );

		// Post Events
		theEventMgr.postEvent(e1);
        theEventMgr.postEvent(e2);

    }

	void Player::doAcceptDrawnCard(Card * inputCard) {

        ostream& simlog = simOutMgr.getStream();
        vector<Card>::iterator iter;

        //TODO: Insert card in sorted position

        simlog << NameOf() << ": Sorted hand:";

        //TODO / TEST: should this be (*iter).toString() instead of iter->toString() ??
        for( iter = vC_Hand.begin(); iter != vC_Hand.end(); iter++ ) {

            simlog << " " << iter->toString();

        }
        simlog << endl;


        //TODO: Select card to discard and/or knock

        //IF discarding
        { 
            simlog << NameOf() << ": Sorted hand:";
    
            //TODO / TEST: should this be (*iter).toString() instead of iter->toString() ??
            for( iter = vC_Hand.begin(); iter != vC_Hand.end(); iter++ ) {
    
                simlog << " " << iter->toString();
    
            }
            simlog << endl << endl;
        }

    }

	void Player::doAcceptDealtCard(Card * inputCard) {
        vC_Hand.push_back(*inputCard);
    }

	void Player::doAcceptDealComplete() {

        ostream& simlog = simOutMgr.getStream();

        //TODO / TEST: Advancing to margin appropriate or clean looking?
        simOutMgr.advToMargin();
		simlog << NameOf() << ": Resetting score" << endl;
        i_score = -1; //Assumed draw

        simlog << NameOf() << ": Unsorted hand:";

        vector<Card>::iterator iter;
        
        for( iter = vC_Hand.begin(); iter != vC_Hand.end(); iter++ ) {
 
            simlog << " " << iter->toString();

        }
        simlog << endl;
        

        //TODO: Sort hand


        int time = theEventMgr.clock();
		
		// Construct new message
        Message *sortedMsg = pD_Dealer->AcceptSorted();

		// Construct new Event
		Event e( time + SpeedSettings[SpeedSettingIndex::Speed_InitialSort] , this , pD_Dealer , sortedMsg );

		// Post Event
		theEventMgr.postEvent(e);


        simlog << NameOf() << ": Sorted hand:";

        //TODO / TEST: should this be (*iter).toString() instead of iter->toString() ??
        for( iter = vC_Hand.begin(); iter != vC_Hand.end(); iter++ ) {

            simlog << " " << iter->toString();

        }
        simlog << endl << endl;

    }

	void Player::doAcceptReturnHand() {

        int time = theEventMgr.clock();

        vector<Card>::iterator iter;

        CardMsg *tempCardMsg;
        
        for( iter = vC_Hand.begin(); iter != vC_Hand.end(); iter++ ) {
 
            //TODO / TEST: replace iter with  (Card *)&(*iter)   ??
            tempCardMsg = pD_Dealer->AcceptReceiveReturnedCard(iter);

            // Construct new Event
    		Event e( time , this , pD_Dealer , tempCardMsg );
    
    		// Post Event
    		theEventMgr.postEvent(e);

        }

        vC_Hand.clear();

        Message *doneWithReturn = pD_Dealer->AcceptHandEmpty();

        // Construct new Event
		Event e( time , this , pD_Dealer , doneWithReturn );

		// Post Event
		theEventMgr.postEvent(e);

    }

	void Player::doAcceptTopCard(Card * inputCard) {

        //TODO: Select card to draw
    }
}

