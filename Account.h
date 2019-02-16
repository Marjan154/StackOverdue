#ifndef ACCOUNT_H
#define ACCOUNT_H
#include <iostream>
#include <string>
#include <vector>
#include <stdlib.h>
#include "Book.h"
#include "BookList.h"
#include <iomanip>
#include <map>
#include <set>
using namespace std;

/*
This class represents an account. An aacount interacts wiht a Library 
to fill up it's map of books.The books can be added, removed, renewed,
and account info can be printed. Recommendations for each accounts are made
based on the ccounts info.
*/

class Account
{
public:
	~Account();
	//Default constructor
	Account(){};
	//Creates account given name or ID
	Account(string name, int ID);
	//Constructor creates accounts given a vector of id, name, and checkout
	//and their books
	Account(vector<string> AccountInfo, BookList myLib);
	//User checkout a book, given a book
	void CheckoutBook(Book* someBook);
	//Renew all of users books
	void renewBooks();
	//Print short account info
	void printAccount();
	//Print short account info
	//void printAccountShort();
	//print partial account info
	void printPartialBook(int BookID);
	//print full account info
	void printAccountFull();
	//Returns book with given Id to a Library
	void returnBook(int BookID);

	void Remove(int BookID);
	//Forcefully removes book from users books
	void forceRemoveBooks();
	//Returns true if user has book with given ID
	bool hasBook(int BookID);
	//Returns true if user has overdue books
	bool hasOverdueBooks();
	//Recommends based on users books read
	void Recommend(const BookList Library);
	//Returns a string of an account info and books in file line format
	string outputAccount();
	//Returns user's ID
	int getUserID() const;
	//Returns user's name
	string getName() const;
	//Returns how many books user has
	int getCheckouts() const;

private:
	
	int numBooks;
	string Name;
	int UserID;
	int checkouts;	
	string MostReadGenre;
	string SecondMostReadGenre;
	string FavoriteAuthor;
	//Users list of books, max size of 10
	unordered_map<int, Book*> myBooks;
	//Users histories of books, organized by genre or by author
	multimap<string, Book*> GenreCount;
	multimap <string, Book*> AuthorCount;
	//HELPER FUNCTIONS
	//Calculates and sets users favorite author
	void FaveAuthor();
	//Calculates and sets user top 2 favorite authors
	void FaveGenre();
	//Prints reccomendations of books from a given Library based on
	//a given favorite author and genres
	void findRecommend(string criteria, string fave, BookList Library);
	//Comparator used to insert books in a certain order
	struct Comparator{bool operator ()(const pair<string, int> &a, const pair<string, int> &b){return (a.second > b.second or a.second==b.second)and(a.first!=b.first);}};
};

#endif