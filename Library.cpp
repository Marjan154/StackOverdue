#ifndef LIBRARY_CPP
#define LIBRARY_CPP
#include <iostream>
#include <string>
#include "Library.h"
using namespace std;
//Constructor reads files and fills up LibraryOfBooks and Users
Library::Library(string BookFile, string AccountFile)
{
	//If only bookfile is provided, read book file, output message
	if (BookFile!="" and AccountFile=="")
	{
		cout<<"No accounts file provided."<<endl;
		BookList myBooks(BookFile);
		LibraryOfBooks= myBooks;
	}
	//If no files provided, run program
	else if(AccountFile=="" and BookFile=="")
	{
		cout<<"No books provided."<<endl;
		cout<<"No accounts provided."<<endl;
		BookList myBooks;
		AccountList myAccounts;
		LibraryOfBooks= myBooks;
		Users= myAccounts;
	}
	//If both files provided, read both of them and initialize AccountList and Booklist vars
	else
	{
		cout<<"Loading books from \""<<BookFile<<"\"."<<endl;
		cout<<"Loading accounts from \""<<AccountFile<<"\"."<<endl;
		BookList myBooks(BookFile);//reads file
		LibraryOfBooks= myBooks;
		AccountList myAccounts(AccountFile, LibraryOfBooks);//reads file
		Users= myAccounts;
		initialSize=LibraryOfBooks.getSize();
	}
}
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
//Recieves a book back 
void Library::recieveBook(int BookID)
{
	if(!LibraryOfBooks.findBook(BookID)->getCheckedOutStatus())
	{
		cout<<"Book is currently not checked out."<<endl;
	}
	else if (LibraryOfBooks.hasBook(BookID))
	{
		int BorrowerID=LibraryOfBooks.findBook(BookID)->getBorrowerID();
		Account* Borrower=Users.findAccount(BorrowerID);
		Borrower->returnBook(BookID);
		LibraryOfBooks.findBook(BookID)->refresh();
	}
	else
	{
		cout<<"BookID# "<<BookID<<" not found."<<endl;
	}		
}
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
//Adds book given title, author and genre
void Library::addBook(string title, string author, string genre)
{
	LibraryOfBooks.AddBook(title,author,genre);
}
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
//Give book with given id to and account with given id
void Library::giveBook(int AccountID, int BookID)
{
	//CHeck if book exists
	if(!LibraryOfBooks.hasBook(BookID))
	{
		cout<<"BookID# "<<BookID<<" not found."<<endl;
	}
	//if it does continue
	else
	{	//Check if available, or acount exists, then
		//if it has overdue books or already checked out more than 10 
		if(LibraryOfBooks.findBook(BookID)->getCheckedOutStatus()==1)
		{
			cout<<"Book is already checked out."<<endl;
		}
		else if(!Users.hasAccount(AccountID))
		{
			cout<<"AccountID# "<<AccountID<< " not found."<<endl;
		}
		else if (Users.findAccount(AccountID)->hasOverdueBooks())
		{
			cout<<"Account has books overdue."<<endl;
		}
		else if(Users.findAccount(AccountID)->getCheckouts()>=10)
		{
			cout<<"Account already has 10 books checked out."<<endl;
		}
		//If passed all rules, checkout
		else
		{
			Users.AddBookToAccount(AccountID, LibraryOfBooks.TakeBookFromLibrary(BookID));
			cout<<"Book successfully checked out."<<endl;
			LibraryOfBooks.PrintBook(BookID);
			Users.findAccount(AccountID)->printPartialBook(BookID);
		}
	}
}
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
//Renews book if possible
void Library::RENEW(int AccountID)
{
	//if user exists,a dn has no overdue books, renew it
	if(Users.hasAccount(AccountID))
	{	
		if (Users.findAccount(AccountID)->hasOverdueBooks())
		{
			cout<<"Account has books overdue."<<endl;
		}
		else
		{
			Users.findAccount(AccountID)->renewBooks();
		}
	}
	else
	{
		cout<<"AccountID# "<<AccountID<< " not found."<<endl;
	}	
}
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
//Prints book info
void Library::PrintBook(int ID)
{
	if (LibraryOfBooks.hasBook(ID))
	{
		Account* temp=new Account;
		LibraryOfBooks.PrintBook(ID);
		if (LibraryOfBooks.findBook(ID)->getCheckedOutStatus()==1)
		{
			int BorrowerID=LibraryOfBooks.findBook(ID)->getBorrowerID();
			temp=Users.findAccount(BorrowerID);	
			temp->printPartialBook(ID);	
		}
		else
		{
			cout<<"AVAILABLE"<<endl;
		}
	}
	else
	{
		cout<<"BookID# "<<ID<<" not found."<<endl;
	}		
}
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
//searches for book based on criteria and search phrase
void Library::searchBook(string criteria, string item)
{
	LibraryOfBooks.search(criteria, item);	
}
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
//Permanently removes book from Library
void Library::removeBook(int BookID)
{
	//If book is checked out, force return it.
	if(LibraryOfBooks.hasBook(BookID))
	{
		if (LibraryOfBooks.findBook(BookID)->getCheckedOutStatus())
		{
			cout<<"Force returning book from AccountID# "<<LibraryOfBooks.findBook(BookID)->getBorrowerID()<<"."<<endl;
			ForceReturn(BookID);
		}
		cout<<"\""<<LibraryOfBooks.findBook(BookID)->getTitle()<<"\" by "<<
		LibraryOfBooks.findBook(BookID)->getAuthor()<<" successfully removed."<<endl;
		LibraryOfBooks.removeBook(BookID);
	}
	else
	{
		cout<<"BookID# "<<BookID<<" not found";	
	}
}
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
//Checks if book exists
bool Library::contains(string name, string author)
{
	return LibraryOfBooks.contains(name,author);
}
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
//Force return books
void Library::ForceReturn(int BookID)
{
	int BorrowerID=LibraryOfBooks.findBook(BookID)->getBorrowerID();
	Account* Borrower=Users.findAccount(BorrowerID);
	Borrower->Remove(BookID);
}
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
//Prints book selection ordered by criteria
void Library::browse(string criteria)
{
	LibraryOfBooks.Browse(criteria);
}
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
//adds account to library given a name
void Library::addAccount(string name)
{
	Users.AddAccount(name);
}
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
//Remove account from Library given id
void Library::removeAccount(int UserID)
{
	if (Users.hasAccount(UserID))
	{
		Users.removeAccount(UserID);
	}
	else
	{
		cout<<"AccountID# "<<UserID<<" not found."<<endl;
	}	
}
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
//Prints all Accounts
void Library::printAccounts(string criteria)
{
	Users.PrintAll(criteria);
}
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
//Prints recommendations of Account with UserID
void Library::RECOMMEND(int UserID)
{	//if account exists, recommend
	if (Users.hasAccount(UserID))
	{
		Account* account=Users.findAccount(UserID);
		account->Recommend(LibraryOfBooks);
	}
	else
	{
		cout<<"AccountID# "<< UserID<< " not found."<<endl;
	}	
}
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
//Prints user info
void Library::printUserInfo(int ID)
{	//if user exists, print info
	if (Users.hasAccount(ID))
	{
		Users.printUserInfo(ID);
	}
	else
	{
		cout<<"AccountID# "<< ID<< " not found."<<endl;
	}
}
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
//Exports book and account info into files
void Library::Export(string bookFileName, string accountsFileName)
{
	LibraryOfBooks.outputBooks(bookFileName);
	Users.OutputAccounts(accountsFileName);
	cout<<"Books data successfully exported to \""<<bookFileName<<"\"."<<endl;
	cout<<"Accounts data successfully exported to \""<<accountsFileName<<"\"."<<endl;
}
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
//Prints system info
void Library::System()
{
	cout<<"System time: "<<Time::getTime()<<endl;
	cout<<"Number of books: "<<LibraryOfBooks.getSize()<<endl;
	cout<<"Number of overdue books: "<<LibraryOfBooks.OverdueBooksCount()<<endl;
	cout<<"Number of accounts: "<<Users.getSize()<<endl;
	cout<<"Number of overdue accounts: "<<Users.OverdueAccounts()<<endl;
}
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
//Prints help
void Library::HELP()
{
	cout<<"BROWSE: Provides the status of all the books."<<endl;
	cout<<"BOOK: Provides the status of a specific book."<<endl;
	cout<<"SEARCH: Searches for all books with a key-phrase in the title or author."<<endl;
	cout<<"ACCOUNTS: Provides account snapshots for all user accounts."<<endl;
	cout<<"ACCOUNT: Provides an account snapshot for a specific user account."<<endl;
	cout<<"CHECKOUT: Checks a book out to a user account."<<endl;
	cout<<"RENEW: Renews a checked out book. (Up to two times allowed)"<<endl;
	cout<<"RETURN: Returns a checked out book."<<endl;
	cout<<"RECOMMEND: Generates a list of recommended books for a given user."<<endl;
	cout<<"ADDB: Adds a new book to the library."<<endl;
	cout<<"REMOVEB: Removes a specific book from the library."<<endl;
	cout<<"ADDA: Creates a new user account in the library."<<endl;
	cout<<"REMOVEA: Removes a specific user account from the library."<<endl;
	cout<<"SYSTEM: Provides diagnostic information about the system."<<endl;
	cout<<"TIME: Fast forwards the system time by a specified number of days."<<endl;
	cout<<"EXPORT: Exports the library’s books and accounts to files."<<endl;
	cout<<"HELP: Displays this help menu."<<endl;
	cout<<"EXIT: Exits the program."<<endl;
}
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

#endif