#include <iostream>
#include <string>
#include <map>
#include <vector>

using namespace std;

class user{
public:
	user();
	user(string fname,string lname,string cel,string sn,string addre,string birth);

	string getForName();
	string getLastName();
	string getCell();
	string getSsn();
	string getAddress();
	string getDob();
	vector<string> keys();
	void setForName(string fnam);
	void setLastName(string lnam);
	void setCell(string cel);	
	void setSsn(string ss);	
	void setAddress(string addr);
	void setDob(string db);
	std::string displayString() const;
	void dump(std::ostream& os) const;
	
private:
	string forname,lastname,cell,ssn,address,dob,email;
	bool camera;
	int budget;
	//vector<car> callHistory;

};