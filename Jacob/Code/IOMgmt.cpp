#include <iomanip>
#include <cstdlib>
#include <cctype>
using namespace std;

#include "IOMgmt.h"
using namespace IOMgmt;


namespace IOMgmt {
    const string IOError::IOERROR = "IOError{}";
    const string TokenError::TOKENERROR = "TokenError{}";
    const string Tokenizer::DELIMS =       " \t\n";      //Blank,Tab,Newline
    const string StringTokenizer::DELIMS = " \t";        //Blank,Tab

    IOError::IOError()
	{
     //default constructor for AppError is automatically called
    }//default constructor
     
    IOError::IOError(string Msg)
	{
		appendMsg(Msg);
        appendOrg(IOERROR);
    }//constructor
            
    IOError::IOError(string Msg, string Org) : AppError(Msg,IOERROR)
	{
	    appendOrg(Org);
    }//constructor

	TokenError::TokenError()
	{
     //default constructor for AppError is automatically called
    }//default constructor
     
    TokenError::TokenError(string Msg)
	{
		appendMsg(Msg);
        appendOrg(TOKENERROR);
    }//constructor
            
    TokenError::TokenError(string Msg, string Org) : AppError(Msg,TOKENERROR)
	{
	    appendOrg(Org);
    }//constructor

	///////////////////////////////////////////////////////// Utility Functions

	bool  IsIn(char x, string s){
      for(int i=0; i < s.length(); i++){
         if( x == s[i] ) return true;
      }//for
      return false;
	}//IsIn
	
	bool  Allwsp(string s){
      for(int i=0; i < s.length(); i++){
         if( ' '  != s[i] &&
             '\t' != s[i] &&
             '\n' != s[i]  ) return false;
      }//for
      return true;
	}//Allwsp

	bool  IsWSP(char ch){
      
         if( ' '  != ch &&
             '\t' != ch &&
             '\n' != ch  ) return false;

         return true;
	}//IsWSP


	///////////////////////////////////////////////////////// InMgr

    //Default Constructor
	InMgr::InMgr ( string Prompt ) throw( IOError )
	{   
		cout <<  Prompt;
		for(;;){
		     cin  >>  fileName;
			 if( fileName == "NONE" ) 
			 { 
				 fileName = ""; 
				 break; 
			 }
			 cout << fileName << endl;
			 fin.open(fileName.c_str(), ios::in );
			 if( !fin.fail() )
			 { 
				finpos = fin.tellg();
				break;
			 }
			 cout << endl << "Input file could not be opened!" << endl;
			 cout << "Please re-enter Default Input name, or NONE: ";
			 fin.clear();
		}//for
	}

	//get the file name from the input mgr
	string InMgr::getFileName() const
	{   
        return fileName;
	}//end

	void   InMgr::close() throw( IOError )
	{      
		   if( fileName == "" ) throw IOError("InMgr object is not enabled!","Inmgr::close()");
           fin.close();
	}//close

	void      InMgr::setFilePos()  throw( IOError )
	{
		if( fileName == "" ) throw IOError("InMgr object is not enabled!","Inmgr::close()");
		finpos = fin.tellg();
	}

	void      InMgr::resetFilePos() throw( IOError )
	{
		if( fileName == "" ) throw IOError("InMgr object is not enabled!","Inmgr::close()");
		fin.seekg( finpos );
	}

    ifstream& InMgr::getStream()  throw( IOError )
	{
		if( fileName == "" ) throw IOError("InMgr object is not enabled!","Inmgr::close()");
		return fin;
	}

	///////////////////////////////////////////////////////// OutMgr

	OutMgr::OutMgr ( string Prompt ) throw( IOError )
	{   
		for(;;){
		     cout <<  Prompt;
		     cin  >>  fileName;
			 if( fileName.length() > 0 ) break;
			 cout << endl << "Null file name! Please re-enter." << endl;
		}//for
        
		fout.open(fileName.c_str(), ios::out );
		if( fout.fail() )
			throw IOError("Output file could not be created!",
			              "OutMgr::OutMgr()");
		lineorg = curpos = fout.tellp();
	}

	//get the file name from the input mgr
	string OutMgr::getFileName() const
	{   
        return fileName;
	}//end


    ostream& OutMgr::getStream() throw( IOError )
	{
		if( fileName == "" ) throw IOError("OutMgr instance is not enabled! ", "OutMgr::getStream()");
		return fout;
	}

    void   OutMgr::close() throw( IOError )
	{
		if( fileName == "" ) throw IOError("OutMgr instance is not enabled! ", "OutMgr::close()");
        fout.close();
	}//close



	void  OutMgr::pushMargin() throw( IOError )
	{
		if( fileName == "" ) throw IOError("OutMgr instance is not enabled! ", 
			                               "OutMgr::pushMargin()");
		if( ++idx >= MARGINSIZE ) throw IOError(string("Margin Stack Overflow!"),
				                                string("OutMgr::pushMargin()"));
		curpos = fout.tellp();
		margin[idx] = curpos - lineorg;
	}//pushMargin

	void    OutMgr::popMargin() throw( IOError )
	{
		if( fileName == "" ) throw IOError("OutMgr instance is not enabled! ", 
			                               "OutMgr::popMargin()");
		if( idx < 0 ) throw IOError(string("Margin Stack Underflow!"),
				                    string("OutMgr::popMargin()"));
        curpos = lineorg + margin[idx--];
	}//popMargin

	
	void    OutMgr::newLine()  throw( IOError )
	{
			if( fileName == "" ) throw IOError("OutMgr instance is not enabled! ", 
			                               "OutMgr::newLine()");
		    fout << endl;
			curpos = lineorg = fout.tellp();
	}//newLine

	void    OutMgr::deltaMargin(int delta) throw( IOError )
	{
			if( fileName == "" ) throw IOError("OutMgr instance is not enabled! ", 
			                                   "OutMgr::deltaMargin()");
			curpos = fout.tellp();
		    long diff = curpos - lineorg + delta;
		    if( delta == 0 ) return;
			if( delta < 0  ) 
			{
				   newLine();
				   if( diff < 0 ) throw IOError(string("Illegal operation on output file!"),
				                                string("OutMgr::deltaMargin(fout)"));
				   for(;diff  > 0; diff-- ) fout << ' ';
			}else  for(;delta > 0; delta--) fout << ' ';
			curpos = fout.tellp();
	}//deltaMargin


	void    OutMgr::toMargin()  throw( IOError )
	{
			if( fileName == "" ) throw IOError("OutMgr instance is not enabled! ", 
			                               "OutMgr::toMargin()");
		    long CUR;
			CUR = fout.tellp();
			curpos = lineorg + margin[idx];
			if( curpos >= CUR )
				 for(; CUR < curpos; CUR++) fout << ' ';
			else fout.seekp(curpos);
	}//newLine


	void    OutMgr::pushToMargin(int delta) throw( IOError )
	{
		if( fileName == "" ) throw IOError("OutMgr instance is not enabled! ", 
			                               "OutMgr::pushToMargin()");
		pushMargin();
		deltaMargin(delta);
	}//pushToMargin


	void    OutMgr::popToMargin() throw( IOError )
	{
		if( fileName == "" ) throw IOError("OutMgr instance is not enabled! ", 
			                               "OutMgr::popToMargin()");
        popMargin();
		fout.seekp(curpos);
	}//popToMargin

	void	OutMgr::advToMargin() throw( IOError )
	{
		if( fileName == "" ) throw IOError("OutMgr instance is not enabled! ", 
			                               "OutMgr::advToMargin()");
		newLine();
		toMargin();
	}
	
	void    OutMgr::pushAdvMargin() throw( IOError )
	{
		if( fileName == "" ) throw IOError("OutMgr instance is not enabled! ", 
			                               "OutMgr::pushAdvMargin()");
		pushMargin();
		advToMargin();
	}
	
	void    OutMgr::popAdvMargin()  throw( IOError )
	{
		if( fileName == "" ) throw IOError("OutMgr instance is not enabled! ", 
			                               "OutMgr::popAdvMargin()");
		popMargin();
		advToMargin();
	}

	void    OutMgr::clearMargins()
	{
		    idx = 0;
			for(int i=0; i < MARGINSIZE; i++) margin[i] = 0;
	}//clearMargins


	/////////////////////////////////////////////////////////// Tokenizer

	//pass the tokenizer a inputmgr derived class
	Tokenizer::Tokenizer(string Prompt) throw(IOError) 
		       :FinMgr(Prompt),fin(FinMgr.getStream())
	{
		delims  = DELIMS;
		discard = "";

	}//Constructor

	bool Tokenizer::More()
	{ 
		//"false" if EOF and putback buffer is empty
		return !fin.eof() || backbuff.length();
	}//More 

	//return the next character if there is on in the backbuffer use it first
	char Tokenizer::NextChar()
	{
		char sym = 0;
   
		if( backbuff.length() )
		{
			sym = backbuff[0];
			backbuff = backbuff.substr(1,backbuff.length()-1);
			return sym;
		}

		if( fin.good() && !sym ) fin.get(sym);
		return sym;

	}//NextChar

	bool Tokenizer::IsDelim(char x)
	{
		for(int i=0; i < delims.length(); i++)
		{
			if( x == delims[i] ) return true;
		}//for
	
		return false;
	}//IsDelim

	string Tokenizer::Scan() 
	{//delivers next token       
		string token = "";
		char  sym;
		
		if( fin.eof() ) 
			return token;
       
		discard = "";      
		sym     = NextChar();
       
		//read delimiters until first non delimiter
		while( !fin.eof() && IsDelim(sym) ) 
		{
			discard = discard + sym;
			sym     = NextChar();
		}//while 
       
		if( fin.eof() ) 
			return token;

		token = token + sym;
		sym = NextChar();
		//now read in all non delimiters until the first delimiter
		while( !fin.eof() && !IsDelim(sym) )
		{
			token = token + sym;
            sym = NextChar();
		}//while
		
		//put the delimiter back since its part of the next token sequence
		if(!fin.eof()) fin.putback(sym);
       
		return token;
	}//Scan

	void  Tokenizer::SetDelims(string symbols) throw(TokenError)
	{
		if(!symbols.length())
			throw IOError(string("Null delimiter string"),
			              string("Tokenizer.SetDelims"));
		
		delims = symbols;
	}//SetDelims

	string Tokenizer::GetDelims()
	{
		return delims;
	}//GetDelims

	string Tokenizer::GetDiscard()
	{
		return discard;
	}//GetDiscard

	void   Tokenizer::Reset()
	{
		delims = DELIMS;
	}//Reset

	void   Tokenizer::Putback(string token)
	{ //"undo" token
			backbuff = token + backbuff;
	}//Putback  

//***********************************************************************************
//Implementation of StringTokenizer Class
//***********************************************************************************

	
    StringTokenizer::StringTokenizer()
		             :strbuff(""), delims(DELIMS),backbuff(""), discard("")
	{
	}
    
           
    StringTokenizer::StringTokenizer(string astr)
		             :strbuff(astr),delims(DELIMS),backbuff(""),discard("")
	{
	}

	void StringTokenizer::CatBuff(string astr)
	{
            strbuff = strbuff + astr;
	}//CatBuff
	
	bool StringTokenizer::More()
	{ 
		//"false" if the string to be tokeized is empty and putback buffer is empty
		return !strbuff.empty() || backbuff.length();

	}//More
	
	char StringTokenizer::NextChar()
	{
             string token;
             char ch = 0;
          
             if(backbuff.length()){
                ch       = backbuff[0];
                backbuff = backbuff.erase(0,1);
				cout << ch << endl;
                return ch;
             }

             if(strbuff.empty()) return ch;
             ch = strbuff[0];
             strbuff = strbuff.erase(0,1);
			 //cout << ch << endl;
             return ch;
	}//NextChar
	
	bool StringTokenizer::IsDelim(char ch)
	{
		  if(!ch ) return true;
          for(int i = 0; i < delims.length(); i++){
            if(ch == delims[i]) return true;
          }
          return false;
	}//IsDelim
	
	string StringTokenizer::Scan() 
	{//delivers next token       
		string token = "";
		char  ch(' ');
		discard = "";      
		
		if( strbuff.empty() && backbuff.empty() ) return token;
       
		ch  = NextChar();
       
		//read in delimiters until first non delimiter
		while( (!strbuff.empty() || !backbuff.empty()) && IsDelim(ch) ) 
		{
			discard = discard + ch;
			ch     = NextChar();
		}//while 
       

		token = token + ch;
		ch = NextChar();

		//now read in all non delimiters until the first delimiter
		while( (!strbuff.empty() || !backbuff.empty()) && !IsDelim(ch) )
		{
			token = token + ch;
            ch = NextChar();
		}//while
		
		//put the delimiter back since its part of the next token sequence
		if(IsDelim(ch)) strbuff = ch + strbuff;
		else token += ch;
       
		//cout << "DISCARD:" << discard << "***" << endl;
		//cout << "TOKEN:" << token << "***" << endl;
		return token;
	}//Scan
	
	void  StringTokenizer::SetDelims(string newDelims) throw(TokenError)
	{
		if(!newDelims.length())
		   throw TokenError("Null delimiter string","StringTokenizer.SetDelims");
		
		delims = newDelims;
	}//SetDelims
	
	string StringTokenizer::GetDelims()
	{
		return delims;
	}//GetDelims
	
	string StringTokenizer::GetDiscard()
	{
		return discard;
	}//GetDiscard
	
	void   StringTokenizer::Reset()
	{
		delims = DELIMS;
	}//Reset
	
	void   StringTokenizer::Putback(string back)
	{ //"undo" token
	     strbuff = back + strbuff;
	}//Putback  

 

}//namespace


