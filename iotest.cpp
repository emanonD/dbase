#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include "user.h"
#include "car.h"
#include "dbase.h"
using namespace std;
int main() {
	dbase newDb;
	newDb.parse("output.out");
	ofstream ofile("output2.out");
	newDb.dump(ofile);
	
	ofile.close();
	return 0;

}