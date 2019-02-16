#ifndef BOOK_H
#define BOOK_H
#include <iostream>
#include <string>
#include <vector>
#include <stdlib.h>
#include "Time.h"
using namespace std;
/*
This class is a container object called Book. The Library holds these books,
and they are exchanged among accounts.
*/

class Book
{
public:
	//Constructors
	Book(){};
	Book(string title, string author, string genre);
	Book(vector<string> Bookinfo);
	Book(int ID, int DueDate, int numRenew);
	
	//Prints short info of book
	void PrintBookDataShort();
	//Prints full info of book
	void PrintBookDataFull();
	//Prints formatted full info of book
	void PrintBookDataFullIndent();
	//Prints if book is available or who it is checked out by
	void PrintStatus();
	//returns file line format of book info
	string outputBook();
	//returns file line format of checked out book info
	string outputCheckedoutBooks();
	//returns true if book is overdue
	bool is_Overdue();
	//Renews book if possible
	void renew();
	//Resets book info
	void refresh();
	//Adds to popularity score
	void addPopularity(){PopularityScore++;}
	
	//Mutator Functions: sets private memeber variables
	void setBookID(int num);
	void setCheckOutStatus(bool checkout);
	void setDueDate(int days){TimeUntilReturn=days;}
	void setRenewTimes(int num){Renewed=num;}
	void setBorrowerID(int id){BorrowerID=id;}
	
	//Accessor Functions: returns private member variables
	int getBookID() const;
	int getBorrowerID()const{return BorrowerID;}
	int getPopularity() const;
	string getAuthor() const;
	string getTitle() const;
	string getGenre() const;
	int getDueDate() const{return TimeUntilReturn;}
	int getRenewed() const{return Renewed;};
	bool getCheckedOutStatus() const;

private:
	int BookID;
	int TimeUntilReturn;
	int PopularityScore;
	int Renewed;
	int BorrowerID;
	string Title;
	string Author;
	string Genre;
	bool checkedOut;
	bool Overdue;
	

};

#endif