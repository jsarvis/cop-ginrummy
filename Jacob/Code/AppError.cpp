#include "AppError.h"

const string AppError::NOERROR = "";

AppError::AppError(){
     msg = origin = NOERROR;
}//default constructor

AppError::AppError(string Why, string Where){
     msg    = Why;
     origin = Where;
}// constructor

void AppError::appendMsg(string Msg){
     msg = msg + ":" + Msg;
}//appendMsg


void AppError::appendOrg(string Org){
     origin = origin + ":" + Org;
}//appendOrg