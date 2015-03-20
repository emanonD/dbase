#include <iostream>
#include <string>
#include <map>
#include "user.h"
#include "car.h"
//#include "dbase.h"

using namespace std;

string decrypt(string tode);
string encrypt(string toen);

int main(){
	user newUser("ximing","jiang","213-263-1341","000","3131 mcclintock","03/19/1996");
	cout<<newUser.displayString();
	return 0;
}