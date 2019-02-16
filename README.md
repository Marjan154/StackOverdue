Author: Marjan Ansar 
Course: {235} 
Instructor: Simon Ayzman 
Assignment: Assignment 3 - StackOverdue

--------------------------------------------------------------------------------------------------------
BACKGROUND:

This program acts as a Library interface that allows users to create accounts, or use their existing accounts to checkout books, renew them,
return them, etc. The system can export all books an accounts info in file format,
report its system info, and can control number of days in the Library. 

-------------------------------------------------------------------------------------------------------------

COMPILATION/EXECUTION INSTRUCTIONS:

Compile the program with:
make

The program can then take two, one, or no arguments in the exact forms of:
1) ./StackOverdue booksfile accountsfile
2) ./StackOverdue booksfile 
3) ./StackOverdue 

The ordering of the arguments are exact.If a provided file does not exist, it is skipped over. Any of the files under data folder are valid files and can be used to run this program.
For example:

a) ./StackOverdue data/library.small/books.data data/library.small/accounts.data

b) ./StackOverdue data/library.large/books.data


The following commands can be used on the program interface. Commands are case sensetive, meaning BROWSE is not the same as browse or bRowsE. An error message will display if an invalid command or criteria is inputted.

BROWSE: Provides the status of all the books.

BOOK: Provides the status of a specific book.

SEARCH: Searches for all books with a key-phrase in the title or author.

ACCOUNTS: Provides account snapshots for all user accounts.

ACCOUNT: Provides an account snapshot for a specific user account.

CHECKOUT: Checks a book out to a user account.

RENEW: Renews a checked out book. (Up to two times allowed)

RETURN: Returns a checked out book.

RECOMMEND: Generates a list of recommended books for a given user.

ADDB: Adds a new book to the library.

REMOVEB: Removes a specific book from the library.

ADDA: Creates a new user account in the library.

REMOVEA: Removes a specific user account from the library.

SYSTEM: Provides diagnostic information about the system.

TIME: Fast forwards the system time by a specified number of days.

EXPORT: Exports the library’s books and accounts to files.

HELP: Displays this help menu.

EXIT: Exits the program.


------------------------------------------------------------------------------------------------------------------------




DESIGN DESCRIPTION:

Book
-Represents a book, that has Title, Author, Genre, Popularity Score, Due date, and a borrower id. Books also have overdue and checkout statuses.

Booklist
-Acts as  a books manager class and holds a library of books. Books can be added, removed, renewed, etc.

Account
-Represents the account of a user. Users can check out books, return books, find reccomendations, etc in their accounts.

AccountList
-Acts as accounts manager class. Has a data structure that hold multiple accounts, or all of the accounts in the Library system.

Library
-Holds a BookList and Accountlist and manages the interaction between them. Can print out all the books and account informations.

LibrarySimulator
-Asks for user input and outputs results based on those commands, until the user exits the system.

Time
-Contains static variables and functions to control the time of the entire program. Time can be travelled by a valid (positive or whole) number of days.


