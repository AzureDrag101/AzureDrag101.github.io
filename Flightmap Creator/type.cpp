#include <iostream>
#include <fstream>
#include <iomanip>
#include "type.h"
using namespace std;

//define struct flightRec
  bool flightRec::operator < (const flightRec & rhs) const{
    return(destination < rhs.destination);
  };
  //overloaded < operator for flightRec
  //this function compares the destinations between two flightRec

  bool flightRec::operator == (const flightRec & rhs) const{
    return((destination == rhs.destination) && (origin == rhs.origin));
  };
  //overloaded == operator for flightRec
  //this function compares the origins and destinations between two flightRec

  ostream& operator << (ostream & os, const flightRec & f){
    os << f.destination << setw(10) << f.flightNum << setw(7) << "$" << f.price;
    return os;
  }
  //overloaded output operator for flightRec struct
