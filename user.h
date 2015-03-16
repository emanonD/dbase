#include <iostream>
#include <string>
#include <map>
using namespace std

class user{
public:
	user();
	user(string name,string cell,string ssn,string address,string dob);

	string getName();
	string getCell();
	string getSsn();
	string getAddress();
	string getDob();
	void setName(string nam);
	void setCell(string cel);	
	void setSsn(string ss);	
	void setAddress(string addr);
	void setDob(string db);
	std::string displayString() const;
	void dump(std::ostream& os) const;

private:
	string name,cell,ssn,address,dob;

};