#include <iostream>
#include <string>
#include <map>
#include <vector>
using namespace std;

class car{
public:
car();
car(string mak,string mode,string colo,int yea,double pric);
void setFeature(int featureNum,bool fea);
void setMake(string mak);
void setModel(string mode);
void setColor(string colo);
void setYear(int yea);
void setPrice(double pric);
string getMake();
string getModel();
string getColor();
int getYear();
double getPrice();
string displayString();
private:
	string make,model,color;
	vector<bool> feature;
	int year;
	double price;
};