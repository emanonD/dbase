
#ifndef USER_H
#define USER_H
#include <iostream>
#include <string>
#include <map>
#include <vector>
//#include "car.h"
//#include "callHistory.h"
using namespace std;

class user{
public:
	user();
	user(string name,string date,string cell);	
	vector<string> keys();
	std::string displayString() const;
	void dump(std::ostream& os) const;
	//void generateCallHistory(string date,car newCar,string method,string comment);
	string _date,_cell,_email,_make,_model,_exterior,_interior,_year,_msrp,_options,_price,_orderNumber;
	int _down,_term,_miles,_dotd;
	bool _new;
	bool _lease;
	string _callBackDate;
	void check();
	//bool haveCar;
	string _key;
//	car _car;
	//int _callHistoryNum;
	vector<string> _name;
	//vector<string> _address;
	//vector<callHistory> _callHistory;
	//vector<string> _images;
	//vector<string> _files;
private:
	
	//vector<car> callHistory;

};

#endif