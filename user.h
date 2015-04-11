
#ifndef USER_H
#define USER_H
#include <iostream>
#include <string>
#include <map>
#include <vector>

using namespace std;

class user{
public:
	user();
	user(string name,string date,string cell,string other);	
	vector<string> keys();
	std::string displayString() const;
	void dump(std::ostream& os) const;
	string _date,_cell,_other,_email,_address,_Referral,_Broker,_Office,_SSN,_MonthlyIncome,_DOB,_Ethnicity,_Gender,_Occupation;
private:
	
	vector<string> _name;
	//vector<car> callHistory;

};

#endif