#include <iostream>
#include <string>
#include <map>
#include "user.h"
#include "car.h"
#include "dbase.h"

using namespace std;

string decrypt(string tode);
string encrypt(string toen);

int main() {
    int control=0;
    dbase myBase;
    while(control!=1)
    {
        cout<<"enter 1 to quit, other to continue,2 to print all,3 to search";
        cin>>control;
        if (control==2)
        {   vector<user> result=myBase.returnAll();
            for(int i=0; i<(int)result.size(); i++)
                cout<<result[i].displayString()<<endl;
        }
        else if (control==1)
        	break;
        else if (control==3)
        {
        	string keyword;
        	cin>>keyword;
        	vector<string> keywords;
        	keywords.push_back(keyword);
        	 vector<user> result=myBase.search(keywords);
            for(int i=0; i<(int)result.size(); i++)
                cout<<result[i].displayString()<<endl;
        }
        else{
        cout<<"enter your first name"<<endl;
        string firstname,lastname,cell,ssn,dob,address;
        cin>>firstname;
        cout<<"enter your lastname"<<endl;
        cin>>lastname;
        cout<<"enter your ssn"<<endl;
        cin>>ssn;
        cout<<"enter your dob"<<endl;
        cin>>dob;
        cout<<"enter your address"<<endl;
        cin>>address;
        cout<<"enter your cell"<<endl;
        cin>>cell;
        user newUser(firstname,lastname,cell,ssn,address,dob);
        cout<<newUser.displayString();
        myBase.addUser(newUser);
    }
    }
    return 0;
}