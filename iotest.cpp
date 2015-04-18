#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include "user.h"
//#include "car.h"
#include "dbase.h"
using namespace std;
int main() {
	dbase newDb;
	newDb.parse("aa.in");
	//vector<string> keys;
	//keys.push_back("Jiang");
	//keys.push_back("wei");
	user newUser;
	cout<<newUser._date;
	ofstream ofile("output1.out");
	vector<user> users=newDb.findDate("2015.04.25");
	cout<<users[0].displayString();
	newDb.dump(ofile);
	
	ofile.close();
	return 0;

}