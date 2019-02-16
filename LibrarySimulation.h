#ifndef LIBRARYSIMULATION_H
#define LIBRARYSIMULATION_H
#include <iostream>
#include <string>
#include "Library.h"
#include "Time.h"
using namespace std;

/*
THis class takes in user input in order to use the Library system. Users
can checkout books, renew books, browse, add  books or new accounts, remove 
them, search for and export books, after giving an appropriate command.
*/

class LibrarySimulation
{
public:
	LibrarySimulation(){};
	//Constructor takes in two files
	LibrarySimulation(string bookfile, string accountfile);
	//Takes command of user, and responds
	void BeginSimulation(string input);
	//Continues taking command until EXIT is called.
	void UseSystem();
private:
	Library StackOverdue;
};
#endif