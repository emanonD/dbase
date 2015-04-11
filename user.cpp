#include <iostream>
#include <string>
#include <map>
#include <vector>
#include "user.h"
using namespace std;

user::user()
{
}
user::user(string name,string date,string cell,string other)
{	int lastloc=0;
	for(int i=0;i<(int)name.size();i++)
	{
		if (name[i]=='*')
		{
			_name.push_back(name.substr(lastloc,i-lastloc));		
			lastloc=i+1;
		}		
	}
	_name.push_back(name.substr(lastloc,name.size()-lastloc));
	_date=date;
	_cell=cell;
	_other=other;
	
}

	vector<string> user::keys()
	{
		vector<string> keychain;
		keychain.push_back(_cell);
		keychain.push_back(_SSN);
		keychain.push_back(_address);
		keychain.push_back(_DOB);
		return keychain;
	}
	
	std::string user::displayString() const
	{
		return "apple";//forname+"  "+lastname+"  "+cell+"  "+ssn+" "+address+"  "+dob;
	}
	void user::dump(std::ostream& os) const
	{
		for(int i=0;i<(int)_name.size()-1;i++)
			os<<_name[i]<<"*";
		os<<_name[_name.size()-1];
		os<<" ";
		os<<_date<<" "<<_cell<<endl<<_other<<" ";
		os<<_email<<endl<<_address<<endl<<_Referral<<" "<<_Broker<<" ";
		os<<_Office<<endl<<_SSN<<" "<<_MonthlyIncome<<" "<<_DOB<<endl;
		os<<_Ethnicity<<" "<<_Gender<<" "<<_Occupation<<endl;
	}
	