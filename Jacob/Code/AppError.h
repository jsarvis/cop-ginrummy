#ifndef _APPERROR
#define _APPERROR
#include <string>
using namespace std;

class AppError {
      private:
          static const string NOERROR;
          string msg;
          string origin;
      public:
          AppError();
          AppError(string Why, string Where); 
          string getMsg()    const {return msg;}
          string getOrigin() const {return origin;}
          void appendMsg(string Msg);
          void appendOrg(string Org);
};
#endif