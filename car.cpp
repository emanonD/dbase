#include <iostream>
#include <string>
#include <map>
#include <vector>
#include "car.h"
using namespace std;

car::car()
{
make="make";
model="model";
color="color";
year=0;
price=0;

}
car::car(string mak,string mode,string colo,int yea,double pric)
{
make=mak;
model=mode;
color=colo;
year=yea;
price=pric;
}

void car::setFeature(int featureNum,bool fea)
{
if((int)feature.size()>=featureNum)
	feature[featureNum]=fea;
else return;
}
void car::setMake(string mak)
{
	make=mak;
}
void car::setModel(string mode)
{
	model=mode;
}
void car::setColor(string colo)
{
	color=colo;
}
void car::setYear(int yea)
{
	year=yea;
}
void car::setPrice(double pric)
{
	price=pric;
}
string car::getMake()
{
	return make;
}
string car::getModel()
{
	return model;
}
string car::getColor()
{
return color;
}
int car::getYear()
{
	return year;
}
double car::getPrice()
{
	return price;
}

string displayString()
{
	return make+"  "+model+"  "+color;
}