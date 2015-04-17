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
void dbase::addUser(user newUser)
{
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
    for (int i=0;i<(int)searchKey.size();i++)
            transform(searchKey[i].begin(), searchKey[i].end(), searchKey[i].begin(), ::tolower);
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
		newVec=setInter(newVec,secVec);
	}
   return newVec;
}
void dbase::parse(string fileloc)
{
    ifstream infile(fileloc.c_str());
    string tag,name,date,cell,other,email,address,Referral,Broker,Office,SSN,MonthlyIncome,DOB,Ethnicity,Gender,Occupation,callBackDate;//,pic1,pic2,pic3;
    string carTag,make,exterior,interior,year,MRSP,value,navigation,rearCamera,feature;
    infile>>tag;
    while (tag=="Another")
    {
        infile>>name>>date>>cell>>other>>email>>address>>Referral>>Broker>>Office>>SSN>>MonthlyIncome>>DOB>>Ethnicity>>Gender>>Occupation>>callBackDate;
        user newUser(name,date,cell,other,address);
        newUser._email=email;
    //newUser._address=address;
    newUser._Referral=Referral;
    newUser._Broker=Broker;
    newUser._Office=Office;
    newUser._SSN=SSN;
    newUser._MonthlyIncome=MonthlyIncome;
    newUser._DOB=DOB;
    newUser._Ethnicity=Ethnicity;
    newUser._Gender=Gender;
    newUser._Occupation=Occupation;
    newUser._callBackDate=callBackDate;
       
        infile>>carTag;
        if (carTag=="Yes")
         {
          newUser.haveCar=true;
         infile>>make>>exterior>>interior>>year>>MRSP>>value>>navigation>>rearCamera>>feature;
         car newCar(make,exterior,interior,year);
         newCar._MRSP=MRSP;
         newCar._value=value;
         newCar._navigation=navigation;
         newCar._rearCamera=rearCamera;
         newCar._feature=feature;
         newUser._car=newCar;
        }
            int numOfCalls;
            infile>>numOfCalls;
            newUser._callHistoryNum=numOfCalls;
            string callDate,method,comment;
            for(int i=0;i<numOfCalls;i++)
            {
                infile>>callDate>>method;
                infile>>make>>exterior>>interior>>year>>MRSP>>value>>navigation>>rearCamera>>feature;
            car newCar(make,exterior,interior,year);
             newCar._MRSP=MRSP;
            newCar._value=value;
            newCar._navigation=navigation;
             newCar._rearCamera=rearCamera;
            newCar._feature=feature;
                infile>>comment;
                callHistory newHistory(callDate,newCar,method,comment);
                newUser._callHistory.push_back(newHistory);
            }
            this->addUser(newUser);
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
        if (newUser.haveCar) {os<<"Yes "; newUser._car.dump(os);} else os<<"No ";
        os<<newUser._callHistoryNum<<" ";
        for(int i=0;i<newUser._callHistoryNum;i++)
            newUser._callHistory[i].dump(os);
    }
    os<<"end";
}