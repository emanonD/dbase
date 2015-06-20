#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <algorithm>
#include "user.h"
//#include "car.h"
//#include "callHistory.h"
using namespace std;

user::user()
{
	
}
user::user(string name,string date,string cell)
{	
	int lastloc=0;
	_name.clear();	
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
	_date=date;
	_cell=cell;
	_new=0;
	_lease=0;
}

	vector<string> user::keys()
	{
		vector<string> keychain;
		for(int i=0;i<(int)_name.size();i++)
		keychain.push_back(_name[i]);
		keychain.push_back(_cell);
		for (int i=0;i<(int)keychain.size();i++)
			transform(keychain[i].begin(), keychain[i].end(), keychain[i].begin(), ::tolower);
		return keychain;
	}
	/*void user::generateCallHistory(string date,car newCar,string method,string comment)
	{
		callHistory newCallHistory(date,newCar,method,comment);
		_callHistory.push_back(newCallHistory);
		_callHistoryNum=_callHistory.size();
	}*/
	std::string user::displayString() const
	{	string toDisplay;
		toDisplay+=_cell+" ";
			for(int i=0;i<(int)_name.size()-1;i++)
			toDisplay+=_name[i]+" ";

		toDisplay+=_name[_name.size()-1];
			toDisplay+=' ';
			toDisplay+=_date+' ';
		
			toDisplay+=_make+' ';
			//toDisplay+=(int)_callHistory.size();

		return toDisplay;//forname+"  "+lastname+"  "+cell+"  "+ssn+" "+address+"  "+dob;
	}
	void user::check()
	{
		cout<<"checking for empty";
		if (_name[0]=="") _name[0]=("name");
		
		if (_cell=="") _cell="Cell";
		
		if (_email=="") _email="Email";
		if (_make=="") _make="make";
		if (_model=="") _model="model";
		if (_exterior=="") _exterior="exterior";
		if (_interior=="") _interior="interior";
		if (_year=="") _year="year";
		if (_msrp=="") _msrp="msrp";
		if (_options=="") _options="options";
		if (_price=="") _price="price";
			
	}
	void user::dump(std::ostream& os) const
	{
		for(int i=0;i<(int)_name.size()-1;i++)
			os<<_name[i]<<"*";
		os<<_name[_name.size()-1];
		os<<" ";
		os<<_date<<" "<<_cell<<" ";
		os<<_email<<" "<<_make<<" "<<_model<<endl;
		os<<_new<<" "<<_lease<<" ";
		if (_new==0)
		{
			os<<_exterior<<" "<<_interior<<" "<<_year<<" "<<_msrp<<" "<<_options<<" "<<_price<<endl;
		}
		else if(_lease==1)
		{
			os<<_down<<" "<<_term<<" "<<_miles;
		}
		else if(_lease==0)
		{
			os<<_dotd;
		}
		os<<_callBackDate;
	}
