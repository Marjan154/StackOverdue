#ifndef TIME_CPP
#define TIME_CPP
#include <iostream>
#include <string>
#include "Time.h"
using namespace std;

//initializing time
int Time::time=1;

//Adds time from user input
void Time::timeJump()
{
	int days;
	cout<<"Enter the number of days to time travel."<<endl;
	cin>>days;
	//Make sure int or positive number is enetered
	if (cin.fail() or days<1)
	{
		cout<<"Invalid value."<<endl;
	}
	else
	{
		cout<<"Traveled "<<days<<" days through time ("<<time;
		time=time+days;
		cout<< "-->"<<time<<")."<<endl;
	}
}

#endif