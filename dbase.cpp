#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <cstdlib>
#include "dbase.h"

using namespace std;

dbase::dbase()
{

}
dbase::dbase(string fileloc)
{

}
void dbase::addUser(user newUser)
{
    char cch ;
    string userKey;
    for(int i=0; i<8; i++)
    {   cch = 'a' + rand()%26;
        userKey+=cch;
    }
    users[userKey]=newUser;
    vector<string> keys=newUser.keys();

    for (int i=0; i<(int)keys.size(); i++)
    {
        if (keybase.count(keys[i])==0)
        {
            vector<string> newVec;
            newVec.push_back(userKey);
            keybase[keys[i]]=newVec;
        }
        else {
            keybase[keys[i]].push_back(userKey);
        }
    }
}
vector<user> dbase::returnAll()
{
	vector<user> retu;
	for(map<string,user>::iterator it=users.begin();it!=users.end();++it)
	{
		user newUser=it->second;
		retu.push_back(newUser);
	}
	return retu;
}
vector<user> dbase::search(vector<string> searchKey)
{
vector<user> newVec;
if (keybase.count(searchKey[0])==0)
return newVec;
else for( int  i=0;i<(int)keybase[searchKey[0]].size();i++)
{
vector<string> tempVec=keybase[searchKey[0]];
newVec.push_back(users[tempVec[i]]);
}
if ((int)searchKey.size()==1)
	return newVec;
else for(int j=1;j<(int)searchKey.size();j++)
	{
		vector<user> secVec;
		if (keybase.count(searchKey[j])!=0)
		for( int i=0;i<(int)keybase[searchKey[j]].size();i++)	
		{
			vector<string> tempVec=keybase[searchKey[j]];
			secVec.push_back(users[tempVec[i]]);
		}
		//newVec=setIntersection(newVec,secVec);
	}

return newVec;

}
