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
	string carString;
	if (_make=="Make") carString="No car recommened in this call";
	else carString=_make+" "+_exterior+" "+_interior+" "+_year+" "+_MRSP+" "+_value+" "+_navigation+" "+_rearCamera+" "+_feature;
	return carString;
}
void car::check()
{
	if (_make=="") _make="Make";
	if (_exterior=="") _exterior="Exterior";
	if (_interior=="") _interior="Interior";
	if (_year=="") _year="Year";
	if (_MRSP=="") _MRSP="MRSP";
	if (_value=="") _value="Value";
	if (_navigation=="") _navigation="Navigation";
	if (_rearCamera=="") _rearCamera="ReadCamera";
	if (_feature=="") _feature="Feature";

}
void car::dump(std::ostream& os) const
{
os<<_make<<" "<<_exterior<<" "<<_interior<<" "<<_year;
os<<" ";
os<<_MRSP<<" "<<_value<<" "<<_navigation<<" "<<_rearCamera<<" "<<_feature<<endl;
}