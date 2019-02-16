#ifndef LIBRARYSIMULATION_CPP
#define LIBRARYSIMULATION_CPP
#include <iostream>
#include <string>
#include "LibrarySimulation.h"
using namespace std;

//Reads file, inputs data
LibrarySimulation::LibrarySimulation(string bookfile, string accountfile)
{		
	Library newLibrary(bookfile, accountfile); 
	StackOverdue=newLibrary;
}
//Keeps asking for commands until user EXIT's
void LibrarySimulation::UseSystem()
{
	string input;
	while(1)
	{
		cout<<">";
		string input;
		cin>>input;
		if (input=="EXIT")
		{
			cout<<"Thank you for using StackOverdue!"<<endl;
			break;
		}
		BeginSimulation(input);
		cout<<endl;
	}
}

//Takes user command
void LibrarySimulation::BeginSimulation(string input)
{	//Checks if books exist, and outputs accordingly
	if (input=="BROWSE")
	{
		if (StackOverdue.getLibrarySize()>0)
		{
			string criteria;
			cout<<"Enter the criteria to sort by.(title/author/genre/bookid/popularity)"<<endl;
			cout<<">";
			cin>>criteria;
			//checks if criteria is appripriate
			if (criteria=="title" or criteria=="author" or criteria=="genre"
				or criteria=="bookid" or criteria=="popularity")
			{
				StackOverdue.browse(criteria);
			}
			else
			{
				cout<<"Invalid value."<<endl;
			}
		}
		else
		{
			cout<<"No books in your library."<<endl;
		}
	}
	//Checks if books exist, and outputs accordingly
	else if (input=="BOOK")
	{
		if (StackOverdue.getLibrarySize()>0)
		{
			int BookID;
			cout<<"Enter the book id."<<endl;
			cout<<">";
			cin>>BookID;
			StackOverdue.PrintBook(BookID);
		}
		else
		{
			cout<<"No books in your library."<<endl;
		}
		
	}
	//Checks if books exist, and outputs accordingly
	else if (input=="SEARCH")
	{
		if (StackOverdue.getLibrarySize()>0)
		{
			string searchby;
			string searchitem;
			cout<<"Enter the criteria to search by.(title/author)"<<endl;
			cout<<">";
			cin>>searchby;
			//check if criteria
			if (searchby=="author" or searchby=="title")
			{
				cout<<"Enter the search phrase."<<endl;
				cin.clear();
				cin.ignore();
				cout<<">";
				getline(cin,searchitem);
				StackOverdue.searchBook(searchby, searchitem);	
			}
			else
			{
				cout<<"Invalid value."<<endl;
			}
		}
		else
		{
			cout<<"No books in your library."<<endl;
		}
	}
	//Checks if accounts exist, and outputs accordingly
	else if (input=="ACCOUNTS")
	{
		
		if (StackOverdue.getAccountsSize()>0)
		{
			string criteria;
			cout<<"Enter the criteria to sort by.(name/accountid/checkouts)"<<endl;
			cout<<">";
			cin>>criteria;
			//check if valid criteria
			if (criteria=="name" or criteria=="accountid" or criteria=="checkouts")
			{
				StackOverdue.printAccounts(criteria);
			}
			else
			{
				cout<<"Invalid value."<<endl;
			}
		}
		else
		{
			cout<<"No accounts in your library."<<endl;
		}

	}
	//Checks if accounts exist, and outputs accordingly
	else if (input=="ACCOUNT")
	{
		if (StackOverdue.getAccountsSize()>0)
		{
			int UserID;
			cout<<"Enter the account id. "<<endl;
			cout<<">";
			cin>>UserID;
			StackOverdue.printUserInfo(UserID);
		}
		else
		{
			cout<<"No accounts in your library."<<endl;
		}
	}
	//Checks if accounts exist, and outputs accordingly
	else if (input=="CHECKOUT")	
	{
		if (StackOverdue.getAccountsSize()>0)
		{
			int BookID;
			int UserID;
			cout<<"Enter the account id."<<endl;
			cout<<">";
			cin>>UserID;
			cout<<"Enter the book id."<<endl;
			cout<<">";
			cin>>BookID;
			StackOverdue.giveBook(UserID, BookID);
		}
		else
		{
			cout<<"No accounts in your library."<<endl;
		}
	}
	//Checks if accounts exist, and outputs accordingly
	else if (input=="RENEW")
	{
		if (StackOverdue.getAccountsSize()>0)
		{
			int UserID;
			cout<<"Enter the account id."<<endl;
			cin>>UserID;
			StackOverdue.RENEW(UserID);
		}
		else
		{
			cout<<"No accounts in your library."<<endl;
		}
	}
	//Checks if accounts exist, and outputs accordingly
	else if (input=="RETURN")
	{
		if (StackOverdue.getAccountsSize()>0)
		{
			int BookID;
			cout<<"Enter the book id."<<endl;
			cout<<">";
			cin>>BookID;
			StackOverdue.recieveBook(BookID);
		}
		else
		{
			cout<<"No accounts in your library."<<endl;
		}
	}
	//Checks if accounts exist, and outputs accordingly
	else if (input=="RECOMMEND")
	{	
		if (StackOverdue.getAccountsSize()>0)
		{
			int UserID;
			cout<<"Enter the account id."<<endl;
			cout<<">";
			cin>>UserID;
			StackOverdue.RECOMMEND(UserID);
		}
		else
		{
			cout<<"No accounts in your library."<<endl;
		}
	}

	else if(input=="ADDB")
	{
		string title;
		string author;
		string genre;
		cout<<"Enter the new book's title."<<endl;
		cin.clear();
		cin.ignore();
		cout<<">";
		getline(cin, title);
		cout<<"Enter the new book's author."<<endl;
		cout<<">";
		getline(cin, author);
		//Check if book already exists.If not add. Else, print error.
		if (StackOverdue.contains(title,author))
		{
			cout<<"Book with this title and author already exists."<<endl;
		}
		else
		{
			cout<<"Enter the new book's genre."<<endl;
			getline(cin, genre);
			StackOverdue.addBook(title, author, genre);
		}

	}
	//Checks if books exist, and outputs accordingly
	else if(input=="REMOVEB")
	{	
		if (StackOverdue.getLibrarySize()>0)
		{
			int BookID;
			cout<<"Enter the book id."<<endl;
			cout<<">";
			cin>>BookID;
			StackOverdue.removeBook(BookID);
		}
		else
		{
			cout<<"No books in your library."<<endl;
		}
	}
	else if(input=="ADDA")
	{
		string name;
		cout<<"Enter the user's name. "<<endl;
		cin.clear();
		cin.ignore();
		cout<<">";
		getline(cin,name);
		StackOverdue.addAccount(name);

	}

	else if(input=="REMOVEA")
	{
		if (StackOverdue.getAccountsSize()>0)
		{
			int UserID;
			cout<<"Enter the account id."<<endl;
			cout<<">";
			cin>>UserID;
			StackOverdue.removeAccount(UserID);
		}
		else
		{
			cout<<"No accounts in your library."<<endl;
		}	
	}

	else if(input=="SYSTEM")
	{
		StackOverdue.System();
	}

	else if(input=="TIME")
	{
		Time::timeJump();
	}

	else if(input=="EXPORT")
	{
		string bookfile;
		string accountfile;
		cout<<"Enter the name for the books file. (This may overwrite a file)"<<endl;
		cin>>bookfile;
		cout<<"Enter the name for the accounts file. (This may overwrite a file)"<<endl;
		cin>>accountfile;
		StackOverdue.Export(bookfile,accountfile);
	}

	else if(input=="HELP")
	{
		StackOverdue.HELP();
	}
	else
	{
		cout<<"Invalid command."<<endl;
	}
}


#endif