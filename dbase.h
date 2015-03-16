#include <iostream>
#include <string>
#include <map>
#include "user.h"

using namespace std

class dbase{

public:
dbase();
dbase(string fileloc);
user search();
void dump(std::ostream& ofile);


private:
map<string,user> database;
map<string,vector<string>> keybase;


}