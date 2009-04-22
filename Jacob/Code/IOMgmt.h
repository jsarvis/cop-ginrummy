#ifndef _IOMGMT
#define _IOMGMT

#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
using namespace std;

#include "AppError.h"
#define   MARGINSIZE   20

namespace IOMgmt {

	class IOError: public AppError 
	{
		public:
		  IOError();               //default constructor
		  IOError(string Msg);             //constructor
		  IOError(string Msg, string Org); //constructor
          //INHERITED: 
            //string getMsg();
            //string getOrigin();
            //void   appendMsg(string Msg);
            //void   appendOrg(string Org);
		
		private:
			static const string IOERROR;
	}; //IOError

	
	class TokenError: public AppError 
	{
		public:
		  TokenError();               //default constructor
		  TokenError(string Msg);             //constructor
		  TokenError(string Msg, string Org); //constructor
          //INHERITED: 
            //string getMsg();
            //string getOrigin();
            //void   appendMsg(string Msg);
            //void   appendOrg(string Org);
		
		private:
			static const string TOKENERROR;
	}; //TokenError

	bool  IsIn(char x, string s);	//Does (x) occur in (s)?
    bool  Allwsp(string s);			//Is (s) all whitespace?
	bool  IsWSP (char ch );			//Is (ch) whitespace?

	class  InMgr  
	{
		public:
		   InMgr( string Prompt )		throw( IOError );
		   string    getFileName() const;
		   ifstream& getStream()		throw( IOError );
		   void		 close()			throw( IOError );

		   void      setFilePos()		throw( IOError );
		   void      resetFilePos()		throw( IOError );

		private:
		   ifstream fin;
		   long     finpos;
		   string   fileName;
	};//InMgr


	class  OutMgr  
	{
		public:
		   OutMgr( string Prompt )			throw( IOError );
 		   string    getFileName() const;
		   ostream&  getStream() 			throw( IOError );
		   void		 close()				throw( IOError );

		   void    pushMargin()				throw( IOError ); //push cur
		   void    popMargin()				throw( IOError ); //pop cur
		   void    newLine()				throw( IOError );
		   void    deltaMargin(int delta)	throw( IOError );

		   void    toMargin()				throw( IOError );
		   void    pushToMargin(int delta)	throw( IOError );
		   void    popToMargin()			throw( IOError );
		   void    advToMargin()			throw( IOError );
		   void    pushAdvMargin()			throw( IOError );
		   void    popAdvMargin()			throw( IOError );

		   void    clearMargins();
	
		private:
		   string    fileName;
		   ofstream  fout;
		   long      lineorg;
		   long      curpos;
		   long      margin[MARGINSIZE];
		   int       idx;
	};//OutMgr

	class Tokenizer 
	{
		public:
		   Tokenizer( string Prompt) throw (IOError); //Constructor uses InMgr
		   bool   More();                    //"false" if EOF
		   string Scan();                    //delivers next token:
                                                     //!found => returns null string
                                                     // found => next token
		   void   SetDelims(string symbols) throw (TokenError);        
                                                     //sets new delimiters (not null)
		   string GetDelims();               //returns current delimiters
		   string GetDiscard();              //returns discarded delimiters
                                                     //before  token returned by Scan()
		   void   Reset();                   //Revert to DELIMS
		   void   Putback(string token);     //"undo" token
		
		private:
		   static  const string DELIMS;     //Blank,Tab,Newline
	       InMgr     FinMgr;
		   ifstream& fin;                     //encapsulated input stream
		   string    delims;                  //active delimiters
		   string    backbuff;                //pushback buffer
		   string    discard;                 //string discarded before next token
		   char      NextChar();              //returns next character
		   bool      IsDelim(char x);         //tests for a delimiter
	};//Tokenizer

	
	class StringTokenizer 
	{
		public:
		   StringTokenizer();
		   StringTokenizer(string astr);
		   bool   More();                    //"false" if no more tokens
		   string Scan();                    //delivers next token:
                                                     //!found => returns null string
                                                     // found => next token
		   void   SetDelims(string symbols)  throw (TokenError);        //sets new delimiters (not null)
		   string GetDelims();               //returns current delimiters
		   string GetDiscard();              //returns discarded delimiters
                                                     //before  token returned by Scan()
		   void   Reset();                   //Revert to DELIMS
		   void   Putback(string token);     //"undo" token
                   void   CatBuff(string astr );    //append to string buffere
		
		private:
		   string   strbuff;                  //encapsulated input string buffer
		   static   const string DELIMS;     //Blank,Tab
		   string   delims;                  //active delimiters
		   string   backbuff;                //pushback buffer
		   string   discard;                 //string discarded before next token
		   char     NextChar();              //returns next character
		   bool     IsDelim(char x);         //tests for a delimiter
	};//StringTokenizer


}//namespace

#endif