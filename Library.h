#ifndef LIBRARY_H
#define LIBRARY_H
#include <iostream>
#include <string>
#include "Book.h"
#include "BookList.h"
#include "AccountList.h"
#include "Account.h"
#include <fstream>
using namespace std;

/*
This class manages between a Library of it's books and a Library of it's accounts.
THe class allows the exchange of books between accounts and and the library
of books. Can print library system information, add accounts and books,
remove them, and print help info. 
*/

class Library
{
public:
	Library(){};
	//Takes in file to initialize LibraryOfBooks and Users
	Library(string BookFile, string AccountFile);
	//Adds book given a book
	void addBook(Book* someBook);
	//Adds book given info
	void addBook(string title, string author, string genre);
	//adds account given a name
	void addAccount(string name);
	//Takes back given book
	void recieveBook(int BookID);
	//Gives book with given ID to Account with  given ID 
	void giveBook(int AccountID, int BookID);
	//Permanently removes book from library and user
	void removeBook(int BookID);
	//Remove an account with given ID permanently
	void removeAccount(int UserID);
	//Force takes a book from an account
	void ForceReturn(int BookID);
	//Prints Book given its ID
	void PrintBook(int ID);
	//Prints Account info given ID
	void printUserInfo(int ID);
	//Prints account info of all accounts
	void printAccounts(string criteria);
	//Prints books ordered by a criteria(name,id,popularity,genre,author)
	void browse(string criteria);	
	//Prints search results of a book given search criteria and search phrase
	void searchBook(string criteria, string item);
	//Renews books of person with given ID
	void RENEW(int AccountID);
	//Prints System info
	void System();
	//Prints Command info
	void HELP();
	//Prints Recommendations to UserId  
	void RECOMMEND(int UserID);
	//Exports book and account files
	void Export(string bookFileName, string accountsFileName);
	//Checks if book with author or title exists in Library
	bool contains(string author, string title);

	//ACCESSOR FUNCTIONS
	//Returns number of users
	int getAccountsSize(){return Users.getSize();}
	//Returns number of books
	int getLibrarySize(){return LibraryOfBooks.getSize();}

private:
	BookList LibraryOfBooks; //contains all books
	AccountList Users;	//contains all accounts
	int initialSize;
	
};
#endif