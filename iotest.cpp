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
	newDb.parse("output.out");
	vector<string> keys;
	keys.push_back("Jiang");
	keys.push_back("Ximing");
	ofstream ofile("output1.out");
	vector<user> users=newDb.search(keys);
	cout<<users[0].displayString();
	newDb.dump(ofile);
	
	ofile.close();
	return 0;

}