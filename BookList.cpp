#ifndef BOOKLIST_CPP
#define BOOKLIST_CPP
#include "BookList.h"
using namespace std;

//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
// reads file, creates book with info, adds it into a map.
BookList:: BookList(string BooksFile)
{
	highestID=0;
	ifstream BookFile;
	string BookData;
	BookFile.open(BooksFile);
	if (!BookFile.is_open())
	{
		cout<< "Could not find file "<<BooksFile<<". Skipping."<<endl;
	}
	getline(BookFile, BookData);
	while(getline(BookFile,BookData))
	{
		AddBook(BookData);
	}
	BookFile.close();
	size=ListOfBooks.size();
}
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
//Removes book with the given id
void BookList::removeBook(int BookID)
{
	ListOfBooks.erase(BookID);	//remove
}
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
//Creates and Adds book given a title, author, and genre, if book does not 
//already exist
void BookList::AddBook(string Name, string Author, string Genre)
{
	Book* someBook= new Book(Name, Author, Genre);
	int newID=highestID+1;
	highestID++;
	someBook->setBookID(newID);
	ListOfBooks.insert(std::pair<int,Book*>(newID,someBook));
	cout<<"BOOKID# "<<newID<<" successfully created."<<endl;			
}
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
//Adds a book pointer to the List of books
void BookList::AddBook(Book* someBook)
{
	ListOfBooks.insert(std::pair<int,Book*>(someBook->getBookID(),someBook));	
}
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
//splits a string and makes a book with that info. Adds book to map.
void BookList::AddBook(string input)
{   //store content in vector [id, title,genre, author, popularity]
	//then create the book, and insert it in the map
	vector<string> Books;
	istringstream ss(input);
	//split line by "|"
	for (string each_split; getline(ss, each_split, '|');)
	{
	  Books.push_back(each_split);//add info to a vector
	  if (Books.size()==5)		  //until all info gotten
	  {
	    Book* myBook= new Book(Books);	//make and add book
	    AddBook(myBook);
	    if (highestID<atoi(Books[0].c_str()))
	    {
	    	highestID=atoi(Books[0].c_str());//highest
	    }
	    Books.clear();	//clear and redo
	  }
	}
}
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
//Checks if a book with the same name or author exists already
bool BookList::contains(string Name, string Author)
{
	for(auto it = ListOfBooks.begin();it!= ListOfBooks.end(); ++it) 
	{
		if(it->second->getTitle()==Name and it->second->getAuthor()==Author)
		{
			return true;
		}			
	}
return false;
}
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
//Returns the pointer to a book given its ID
Book* BookList::findBook(int BookID)
{
	return ListOfBooks[BookID];
}
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
//Checksout Book, to give to user
Book* BookList::TakeBookFromLibrary(int BookID)
{
	ListOfBooks[BookID]->setCheckOutStatus(true);
	ListOfBooks[BookID]->setDueDate(Time::getTime()+15);
	return ListOfBooks[BookID];
}
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
//Renews every book in the list, if possible
void BookList::RenewAllBooks()
{
	//Count how many books will be renewed, then print it
	int count=0;
	for(auto it = ListOfBooks.begin();it!= ListOfBooks.end(); ++it) 
	{
		if (it->second->getRenewed()>=2)
		{
			count++;
		}
	}
	cout<<ListOfBooks.size()-count<<" of "<<ListOfBooks.size()<<
	" books successfully renewed."<<endl;
	//Renew books in the list of books.
	for(auto it = ListOfBooks.begin();it!= ListOfBooks.end(); ++it) 
	{
		if (it->second->getCheckedOutStatus()==true)
		{
			it->second->renew();
			cout<<endl;
		}
	}
}
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
//Returns how many books are overdue in the list of books
int BookList::OverdueBooksCount()
{
	//Count overdue books
	int count=0;
	for (auto it = ListOfBooks.begin(); it !=ListOfBooks.end() ; ++it)
	{
		if (it->second->getCheckedOutStatus()==1 and it->second->is_Overdue())
		{
			count++;
		}
	}
return count;
}
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
//Prints full description of a book given its ID
void BookList::PrintBook(int ID)
{
	if(ListOfBooks.find(ID)==ListOfBooks.end())
	{
		cout<<"BookID# "<<ID<<" not found."<<endl;
	}
	else
	{
		ListOfBooks[ID]->PrintBookDataFull();
	}
}
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
//Prints full description of a book given its ID
void BookList::PrintBooksShort()
{
	int x=1;
	for(auto it = ListOfBooks.begin();it!= ListOfBooks.end(); ++it) 
	{
		cout<< "\t"<<x<<". ";
		ListOfBooks[it->first]->PrintBookDataShort();
		cout<<endl;
		x++;
	}
}
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
//Prints full descriptions of all data in the maps
void BookList::PrintBooks()
{	
	int x=1;
	for(auto it = ListOfBooks.begin();it!= ListOfBooks.end(); ++it) 
	{
		cout<<"\t"<<x<<". "<<endl;
		ListOfBooks[it->first]->PrintBookDataFullIndent();
		x++;
	}
}
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
//Helper function to print vector
void BookList::printVector(vector<Book*> vect)
{
	for (unsigned int i = 0; i < vect.size(); i++)
	{
		cout<<i+1<<". ";
		vect[i]->PrintBookDataShort();
		vect[i]->PrintStatus();
	}
}
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
//Prints books after ordered by criteria
void BookList::Browse(string criteria)
{
		printVector(order(criteria));	
}
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
//Returns a vector ordered by specific criteria
vector<Book*> BookList::order(string criteria)
{	
	vector<Book*> BooksToSort;
		//Copy map items in a vector that will be ordered based on criteria
	for (auto  it = ListOfBooks.begin(); it!=ListOfBooks.end(); ++it)
	{
		BooksToSort.push_back(it->second);
	}
		//Sorts vector by title, alphabetically;
	if (criteria=="title")
	{
		sort (BooksToSort.begin(), BooksToSort.end(), [](Book* const &a, Book* const &b){ return a->getTitle() < b->getTitle(); });
	}
	//Sorts vector by genre, alphabetically;	
	if (criteria=="genre")
	{
		sort (BooksToSort.begin(), BooksToSort.end(), [](Book* const &a, Book* const &b){ return a->getGenre() < b->getGenre(); });
	}
	//Sorts vector by genre, alphabetically;
	if(criteria=="author")
	{
		sort (BooksToSort.begin(), BooksToSort.end(), [](Book* const &a, Book* const &b){ return a->getAuthor() < b->getAuthor(); });
	}
	//Sorts vector by bookID, ascending numerical;
	if(criteria=="bookid")
	{
		sort (BooksToSort.begin(), BooksToSort.end(), [](Book* const &a, Book* const &b){ return a->getBookID() < b->getBookID(); });
	}
	//Sorts vector by popularity, descending numerical;
	if(criteria=="popularity")
	{
		sort (BooksToSort.begin(), BooksToSort.end(), [](Book* const &a, Book* const &b){ return a->getPopularity()> b->getPopularity(); });	
	}
return BooksToSort;
}
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
//Prints out search results after searching for a book
// given a search criteria and a search phrase
void BookList::search(string criteria, string item)
{
	int count=1;
	bool found=false;
	for(auto  it = ListOfBooks.begin(); it!=ListOfBooks.end()  ; ++it)
	{ 
		if (criteria=="title")
		{
			if((it->second->getTitle()).find(item)!= std::string::npos)
			{
				found=true;
				if (count==1)
				{
					cout<<"Search Results:"<<endl;
				}
				cout<<count<<". ";
				it->second->PrintBookDataShort();
				it->second->PrintStatus();
				count++;
			}
		}
	
		if (criteria=="author")
		{
			if((it->second->getAuthor()).find(item)!= std::string::npos)
			{
				found=true;
				if (count==1)
				{
					cout<<"Search Results:"<<endl;
				}
				cout<<count<<". ";
				it->second->PrintBookDataShort();
				it->second->PrintStatus();
				count++;
			}
		}	
	}		
	if (!found)
	{
		cout<<"No search results found."<<endl;
	}
}
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
//Check if book with given id exists
bool BookList::hasBook(int BookID)
{
	return (ListOfBooks.find(BookID)!=ListOfBooks.end());
}
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
//Output file of all books
void BookList::outputBooks(string bookFileName)
{			
	ofstream sendfile;			
	sendfile.open(bookFileName);
	if (ListOfBooks.size()>0)
	{
		sendfile<<to_string(ListOfBooks.size())<<endl;
	}		
	for (auto it = ListOfBooks.begin(); it !=ListOfBooks.end() ; ++it)
	{
		sendfile << it->second->outputBook()<<endl;
	}
	sendfile.close();		
}
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
//Returns number of books
int BookList::getSize() const
{
	return ListOfBooks.size();
}
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
#endif