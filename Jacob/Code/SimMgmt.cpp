#include "SimMgmt.h"
using namespace SimMgmt;

namespace SimMgmt
{
    EventMgr  theEventMgr;
    InMgr  simInMgr ("Enter the name of the simulation input file: ");
	OutMgr simOutMgr("Enter the name of the simulation log file: ");

	//////////////////////////////////////////////////////////////////////// Message 
	Message::Message(int Handler, string Description)
	{
		handler     = Handler;
		description = Description;
	}

	void  Message::Insert()
	{ 
		ostream& fout = simOutMgr.getStream();

		simOutMgr.pushMargin();
		fout << "Message{ ";
		Put();
		simOutMgr.advToMargin();
		fout << "}Message ";
		simOutMgr.popMargin();
	}
	
    void Message::Put()
	{
		ostream& fout = simOutMgr.getStream();

		simOutMgr.pushMargin();
		fout << " Handler: " << handler;
		simOutMgr.advToMargin();
		fout << " Description: " << description << ' ';
		simOutMgr.popMargin();
	}
    
	ostream& operator<<(ostream &fout, Message &anyMsg) 
	{
		anyMsg.Insert(); 
		return fout;
	}


	////////////////////////////////////////////////////////////////////////  Agent

	Agent::Agent()
	{
	}

	
	Agent::~Agent()
	{
	}


  
		void   Agent::Extract() throw(TokenError)
		{
			string token;
			ifstream& fin = simInMgr.getStream();


			// Parse opening token "Agent{"
			fin >> token;
			if ( token != "Agent{" ) 
			   throw TokenError(string("Unrecognized open token," + token + ", 'Agent{' excpected!"),
                                string("Agent::Extract()"));
			Get();

			// Parse closing token "}Agent"
			fin >> token;
			if ( token != "}Agent" ) 
			   throw TokenError(string("Unrecognized close token," + token + ", '}Agent' expected!"),
                                string("Agent::Extract()")); 
		}
		
		void    Agent::Insert()
		{
			ostream& fout = simOutMgr.getStream();

		    simOutMgr.pushMargin();
			fout << "Agent{ ";
			Put();
		    simOutMgr.advToMargin();
			fout << "}Agent ";
			simOutMgr.popMargin();

		}
		
		
		void Agent::Get() throw(TokenError)
		{
			string token;
			ifstream& fin = simInMgr.getStream();


			fin >> token;
			if ( token != "name:" ) 
			   throw TokenError(string("Unrecognizable data token," + token + ",'name:' excpected!"),
                                string("Agent::Get()"));
			fin >> name;
		} 

        void Agent::Put()
		{
			ostream& fout = simOutMgr.getStream();

			simOutMgr.pushMargin();
			fout << " name: " << name;
			simOutMgr.popMargin();
		}
		
		ostream& operator<<(ostream &fout, Agent &anyAgent)
		{
			anyAgent.Insert(); 
			return fout;
		}
        	

        ifstream& operator>>(ifstream &fin, Agent &anyAgent) throw (TokenError)
		{
			anyAgent.Extract();
		    return fin;
		}

///////////////////////////////////////////////////////////////////////////// Event

	Event::Event( int Time, Agent *Sendr, Agent *Recvr, Message *Msg )
	{
		simtime = Time;
		sendr = Sendr;
		recvr = Recvr;
		msg = Msg;
	}
	
	bool Event::operator> (Event e2)
	{
		return ( (*this).getTime() > e2.getTime() );
	}

	bool Event::operator<=(Event e2)
	{
		return ( (*this).getTime() <= e2.getTime() );
	}

	bool Event::operator< (Event e2)
	{
		return ( (*this).getTime() < e2.getTime() );
	}

	ostream& operator<<( ostream &fout, Event e )
	{
		
		simOutMgr.pushMargin();
		fout << "TIME: "   << e.getTime() << " ";
		fout << "SENDER: " << e.getSendr()->NameOf() << " RECVR: " << e.getRecvr()->NameOf() << "  ";
		fout << (*e.getMsg());
		simOutMgr.popMargin();
		return fout; 
	}


////////////////////////////////////////////////////////////////////////////// EventMgr

	EventMgr::EventMgr()
	{
		currRecvr = currSendr = NULL;
		currTime = 0;
	}

	void	EventMgr::postEvent(Event E)
	{

		int n = eventQ.size();
		
		if ( n == 0 ) {
			eventQ.push_front(E);
			return;
		}else{
			list<Event>::iterator i = eventQ.begin();
			list<Event>::iterator stop = eventQ.end();

			for (; i != stop ; i++ )
				if ( E <*i ){ 
					eventQ.insert(i,E);
					return;
				}//if
			eventQ.push_back(E);
		}//else
	}//postEvent


	Event	EventMgr::getNextEvent()
	{
		Event e = eventQ.front();
		eventQ.pop_front();
		currSendr = e.getSendr();
		currRecvr = e.getRecvr();
		currTime  = e.getTime();
		return e;
	}

	void EventMgr::Insert()
	{
		list<Event>::iterator it;
		ostream& fout = simOutMgr.getStream();

		simOutMgr.pushMargin();
		for ( it = eventQ.begin(); it != eventQ.end(); it++ ){
			fout << *it;
			simOutMgr.advToMargin();
		}//for

		simOutMgr.popMargin();
	}
	
	ostream& operator<<(ostream &fout, EventMgr &Mgr)
	{

        Mgr.Insert();
		return fout;
	}


}//SimMgmt

