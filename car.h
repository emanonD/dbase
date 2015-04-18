#ifndef CAR_H
#define CAR_H

#include <iostream>
#include <string>
#include <map>
#include <vector>
using namespace std;

class car{
public:
car();
car(string make,string exterior,string interior,string year);
string displayString();
void dump(std::ostream& os) const;
void check();
string _make,_exterior,_interior,_year,_MRSP,_value,_navigation,_rearCamera,_feature;
private:	
	
};

#endif