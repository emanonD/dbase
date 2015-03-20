#include <iostream>
#include <string>
#include <map>
#include <vector>
#include "user.h"
using namespace std;

user::user()
{
forname="forname";
lastname="lastname";
cell="cell";
ssn="ssn";
address="address";
dob="dob";
}
user::user(string fname,string lname,string cel,string sn,string addre,string birth)
{
	forname=fname;
	lastname=lname;
	cell=cel;
	ssn=sn;
	address=addre;
	dob=birth;
}
string user::getForName()
{
return forname;
}
string user::getLastName()
{
	return lastname;
}
string user::getCell()
{
	return cell;
}
	string user::getSsn()
	{
		return ssn;
	}
	string user::getAddress()
	{
		return address;
	}
	string user::getDob()
	{
		return dob;
	}
	vector<string> user::keys()
	{
		vector<string> keychain;
		keychain.push_back(forname);
		keychain.push_back(lastname);
		keychain.push_back(cell);
		keychain.push_back(ssn);
		keychain.push_back(address);
		keychain.push_back(dob);
		return keychain;
	}
	void user::setForName(string fnam)
	{
		forname=fnam;
	}
	void user::setLastName(string lnam)
	{
		lastname=lnam;
	}
	void user::setCell(string cel)
	{
		cell=cel;
	}
	void user::setSsn(string ss)
	{
		ssn=ss;
	}
	void user::setAddress(string addr)
	{
		address=addr;
	}
	void user::setDob(string db)
	{
		dob=db;
	}
	std::string user::displayString() const
	{
		return forname+"  "+lastname+"  "+cell+"  "+ssn+" "+address+"  "+dob;
	}
	void user::dump(std::ostream& os) const
	{
		os<<forname+"  "+lastname+"  "+cell+"  "+ssn+"  "+address+"  "+dob;
	}
	