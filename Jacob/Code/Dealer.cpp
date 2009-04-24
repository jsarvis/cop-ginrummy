#include "Dealer.h"
#include "Player.h"
#include "GinRummy.h"

namespace SimModels {

    //protected
    void Dealer::Get(ifstream& fin) throw (TokenError) {
        string token;

        // parse inherited members 
        Player::Get(fin); 

        // parse token "Speed_Shuffle"
        fin >> token;
        if ( token != "Speed_Shuffle:" ) 
           throw TokenError(string("Incorrect Token '" + token + "', expected 'Speed_Shuffle:' !"),
                            string("Dealer::Get(@1)"));

        // Parse Speed_Shuffle
        fin >> token;
        SpeedSettings[SpeedSettingIndexDealer::Speed_Shuffle] = atoi(token.c_str());  

        // parse token "Speed_Deal"
        fin >> token;
        if ( token != "Speed_Deal:" ) 
           throw TokenError(string("Incorrect Token '" + token + "', expected 'Speed_Deal:' !"),
                            string("Dealer::Get(@2)"));

        // Parse Speed_Deal
        fin >> token;
        SpeedSettings[SpeedSettingIndexDealer::Speed_Deal] = atoi(token.c_str());  

    }

    void Dealer::Put(ostream& fout) {

        simOutMgr.pushMargin();
        Player::Put(fout);
        simOutMgr.advToMargin();
        fout << " Speed_Shuffle: " << SpeedSettings[SpeedSettingIndexDealer::Speed_Shuffle];
        simOutMgr.advToMargin();
        fout << " Speed_Deal: " << SpeedSettings[SpeedSettingIndexDealer::Speed_Deal];
        simOutMgr.popMargin();

    }

    //public
    Dealer::Dealer(ifstream& fin, StockPile * deck, GinRummy * inputGameControl):Player(fin) {

        Extract(fin);

        pSP_StockPile = deck;

        GameControl = inputGameControl;

        State = -1; //Not initialized

    }

    void Dealer::Initialize(Message * IncomingPlayersMsg) {

        Player::Initialize(IncomingPlayersMsg);

        State = 0; //Initialized

    }

    void Dealer::Dispatch(Message * IncomingMsg) {

        switch( IncomingMsg->getHandler() )
		{
		case 1: 
		case 2: 
        case 3: 
        case 4: 
		case 5: 
        case 6: 
        case 7: {
                    Player::Dispatch(IncomingMsg);
                    break;
                }
        case 8: {
					doAcceptDrawStockPile( (Player*)theEventMgr.getSendr() );
					break;
				}
		case 9: {
					doAcceptDrawDiscardPile( (Player*)theEventMgr.getSendr() );
					break;
				}
        case 10: doAcceptSorted(); break;
        case 11: {
                    doAcceptReceiveDiscard( ((CardMsg *)IncomingMsg)->pC_Contents );
                    break;
                 }
		case 12: {
                    doAcceptReceiveReturnedHand( ((CardMsg *)IncomingMsg)->pC_Contents );
                    break;
                 }
        case 13: doAcceptHandEmpty(); break;
        case 14: {
					doAcceptQueryTopCard( (Player*)theEventMgr.getSendr() );
					break;
				 }
        case 15: doAcceptShuffle(); break;
        case 16: doAcceptShuffleComplete(); break;
		default: throw AppError("Undefined handler ID!", "Dealer::Dispatch()");
		}

    }
    
    void Dealer::Extract(ifstream& fin) throw (TokenError) {

        string token;

        // Parse opening token
        fin >> token;
        if ( token != "Dealer{" ) 
            throw TokenError(string("Incorrect Token, '" + token + "', expected 'Dealer{' !"),
                             string("Dealer::Extract(@1)"));

        // Parse data members
        Get(fin);

        // Parse closing token
        fin >> token; 
        if ( token != "}Dealer" ) 
            throw TokenError(string("Incorrect Token '" + token + "', expected token '}Dealer' !"),
                             string("Dealer::Extract(@2)"));

    }

    void Dealer::Insert(ostream& fout) {

        simOutMgr.pushMargin();
        fout << "Dealer{ ";
        Put(fout);
        simOutMgr.advToMargin();
        fout << "}Dealer ";
        simOutMgr.popMargin();

    }

	void Dealer::StartGame() {

        if (State == 0) {
    
            // Construct new message
            Message *shuffleMsg = AcceptShuffle();
     
            // Construct new Event
            Event e( 0 , this , this, shuffleMsg );
    
            // Post Event
            theEventMgr.postEvent(e);
        } else {
            //TODO: AppError, dealer not ready
        }

    }

	Message * Dealer::AcceptDrawStockPile() {
        return new Message(8,"Draw stock pile");
    }

	Message * Dealer::AcceptDrawDiscardPile() {
        return new Message(9,"Draw discard");
    }

	Message * Dealer::AcceptSorted() {
        return new Message(10,"The cards are sorted");
    }

	CardMsg * Dealer::AcceptReceiveDiscard(Card * inputCard) {
        return new CardMsg(11,"Card to discard",inputCard);
    }

	CardMsg * Dealer::AcceptReceiveReturnedCard(Card * inputCard) {
        return new CardMsg(12,"Card to return",inputCard);
    }

	Message * Dealer::AcceptHandEmpty() {
        return new Message(13,"Hand empty");
    }

	Message * Dealer::AcceptShuffle() {
        return new Message(15,"Shuffle the stock pile");
    }

	Message * Dealer::AcceptShuffleComplete() {
        return new Message(16,"The stock pile is shuffled");
    }

	Message * Dealer::AcceptQueryTopCard() {
        return new Message(14,"Query Top Card");
    }

    //private
	void Dealer::doAcceptDrawStockPile(Player * pP_Requester) {

        ostream& simlog = simOutMgr.getStream();

        int time = theEventMgr.clock();

        if (!pSP_StockPile->hasTwo()) {
            //Game is a draw

    		// Construct new message
            //TODO / TEST: Okay to have two pointers to same message in two different events?
            Message *returnhandMsg = pP_OtherPlayer->AcceptReturnHand();
    
    		// Construct new Event
    		Event e1( time  , this , (Player*)this , returnhandMsg );
            Event e2( time  , this , pP_OtherPlayer , returnhandMsg );
    
    		// Post Events
    		theEventMgr.postEvent(e1);
            theEventMgr.postEvent(e2);

            simlog << NameOf() << ": Stock Pile too low, game is a draw" << endl << endl;

        } else {

            CardMsg *drawnCardMsg = pP_Requester->AcceptDrawnCard( pSP_StockPile->Draw() );

            // Construct new Event
            Event e( time  , this , pP_Requester , drawnCardMsg );

            // Post Event
            theEventMgr.postEvent(e);

        }
        
    }

	void Dealer::doAcceptDrawDiscardPile(Player * pP_Requester) {

        int time = theEventMgr.clock();

        CardMsg *drawnCardMsg = pP_Requester->AcceptDrawnCard( DP_Discard.Draw() );

        // Construct new Event
        Event e( time  , this , pP_Requester , drawnCardMsg );

        // Post Event
        theEventMgr.postEvent(e);
    }

	void Dealer::doAcceptSorted() {

        int time = theEventMgr.clock();

        if ( State == 1 ) {
            State = 2; //Game begun, playing

            Message *firstTurnMsg = pP_OtherPlayer->AcceptYourTurn();
    
    		// Construct new Event
    		Event e( time  , this , pP_OtherPlayer , firstTurnMsg );
    
    		// Post Event
    		theEventMgr.postEvent(e);


        } else if ( State == 0 ) {
            State = 1; //Waiting for second sort
        } else {
            //TODO: AppError
        }

    }

	void Dealer::doAcceptReceiveDiscard(Card * inputCard) {

        DP_Discard.Add(*inputCard);

    }

	void Dealer::doAcceptReceiveReturnedHand(Card * inputCard) {
        
        pSP_StockPile->Add(*inputCard);        

    }

	void Dealer::doAcceptHandEmpty() {

        if ( State == 3 ) {
            State = 0; //Initialized

            while (!DP_Discard.isEmpty()) {
                pSP_StockPile->Add(*(DP_Discard.Draw()));
            }

            //TODO: signal GinRummy that game is over
            //GameControl->

        } else if ( State == 2 ) {
            State = 3; //Waiting for second hand empty
        } else {
            //TODO: AppError
        }
    }

	void Dealer::doAcceptShuffle() {

        int time = theEventMgr.clock();
		
		// Construct new message
        Message *shuffleCompleteMsg = AcceptShuffleComplete();

		// Construct new Event
		Event e( time + SpeedSettings[SpeedSettingIndexDealer::Speed_Shuffle] , this , this , shuffleCompleteMsg );

		// Post Event
		theEventMgr.postEvent(e);

    }

	void Dealer::doAcceptShuffleComplete() {

        int time = theEventMgr.clock();

        pSP_StockPile->Shuffle();

        //Deal 10 cards to each player
        for ( int i = 0; i < 10; i++ ) {

            // Construct new message
            CardMsg *dealtCardMsg1 = pP_OtherPlayer->AcceptDealtCard( pSP_StockPile->Draw() );
            CardMsg *dealtCardMsg2 = pP_OtherPlayer->AcceptDealtCard( pSP_StockPile->Draw() );
    
            // Construct new Event
            Event e1( time  , this , pP_OtherPlayer , dealtCardMsg1 );
            Event e2( time  , this , (Player*)this , dealtCardMsg2);
    
            // Post Events
            theEventMgr.postEvent(e1);
            theEventMgr.postEvent(e2);

        }

        // Construct new message
        Message *dealCompleteMsg = pP_OtherPlayer->AcceptDealComplete();

		// Construct new Event
        Event e1( time + SpeedSettings[SpeedSettingIndexDealer::Speed_Deal] , this , pP_OtherPlayer , dealCompleteMsg );
        Event e2( time + SpeedSettings[SpeedSettingIndexDealer::Speed_Deal] , this , (Player*)this , dealCompleteMsg );

        // Post Events
        theEventMgr.postEvent(e1);
        theEventMgr.postEvent(e2);


    }

	void Dealer::doAcceptQueryTopCard(Player * pP_Requester) {

        int time = theEventMgr.clock();

        CardMsg *drawnCardMsg = pP_Requester->AcceptTopCard( DP_Discard.getTopCard() );

        // Construct new Event
        Event e( time  , this , pP_Requester , drawnCardMsg );

        // Post Event
        theEventMgr.postEvent(e);
    }

}

