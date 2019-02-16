#ifndef ACCOUNTLIST_H
#define ACCOUNTLIST_H	
#include <fstream>
#include <string>
#include "Account.h"
#include "BookList.h"
#include <map>
#include <sstream>
#include <unordered_map>
using namespace std;

class AccountList
{
public:

	AccountList(){};
	//Reads file and inserts data
	AccountList(const string AccountsFile, BookList myLib); 
	//Adds account
	void AddAccount(string Name);
	//Adds account
	void AddAccount(Account* someAccount);
	//Removes account with ID
	void removeAccount(int AccountID);
	//Add given book to account with given ID
	void AddBookToAccount(int UserID, Book* Book);
	//void checkBookAvailability(int ID);
	//Print user info with ID
	void printUserInfo(int ID);
	//Print aAll user info
	void PrintAll(string criteria);
	//Orders Accounts by criteria
	vector<Account*> order(string criteria);
	//returns account with id
	Account* findAccount(int UserID);
	//Prints out how many overdue accounts
	int OverdueAccounts();
	//retruns number of Accounts
	int getSize(){return ListOfAccounts.size();}
	//Outputs accounts into a file in format
	void OutputAccounts(string accountsfile);
	//check if account with ID exists
	bool hasAccount(int ID);

private:
	unordered_map <int, Account*> ListOfAccounts;
	int highestID;

};

#endif