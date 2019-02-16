#ifndef BOOK_CPP
#define BOOK_CPP
#include <iostream>
#include <string>
#include "Book.h"
#include "Time.h"
using namespace std;

//constructor creates a book with given title, author, genre. 
Book::Book(string title, string author, string genre)
{
	Title=title;
	Author=author;
	Genre=genre;
	TimeUntilReturn=Time::getTime()+15;
	checkedOut=false;
	PopularityScore=0;
	Renewed=0;
}
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
//Constructor makes book given id, due date, and times renewed
Book::Book(int ID, int DueDate, int numRenew)
{
	BookID=ID;
	TimeUntilReturn=DueDate;
	Renewed=numRenew;
	PopularityScore=0;
	checkedOut=false;
	TimeUntilReturn=Time::getTime()+15;
}
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
//creates book given info stored in a vector(reading a file)
Book::Book(vector<string> Bookinfo)
{
  BookID = atoi((Bookinfo[0]).c_str()); //stoi
  Title = Bookinfo[1];
  Author = Bookinfo[2];
  Genre = Bookinfo[3];
  PopularityScore = atoi((Bookinfo[4]).c_str());
  TimeUntilReturn=Time::getTime()+15;
  checkedOut=false;
  Renewed=0;
  BorrowerID=-1;
}
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
//Resets book information
void Book::refresh()
{
 	TimeUntilReturn=Time::getTime()+15;
	checkedOut=false;
	Renewed=0;
	BorrowerID=-1;
}
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
//Prints short data of a book
void Book::PrintBookDataShort()
{
	cout<<"\""<<Title<<"\" by "<< Author<<
	" (BookID# "<<BookID<<") ["<<Genre<<"]. ";
}
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
void Book::PrintStatus()
{
	if (checkedOut)
	{
		cout<<"CHECKED OUT (AccountID# "<<BorrowerID<<")."<<endl;
	}
	else
	{
		cout<<"AVAILABLE. "<<endl;
	}
}
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
//Prints full data of a book
void Book::PrintBookDataFull()
{
	cout<<"Title: \""<<Title<<"\""<<endl;
	cout<<"Author: "<<Author<<endl;
	cout<<"BookID#: "<< BookID<<endl;
	cout<<"Genre: "<<Genre<<endl;
	cout<<"Popularity Score: "<<PopularityScore<<endl;
	
}
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
//Prints indented data of a book
void Book::PrintBookDataFullIndent()
{
	cout<<"\t"<<"Title: \""<<Title<<"\""<<endl;
	cout<<"\t"<<"Author: "<<Author<<endl;
	cout<<"\t"<<"BookID#: "<< BookID<<endl;
	cout<<"\t"<<"Genre: "<<Genre<<endl;
	cout<<"\t"<<"Popularity Score: "<<PopularityScore<<endl;
	cout<<"\t"<<"Due Date: "<<TimeUntilReturn<<endl;
	cout<<"\t"<<"Times renewed: "<<Renewed<<endl;
	if (is_Overdue())
	{
		cout<<"\t"<<"OVERDUE"<<endl;
	}
	
}
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
//Returns true if a book is overdue
bool Book::is_Overdue()
{
	return (TimeUntilReturn<Time::getTime());
}
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
//Renews a book if it is not overdue or reached a max of 2 renews
void Book::renew()
{
	//Adds 5 days for a max of two times to non overdue books
	if(Renewed<2 and !is_Overdue())
	{
		TimeUntilReturn+=5;
		Renewed++;
		PrintBookDataFullIndent();
		cout<<"\t"<<"Book successfully renewed."<<endl;
	}
	else
	{
		PrintBookDataFullIndent();
		cout<<"\t"<<"Book already renewed twice"<<endl;
	}
}
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
//Returns a string of a book file format
string Book::outputBook()
{
	string a=to_string(BookID)+"|"+Title+"|"+Author+"|"+Genre+"|"+to_string(PopularityScore);
	return a;
}
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
//Returns a string of a checked out book in file format
string Book::outputCheckedoutBooks()
{
	string a=to_string(BookID)+"|"+to_string(TimeUntilReturn)+"|"+to_string(Renewed)+"\n";
	return a;
}
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
//Sets checkout status
void Book::setCheckOutStatus(bool checkout)
{
	checkedOut=checkout;
}
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
//Sets bookID
void Book::setBookID(int num)
{
	BookID=num;
}
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
//returns bookid
int Book::getBookID() const
{
	return BookID;
}
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
//returns checkout status
bool Book::getCheckedOutStatus() const
{
	return checkedOut;
}
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
//returns author
string Book::getAuthor() const
{
	return Author;
}
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
//returns title
string Book::getTitle() const
{
	return Title;
}
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
//returns popularity
int Book::getPopularity() const
{
	return PopularityScore;
}
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
//returns genre
string Book::getGenre() const
{
	return Genre;
}
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

#endif