#ifndef DBASE_H
#define DBASE_H
#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <algorithm>
#include "user.h"
//#include "car.h"

using namespace std;


class dbase{

public:
dbase();
dbase(string fileloc);
void addUser(user newUser);
//addCar(car newCar);
vector<user> search(vector<string>);
vector<user> returnAll();
//void dump(std::ostream& ofile);
void parse(string fileloc);
void dump(ostream& os);
vector<user> setInter(vector<user>& s1, vector<user>& s2);
private:
//map<string,car> cars;
map<string,user> users;
map<string,vector<string> > keybase;
string _fileloc;

};




#endif