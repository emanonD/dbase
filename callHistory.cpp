#include <iostream>
#include <string>
#include <map>
#include <vector>
#include "callHistory.h"
using namespace std;

callHistory::callHistory()
{


}
callHistory::callHistory(string date,car newCar,string method,string comment)
{
_car=newCar;
_date=date;
_method=method;
 int lastloc=0;
	for(int i=0;i<(int)comment.size();i++)
	{
		if (comment[i]=='*')
		{
			_comment.push_back(comment.substr(lastloc,i-lastloc));		
			
			lastloc=i+1;

		}		
	}
	_comment.push_back(comment.substr(lastloc,comment.size()-lastloc));
}

string callHistory::displayString()
{
	string callHis;
	callHis=_method+" "+_car.displayString()+"\n";
	for(int i=0;i<(int)_comment.size()-1;i++)
			callHis+=_comment[i]+" ";
	return callHis;
}

void callHistory::dump(std::ostream& os) 
{
os<<_date<<" "<<_method<<" "<<endl;
_car.check();
_car.dump(os);
for(int i=0;i<(int)_comment.size()-1;i++)
		os<<_comment[i]<<"*";
		os<<_comment[_comment.size()-1];
		os<<endl;
}
