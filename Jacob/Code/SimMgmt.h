#ifndef _SIMMGMT
#define _SIMMGMT

#include <iostream>
#include <fstream>
#include <string>
#include <list>
using namespace std;


#include "IOMgmt.h"
using namespace IOMgmt;

namespace SimMgmt
{

class Message 
   {//concrete base class  
      public:
            Message(int Handler,string Description);       //constructor
			virtual ~Message() { }                         //destructor
			int     getHandler() const { return handler;}  //inspector
            friend  ostream& operator<<(ostream &fout, Message &anyMsg); //boundary:Insert
								
      protected:
		    virtual void Insert();
            virtual void Put   ();
            //needed to implement a "virtual friend" operator<<
	        //each public derived subclass must redefine this method
      private:
            int      handler;
	        string   description;
   };//Message

class Agent 
{//abstract class
   private:
	string name;			//instance attribute

  public:
	Agent();				//default constructor
	virtual ~Agent();		//destructor
	string	NameOf()  const {return name;   } //In-line inspector

	virtual	void Insert  (); //writes to default program output stream
	virtual	void Extract ()	throw (TokenError);  //reads from default program input stream
	friend 	ostream&  operator<<( ostream& fout, Agent& agnt);  //fout must be the default output stream
	friend	ifstream& operator>>( ifstream& fin, Agent& agnt) throw (TokenError); //fin must be the default input stream
	virtual void   Initialize(Message* players)=0;  //pure virtual method for simulation initialization
	virtual void   Dispatch  (Message* msg    )=0;  //pure virtual method for message dispatch to receiver agent
  protected:
	virtual void Put();
	virtual void Get()	throw (TokenError);
};


class Event 
   { //Single base class
      public:
		   Event(){}                               //default constructor
           Event( int    Time,  Agent*   Sendr,    //explicit constructor
			      Agent* Recvr, Message* Msg );
           virtual ~Event(){}                        //default destructor
           Agent*  getSendr() {return sendr;}        //in-line inspector
           Agent*  getRecvr() {return recvr;}        //in-line inspector
           int     getTime()  {return simtime;}      //in-line inspector
           Message* getMsg()  {return msg;   }       //in-line inspector
           bool       operator> (Event e2);          //predicate
           bool       operator<=(Event e2);          //predicate
           bool       operator< (Event e2);          //predicate
     friend ostream&  operator<<(ostream &fout,Event  e);  //boundary:Insert
      private:
           int      simtime;
           Agent*   sendr;
	       Agent*   recvr;
	       Message* msg;
   };//Event

   class EventMgr 
   {  //Single base class
      public:
           EventMgr();
           ~EventMgr(){}
		   bool	   moreEvents() {return !eventQ.empty();}
		   int	   clock()      {return currTime; }
           Agent*  getSendr()   {return currSendr;}
           Agent*  getRecvr()   {return currRecvr;}

           void	   postEvent(Event e);
           Event   getNextEvent();
		   void    Insert();
      friend ostream& operator<<(ostream &fout, EventMgr &Mgr);
      
      private:
           std::list<Event> eventQ;
	       int    currTime;	    //time of last Event removed from eventQ
	       Agent *currSendr;	//last Sendr agent
	       Agent *currRecvr;	//last Recvr agent
   };//EventMgr

   extern  EventMgr   theEventMgr;
   extern  InMgr      simInMgr;
   extern  OutMgr     simOutMgr;

   typedef Agent&	  AGENTREF;
   typedef Agent*	  AGENTPTR;

   typedef Message&	  MSGREF;
   typedef Message*	  MSGPTR;

   typedef EventMgr&  EMGRREF;
   typedef EventMgr*  EMGRPTR;

}//SimMgmt





#endif
