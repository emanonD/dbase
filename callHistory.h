

#include <iostream>
#include <string>
#include "car.h"
using namespace std;

class callHistory{
public:
callHistory();
callHistory(string date,car newCar,string method,string comment);
string displayString();
void dump(std::ostream& os) const;
car _car;
string _date,_method;
vector<string> _comment;
private:	
	
};


