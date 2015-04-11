#include <iostream>
#include <string>
#include <map>
#include <vector>
#include "car.h"
using namespace std;

car::car()
{


}
car::car(string make,string exterior,string interior,string year)
{
_make=make;
_exterior=exterior;
_interior=interior;
_year=year;
}

string car::displayString()
{
	return "apple";
}

void car::dump(std::ostream& os) const
{
os<<_make<<" "<<_exterior<<" "<<_interior<<" "<<_year;
os<<endl;
os<<_MRSP<<" "<<_value<<endl<<_navigation<<" "<<_rearCamera<<" "<<_feature<<endl;
}