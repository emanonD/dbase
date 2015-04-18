#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <algorithm>
#include "user.h"
#include "car.h"
#include "callHistory.h"
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
	void user::generateCallHistory(string date,car newCar,string method,string comment)
	{
		callHistory newCallHistory(date,newCar,method,comment);
		_callHistory.push_back(newCallHistory);
		_callHistoryNum=_callHistory.size();
	}
	std::string user::displayString() const
	{	string toDisplay;
		toDisplay+=_date+" ";
			for(int i=0;i<(int)_name.size()-1;i++)
			toDisplay+=_name[i]+" ";

		toDisplay+=_name[_name.size()-1];
			toDisplay+=' ';
			toDisplay+=_cell+' ';
			
			toDisplay+=_email+' ';

		return toDisplay;//forname+"  "+lastname+"  "+cell+"  "+ssn+" "+address+"  "+dob;
	}
	void user::check()
	{
		cout<<"checking for empty";
		if (_name[0]=="") _name[0]=("name");
		if (_address[0]=="")  _address[0]=("address");
		//if (_date=="") _date="date";
		cout<<_cell;
		if (_cell=="") _cell="Cell";
		if (_other=="") _other="Cell2";
		if (_email=="") _email="Email";
		if (_Referral=="") _Referral="Referral";
		if (_Broker=="") _Broker="Broker";
		if (_SSN=="") _SSN="SSN";
		if (_Office=="") _Office="Office";
		if (_MonthlyIncome=="") _MonthlyIncome="MonthlyIncome";
		if (_DOB=="") _DOB="DoB";
		if (_Ethnicity=="") _Ethnicity="Ethnicity";
		if (_Gender=="") _Gender="Gender";
		if (_Occupation=="") _Occupation="Occupation";
		if (haveCar)
			_car.check();
		for (int i=0;i<(int)_callHistory.size();i++)
			if (_callHistory[i]._comment[0]=="")
				_callHistory[i]._comment[0]="Comment";
		//,_cell,_other,_email,_Referral,_Broker,_Office,_SSN,_MonthlyIncome,_DOB,_Ethnicity,_Gender,_Occupation;
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
		os<<" "<<_Referral<<" "<<_Broker<<" ";
		os<<_Office<<" "<<_SSN<<" "<<_MonthlyIncome<<" "<<_DOB<<" ";
		os<<_Ethnicity<<" "<<_Gender<<" "<<_Occupation<<" "<<_callBackDate<<" ";
	}
	