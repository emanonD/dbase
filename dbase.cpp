#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <fstream>
#include <cstdlib>
#include <algorithm>
#include "dbase.h"
#include "user.h"
#include "callHistory.h"

using namespace std;

dbase::dbase()
{

}
dbase::dbase(string fileloc)
{
_fileloc=fileloc;
}
vector<string> dbase::producer(string s)
{
    vector<string> toReturn;
    int lastloc=0; 
        if (s[0]==' ')
            s=s.substr(1);
    
    for(int i=0;i<(int)s.size();i++)
    {
        if (s[i]=='*')
        {
            toReturn.push_back(s.substr(lastloc,i-lastloc));        
            lastloc=i+1;
        }       
    }
    toReturn.push_back(s.substr(lastloc,s.size()-lastloc));
    return toReturn;
}
void dbase::addUser(user newUser)
{
    newUser.check();
    char cch ;
    string userKey;
    for(int i=0; i<8; i++)
    {   cch = 'a' + rand()%26;
        userKey+=cch;
    }
    newUser._key=userKey;
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
void dbase::replaceUser(user newUser)
{   
    string userKey=newUser._key;
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
    users[newUser._key]=newUser;
}
vector<user> dbase::setInter(vector<user>& s1, vector<user>& s2)
{
  vector<user> result;
  bool contain=false;
  for(int i=0;i<(int)s1.size();i++)
  {
    contain=false;
    for (int j=0;j<(int)s2.size();j++)
        if (s1[i]._cell==s2[i]._cell)
            contain=true;
    if(contain) result.push_back(s1[i]);
  }
  return result;
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
vector<user> newVec; if (searchKey.size()!=0){
    for (int i=0;i<(int)searchKey.size();i++)
            transform(searchKey[i].begin(), searchKey[i].end(), searchKey[i].begin(), ::tolower);
    
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
		newVec=setInter(newVec,secVec);
	}
}
   // if (searchKey.size()==0)
     else   for(map<string,user>::iterator it=users.begin();it!=users.end();++it)
    {
        user newUser=it->second;
        newVec.push_back(newUser);
    }
   return newVec;
}
void dbase::parse(string fileloc)
{
    ifstream infile(fileloc.c_str());
    string tag,name,date,cell,email,address,callBackDate,make,model,orderNumber;//,pic1,pic2,pic3;
    int newTag,leaseTag;
    string exterior,interior,year,msrp,options,price;
    int down,term,miles,dotd;
    infile>>tag;
    while (tag=="Another")
    {
        tag=="0";
        infile>>name>>date>>cell>>email>>make>>model;
        user newUser(name,date,cell);
        newUser._email=email;
        newUser._make=producer(make);

    //newUser._address=address;
 
    newUser._model=producer(model);
    infile>>newTag>>leaseTag;
    if (!newTag)
    {   newUser._new=newTag;
        newUser._lease=leaseTag;
        infile>>exterior>>interior>>year>>msrp>>options>>price;
        newUser._exterior=exterior;
        newUser._interior=interior;
        newUser._year=year;
        newUser._msrp=msrp;
        newUser._options=options;
        newUser._price=price;
    }
    else if(!leaseTag)
    {
        newUser._new=newTag;
        newUser._lease=leaseTag;
        infile>>dotd;
        newUser._dotd=dotd;
    }
    else if(leaseTag)
    {
        newUser._new=newTag;
        newUser._lease=leaseTag;
        infile>>down>>term>>miles;
        newUser._down=down;
        newUser._term=term;
        newUser._miles=miles;
    }
    infile>>orderNumber;
    newUser._orderNumber=orderNumber;
    infile>>callBackDate;
    newUser._callBackDate=callBackDate;
    this->addUser(newUser);
    infile>>tag;
    if (tag!="Another")
        while (tag!="end")
            infile>>tag;
    }
}
void dbase::dump(ostream& os)
{
   for(map<string,user>::iterator it=users.begin();it!=users.end();++it)
    {
        user newUser=it->second;
        os<<"Another "<<endl;
        newUser.dump(os);
        os<<endl;
    }
    os<<"end";
}
vector<user> dbase::findDate(string Qdate)
{
    vector<user> toCall;
    for(map<string,user>::iterator it=users.begin();it!=users.end();++it)
    {
        user newUser=it->second;
        cout<<Qdate<<endl;
        cout<<newUser._callBackDate;
        if (newUser._callBackDate==Qdate)
            toCall.push_back(newUser);

    }
    return toCall;
}