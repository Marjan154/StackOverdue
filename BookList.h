#ifndef BOOKLIST_H
#define BOOKLIST_H
#include <iostream>
#include <fstream>
#include <string>
#include "Book.h"
#include <sstream>
#include <map>
#include <unordered_map>
#include <string>  
#include <vector>
#include <algorithm>
#include "Time.h"
using namespace std;

/*
This class holds a map of books. THis map of books can exist within an
Account, as a users reading list, or in a a Library, as a Libarary Of books.
The books can be added, removed, renewed, and printed as needed.
*/

class BookList
{
public:
	//~BookList();
	//Default Constructor
	BookList(){};
	

	//Constructor takes a file of book info and creates a library of books
	BookList(string BooksFile); 

	//Overloaded AddBook functions all add books to ListOfBooks map,
	// given cerain input
	void AddBook(string Name, string Author, string Genre);
	//Takes a string of book info in the file format, and adds book
	void AddBook(string input);//
	void AddBook(Book* someBook);//
	void AddBook(int ID);
	
	//Removes a book given its ID
	void removeBook(int BookID);//
	
	//Returns a book pointer with a given ID and sets its checkout status to true
	Book* TakeBookFromLibrary(int BookID);
	
	//Prints full data of single book
	void PrintBook(int ID);
	
	//Prints short data of all Books
	void PrintBooksShort();
	
	//Prints full data of all Books
	void PrintBooks();
	
	//Renews all books if allowed
	void RenewAllBooks();
	
	//Prints out all books given an order criteria(title,author,genre,bookid,popularity)
	void Browse(string criteria);
	
	//Prints out search results after searching for a book
	// given a search criteria and a search phrase
	void search(string criteria, string item);
	
	//Recommends a book from a Library, based on criteria(genre or author)
	//and a favorite of that criteria
	void Recommend(string criteria, string fave, BookList Library);
	
	//returnns a book with the given ID
	Book* findBook(int BookID);
	
	//Returns true if contains a book with same ID
	bool hasBook(int BookID);
	
	//returns true if any books are overdue
	//bool hasOverdueBooks();
	
	//returns true if book with same name or author already exists
	bool contains(string Name, string Author);
	
	//returns the number of overdue books
	int OverdueBooksCount();
	
	//Outputs a file of all books given a file name
	void outputBooks(string bookFileName);
	
	//returns a string of file line format of checked out books
	string outputCheckedoutBooks();
	
	//returns number of books
	int getSize() const;

	//Orders a vector of books based on criteria(name,author,genre, popularity, id)
	vector<Book*> order(string criteria);
	

private:
	unordered_map <int, Book*> ListOfBooks;
	int highestID;
	int size;
	//Helper function to print a vector of books
	void printVector(vector<Book*> vect);
	

};

#endif
