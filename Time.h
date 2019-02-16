#ifndef TIME_H
#define TIME_H
#include <iostream>
#include <string>
using namespace std;


class Time
{
public:
	static void timeJump(); //skips time
	static int getTime(){return time;}

private:
	static int time;
};
#endif