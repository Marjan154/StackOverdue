#ifndef ACCOUNTLIST_CPP
#define ACCOUNTLIST_CPP	
#include <fstream>
#include <string>
#include "Account.h"
#include "AccountList.h"
#include <map>
#include <unordered_map>
using namespace std;


//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
//Reads file and inserts data
AccountList::AccountList(string AccountsFile, BookList myLib)
{
	//check if file exists
	highestID=0;
	vector<string> Accounts;
	unsigned int numbooks;
	ifstream AccountFile;
	string AccountData;
	AccountFile.open(AccountsFile);
	if (!AccountFile.is_open())
	{
		cout<< "Could not find file "<<AccountsFile<<". Skipping."<<endl;
	}
	//If it does, read file, split by | until number of checkouts lines +1
	//and push into a vector. Add the account
	getline(AccountFile, AccountData);
	while(!AccountFile.eof())
	{
		while(getline(AccountFile,AccountData))
		{
			stringstream ss(AccountData);
			while(getline(ss, AccountData, '|'))//split line by |
			{
				Accounts.push_back(AccountData);
				if (Accounts.size()>=3)//After User info is added
				{
					if (highestID<atoi(Accounts[0].c_str()))//tracks maxid
					{
						highestID=atoi(Accounts[0].c_str());
					}
					numbooks=atoi(Accounts[2].c_str());	
					if(Accounts.size()==((numbooks+1)*3))//Continues until all books found
					{
					  	Account* myAccount= new Account(Accounts, myLib);					  		
				  		AddAccount(myAccount); 		
			  	  		Accounts.clear();			  	
					} 
				}					
			}
		}	
	}
AccountFile.close();	
}
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
//Inserts accounts
void AccountList::AddAccount(Account* someAccount)
{
	ListOfAccounts.insert(std::pair<int,Account*>(someAccount->getUserID(),someAccount));
}
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
//Adds new account with given name
void AccountList::AddAccount(string name)
{
	
	std::map<int,Account*>::const_iterator it;
	int newID=highestID+1;
	highestID++;
	Account* someAccount= new Account(name, newID);
	ListOfAccounts.insert(std::pair<int,Account*>(newID,someAccount));
	cout<<"AccountID#"<<newID<< " successfully created."<<endl;
}
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
//deletes account
void AccountList::removeAccount(int AccountID)
{	//checks if user has books, and force returns them before deleting.
	if (ListOfAccounts[AccountID]->getCheckouts()>0)
	{
		ListOfAccounts[AccountID]->forceRemoveBooks();
	}
	cout<<ListOfAccounts[AccountID]->getName()<<"'s account successfully removed."<<endl;
	ListOfAccounts.erase(AccountID);
}
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
//Add book to specific account
void AccountList::AddBookToAccount(int UserID, Book* Book)
{
		ListOfAccounts[UserID]->CheckoutBook(Book);
}
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
//print info if Id exist
void AccountList::printUserInfo(int ID)
{
	//check if user exists, and prints if user does
	if (ListOfAccounts.find(ID)!=ListOfAccounts.end())
	{
		ListOfAccounts[ID]->printAccountFull();
	}
	else
	{
		cout<<"AccountID# "<<ID<<" not found."<<endl;
	}
}
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
//print all accounts
void AccountList::PrintAll(string criteria)
{
	if (criteria=="name" or criteria=="accountid" or criteria=="checkouts")
	{
		vector<Account*> AccountsToSort=order(criteria);
		for (unsigned int i = 0; i < AccountsToSort.size(); ++i)
		{
			cout<<i+1<<". ";
			AccountsToSort[i]->printAccount();
		}
	}
	else
	{	
		cout<<"Invalid value."<<endl;
	}
}
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
//Output file with account data
void AccountList::OutputAccounts(string accountsfile)
{
	ofstream sendfile;			
	sendfile.open(accountsfile);
	if (ListOfAccounts.size()>0)
	{
		sendfile<<ListOfAccounts.size()<<endl;
	}		
	for (auto it = ListOfAccounts.begin(); it !=ListOfAccounts.end() ; ++it)
	{
		sendfile << it->second->outputAccount();
	}
	sendfile.close();
}
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
//returns account with userid
Account* AccountList::findAccount(int UserID)
{
	return ListOfAccounts[UserID];
}
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
//retruns number od Overdue accounts
int AccountList::OverdueAccounts()
{
	int count;
	for (auto it = ListOfAccounts.begin(); it !=ListOfAccounts.end() ; ++it)
	{
		if (it->second->hasOverdueBooks())
		{
			count++;
		}
	}
	return count;
}
// //%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
//Order Accounts by criteria
vector<Account*> AccountList::order(string criteria)
{	
	//copy accountss into a vector, sort using vector sort function, and a cpmarator
	vector<Account*> AccountsToSort;
	for (auto  it = ListOfAccounts.begin(); it!=ListOfAccounts.end() ; ++it)
	{
		AccountsToSort.push_back(it->second);
	}

	if (criteria=="name")
	{
		sort (AccountsToSort.begin(), AccountsToSort.end(), [](Account* const &a, Account* const &b) { return a->getName() < b->getName(); });
	}
		
	if (criteria=="accountid")
	{
		sort (AccountsToSort.begin(), AccountsToSort.end(), [](Account* const &a, Account* const &b) { return a->getUserID() < b->getUserID(); });
	
	}

	if(criteria=="checkouts")
	{
		sort (AccountsToSort.begin(), AccountsToSort.end(), [](Account* const &a, Account* const &b) { return a->getCheckouts() > b->getCheckouts(); });
		
	}

return AccountsToSort;
}
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
//Check if account exists
bool AccountList::hasAccount(int ID)
{
	return (ListOfAccounts.find(ID)!=ListOfAccounts.end());
}
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
#endif