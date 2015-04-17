#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <algorithm>
#include "user.h"
#include "car.h"
using namespace std;

user::user()
{

}
user::user(string name,string date,string cell,string other,string address)
{	int lastloc=0;
	_name.clear();
	_address.clear();
	//for(int i=0;i<(int)name.size();i++)
	
		if (name[0]==' ')
			name=name.substr(1);
	
	for(int i=0;i<(int)name.size();i++)
	{
		if (name[i]=='*')
		{
			_name.push_back(name.substr(lastloc,i-lastloc));		
			lastloc=i+1;
		}		
	}
	_name.push_back(name.substr(lastloc,name.size()-lastloc));
	 lastloc=0;
	for(int i=0;i<(int)address.size();i++)
	{
		if (address[i]=='*')
		{
			_address.push_back(address.substr(lastloc,i-lastloc));		
			
			lastloc=i+1;

		}		
	}
	_address.push_back(address.substr(lastloc,address.size()-lastloc));
	_date=date;
	_cell=cell;
	_other=other;
	haveCar=false;
	_callHistoryNum=0;
	
}

	vector<string> user::keys()
	{
		vector<string> keychain;
		for(int i=0;i<(int)_name.size();i++)
		keychain.push_back(_name[i]);
		for(int i=0;i<(int)_address.size();i++)
		keychain.push_back(_address[i]);
		keychain.push_back(_cell);
		keychain.push_back(_SSN);
		//keychain.push_back(_address);
		keychain.push_back(_DOB);
		for (int i=0;i<(int)keychain.size();i++)
			transform(keychain[i].begin(), keychain[i].end(), keychain[i].begin(), ::tolower);
		return keychain;
	}
	
	std::string user::displayString() const
	{	string toDisplay;
		toDisplay+=_date+" ";
		 for(int i=0;i<(int)_name.size();i++)
			toDisplay+=_name[i]+' ';
			toDisplay+=' ';
			toDisplay+=_cell+' ';
			
			toDisplay+=_email+' ';

		return toDisplay;//forname+"  "+lastname+"  "+cell+"  "+ssn+" "+address+"  "+dob;
	}
	void user::dump(std::ostream& os) const
	{
		for(int i=0;i<(int)_name.size()-1;i++)
			os<<_name[i]<<"*";
		os<<_name[_name.size()-1];
		os<<" ";
		os<<_date<<" "<<_cell<<" "<<_other<<" ";
		os<<_email<<" ";
		for(int i=0;i<(int)_address.size()-1;i++)
		os<<_address[i]<<"*";
		os<<_address[_address.size()-1];
		os<<" ";
		os<<endl<<_Referral<<" "<<_Broker<<" ";
		os<<_Office<<endl<<_SSN<<" "<<_MonthlyIncome<<" "<<_DOB<<" ";
		os<<_Ethnicity<<" "<<_Gender<<" "<<_Occupation<<" "<<_callBackDate<<" ";
	}
	