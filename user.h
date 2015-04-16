
#ifndef USER_H
#define USER_H
#include <iostream>
#include <string>
#include <map>
#include <vector>
#include "car.h"
#include "callHistory.h"
using namespace std;

class user{
public:
	user();
	user(string name,string date,string cell,string other,string address);	
	vector<string> keys();
	std::string displayString() const;
	void dump(std::ostream& os) const;
	string _date,_cell,_other,_email,_Referral,_Broker,_Office,_SSN,_MonthlyIncome,_DOB,_Ethnicity,_Gender,_Occupation;
	bool haveCar;
	string _key;
	car _car;
	int callHistoryNum;
	vector<string> _name;
	vector<string> _address;
	vector<callHistory> _callHistory;
private:
	
	//vector<car> callHistory;

};

#endif