#ifndef DBASE_H
#define DBASE_H
#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <algorithm>
#include "user.h"
#include "car.h"

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
private:
map<string,car> cars;
map<string,user> users;
map<string,vector<string> > keybase;
string _fileloc;

};

/*vector<user> setIntersection(vector<user>& s1, vector<user>& s2)
{
  vector<user> result;
  bool contain=false;
  for(int i=0;i<(int)s1.size();i++)
  {
  	contain=false;
    for (int j=0;j<(int)s2.size();j++)
    	if (s1[i].getAddress().compare(s2[j].getAddress())==0)
    		contain=true;
    if(contain) result.push_back(s1[i]);
  }
  return result;
}
*/
#endif