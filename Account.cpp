#ifndef ACCOUNT_CPP
#define ACCOUNT_CPP
#include <iostream>
#include <string>
#include "Account.h"
using namespace std;

//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
//deallocate account book holding structures
Account::~Account()
{
	//erase from users books and book histories
	for (auto it = myBooks.begin();it!= myBooks.end(); ++it)
	{
		delete it->second;
		myBooks.erase(it->second->getBookID());
	}
	for (auto it = GenreCount.begin();it!= GenreCount.end(); ++it)
	{
		delete it->second;
		GenreCount.erase(it->second->getGenre());
	}
	for (auto it = AuthorCount.begin();it!= AuthorCount.end(); ++it)
	{
		delete it->second;
		AuthorCount.erase(it->second->getAuthor());
	}
}
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
//initialize account with name and ID
Account::Account(string name, int ID){
  UserID = ID; 
  Name = name;
  checkouts=myBooks.size();
}
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
//Constructor creates accounts given a vector of id, name, and checkout
//and their books
Account::Account(vector<string> AccountInfo, BookList myLib){
  //first 3 eleemnts in vector are user id, name, #books
  UserID = atoi((AccountInfo[0]).c_str()); //
  Name = AccountInfo[1];
  numBooks=atoi((AccountInfo[2]).c_str());
  //For evry 3 peices of info(book id, due date,popularity) after that, 
  //create a book and add it to users list of checked out books
  for (unsigned int i = 3; i <AccountInfo.size() ; i=i+3)
  {
  	int id=atoi((AccountInfo[i]).c_str());
  	//Checks if book even exists.If it does checkout & set book info
  	if (myLib.hasBook(id))
  	{
  		int due=atoi((AccountInfo[i+1]).c_str());
	  	int renew=atoi((AccountInfo[i+2]).c_str());
	  	Book* myBook=new Book(id, due, renew);
	  	myBook=myLib.findBook(id);
	  	myBook->setDueDate(due);
	  	myBook->setRenewTimes(renew);
		CheckoutBook(myBook);
		myBook->setCheckOutStatus(true);
		myBook->setBorrowerID(UserID);  
  	}
  	else
  	{
  		cout<<"Could not find library book with ID# "<<id<<endl;
  	}
  }
}
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
//Deletes book
void Account::Remove(int BookID)
{
	myBooks.erase(BookID);//delete
}
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
//Force returns all books to library
void Account::forceRemoveBooks()
{
	//If user has any books, go through booklist. Print indication, and remove
	if (myBooks.size()>0)
	{
		for (auto it = myBooks.begin();it!= myBooks.end(); ++it)
		{
			cout<<"\""<<it->second->getTitle()<<"\" by "<<it->second->getAuthor()
			<<" (BookID# "<<it->second->getBookID()<<") force returned."<<endl;
			it->second->setCheckOutStatus(false);
		}
	}
}
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
//Checks out a book given a book
void Account::CheckoutBook(Book* someBook)
{
	//Count to check if book exists in history, to see if need to add popularity
	bool contains=false;
	someBook->setBorrowerID(UserID);
	for(auto it = GenreCount.begin();it!= GenreCount.end(); ++it)
	{
		if (it->second->getBookID()==someBook->getBookID())
		{
			contains=true;
		}
	}
	//Adds book to booklist and history of books
	myBooks.insert(std::pair<int,Book*>(someBook->getBookID(),someBook));
	GenreCount.insert(std::pair<string,Book*>(someBook->getGenre(),someBook));
	AuthorCount.insert(std::pair<string,Book*>(someBook->getAuthor(),someBook));
	//If book was never checked out before, add to popularity score
	if (!contains)
	{
		someBook->addPopularity();
	}
}

//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
//Calculates 2 favorite genres and sets it
void Account::FaveGenre()
{
	//Inserts pairs of genre and count of genre form gretatest to least
  	set<pair<string, int>, Comparator> counts;
	int count;
	vector<string> faves;
	for(auto it = GenreCount.begin();it!= GenreCount.end(); ++it)
	{
		count=GenreCount.count(it->first);
		counts.insert(std::pair<string,int>(it->second->getGenre(), count));
	}
	for(auto it = counts.begin();it!= counts.end(); ++it)
	{
		faves.push_back(it->first);
		if(faves.size()==3){break;} //breaks after highest 2 added
	}
MostReadGenre=faves[0];
SecondMostReadGenre=faves[1];
}
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
//Finds and sets favorite author
void Account::FaveAuthor()
{
	//Inserts pairs of author and counts of author form gretatest to least
  	set<pair<string, int>, Comparator> counts;
	int count;
	for(auto it = AuthorCount.begin();it!= AuthorCount.end(); ++it)
	{
		count=AuthorCount.count(it->first);
		counts.insert(std::pair<string,int>(it->second->getAuthor(), count));
	}
//Returns the first one or the max out of ordered set
FavoriteAuthor=counts.begin()->first;
cout<<FavoriteAuthor<<endl;
}
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
void Account::findRecommend(string criteria, string fave, BookList Library)
{
	int counter=1;
	vector<Book*> vect=Library.order("popularity");		
	for (unsigned int i = 0; i < vect.size(); ++i)
	{
		if (criteria=="genre")
		{
			if(vect[i]->getGenre()==fave)
			{
				cout<<counter<<". ";
				vect[i]->PrintBookDataShort();
				vect[i]->PrintStatus();
				counter++;
				if (counter==3){break;}
			}		
		}

		if (criteria=="author")
		{
			if (vect[i]->getAuthor()==fave)
			{	
				cout<<counter<<". ";
				vect[i]->PrintBookDataShort();
				vect[i]->PrintStatus();
				break;
			}			
		}	
	}
}
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
//Prints reccomendations of books from a given Library based on
//users favorite author and genres
void Account::Recommend(BookList Library)
{
	//If book is already in reading history, dont include in recommendations
	for (auto it = GenreCount.begin();it!= GenreCount.end(); ++it)
	{
		if (Library.hasBook(it->second->getBookID()))
		{
			Library.removeBook(it->second->getBookID());
		}
	}
	//If no books ever read, no recommendations
	if (GenreCount.size()==0)
	{
		cout<<"No available recommendations."<<endl;
	}
	//If one book read, recommend 3 books only
	else if (GenreCount.size()==1)
	{
		MostReadGenre=GenreCount.begin()->second->getGenre();
		FavoriteAuthor=AuthorCount.begin()->second->getAuthor();
		cout<<"You love "<< MostReadGenre <<". We recommend:"<<endl;
		findRecommend("genre", MostReadGenre, Library);
		cout<<"You love "<< FavoriteAuthor <<". We recommend:"<<endl;
		findRecommend("author", FavoriteAuthor, Library);
	}
	//Else recommend 5 books
	else
	{
		FaveGenre();
		FaveAuthor();
		cout<<"You love "<< MostReadGenre <<". We recommend:"<<endl;
		findRecommend("genre", MostReadGenre, Library);
		cout<<"You love "<< SecondMostReadGenre <<". We recommend:"<<endl;
		findRecommend("genre", SecondMostReadGenre, Library);
		cout<<"You love "<< FavoriteAuthor <<". We recommend:"<<endl;
		findRecommend("author", FavoriteAuthor, Library);
	}	
}
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
//Renews all books if allowed
void Account::renewBooks()
{
	int count=0;
	for(auto it = myBooks.begin();it!= myBooks.end(); ++it) 
	{
		if (it->second->getRenewed()>=2)
		{
			count++;
		}
	}
	cout<<myBooks.size()-count<<" of "<<myBooks.size()<<
	" books successfully renewed."<<endl;
	//Renew books in the list of books.
	for(auto it = myBooks.begin();it!= myBooks.end(); ++it) 
	{
		if (it->second->getCheckedOutStatus()==true)
		{
			it->second->renew();
			cout<<endl;
		}
	}
}
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
//Prints short Account info
void Account::printAccount()
{
	cout<<Name;
	cout<<" (AccountID# "<<UserID<<"). ";
	if (myBooks.size()==0)
	{
		 cout<<"No books checked out."<<endl;
	}
	else
	{
		cout<<myBooks.size()<<" books checked out."<<endl;
	}
	int x=1;
	for(auto it = myBooks.begin();it!= myBooks.end(); ++it) 
	{
		cout<< "\t"<<x<<". ";
		myBooks[it->first]->PrintBookDataShort();
		cout<<endl;
		x++;
	}
}
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
//Prints full account info 
void Account::printAccountFull()
{
	cout<<"Name: "<<Name<<endl;
	cout<<"AccountID#: "<<UserID<<endl;
	if (myBooks.size()==0)
	{
		 cout<<"No books checked out."<<endl;
	}
	else
	{
		cout<<myBooks.size()<<" books checked out."<<endl;
		int x=1;
		for(auto it = myBooks.begin();it!= myBooks.end(); ++it) 
		{
			cout<<"\t"<<x<<". "<<endl;
			myBooks[it->first]->PrintBookDataFullIndent();
			x++;
		}
	}	
}
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
//Returns a string of an account info and boos in file line format
string Account::outputAccount()
{	//collects all user info in file format
	string a=to_string(UserID)+"|"+Name+"|"+to_string(myBooks.size())+"\n";
	for (auto it = myBooks.begin(); it !=myBooks.end() ; ++it)
	{
		a+=it->second->outputCheckedoutBooks();	
	}
	return a;
}
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
//Prints partial account info
void Account::printPartialBook(int BookID)
{
	cout<<"Borrower AccountID#: "<<UserID<<endl;
	cout<<"Due Date: "<<myBooks[BookID]->getDueDate()<<endl;
	cout<<"Times Renwed: "<<myBooks[BookID]->getRenewed()<<endl;
	if (myBooks[BookID]->is_Overdue())
	{
		cout<<"OVERDUE"<<endl;
	}
	
}
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
//Return book back to library
void Account::returnBook(int BookID)
{
	//If user has the book with given ID
	//Remove it from Booklist, reset its info, and change its status to Available
	//Print timing info
	if (hasBook(BookID))
	{
		Book* returnBook=myBooks[BookID];
		Remove(BookID);
		cout<<"Book successfully returned by AccountID# "<<UserID;
		if(returnBook->is_Overdue())
		{
			cout<<" (overdue by "<<Time::getTime()-returnBook->getDueDate()<<" days)."<<endl;
		}
		else
		{
			cout<<" (on time)."<<endl;
		}
	}
	else
	{
		cout<<"Book is not currently checked out."<<endl;
	}
}
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
//returns true if any books are overdue
bool Account::hasOverdueBooks()
{
	for(auto it = myBooks.begin();it!= myBooks.end(); ++it) 
	{
		if(it->second->is_Overdue())
		{	
			return true;
		}		
	}
return false;
}
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
//return true if use has book
bool Account::hasBook(int BookID)
{
	return (myBooks.find(BookID)!=myBooks.end());
}
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
//returns userid
int Account::getUserID() const
{
	return UserID;
}
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
//retruns name
string Account::getName() const
{
	return Name;
}
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
//return number of books
int Account::getCheckouts() const
{
	return myBooks.size();
}

#endif