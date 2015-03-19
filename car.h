#include <iostream>
#include <string>
#include <map>
#include <vector>
using namespace std
class car{
car();
car(string make,string model,string color,int year,double price);
void setFeature(vector<bool>);
void setMake(string make);
void setModel(string model);
void setColor(string color);
void setYear(int year);
void setPrice(double price);

private:
	string make,model,color;
	vector<bool> feature;
	int year;
	double price;
}