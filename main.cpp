
#include "LibrarySimulation.h"
#include <iostream>
using namespace std;


int main(int argc, char* argv[])

{
	if (argc==3)//2 files
	{
		LibrarySimulation StackOverdue(argv[1], argv[2]);
		StackOverdue.UseSystem();
	}

	else if(argc==2)//1 file
	{
	  	LibrarySimulation StackOverdue(argv[1], "");
	  	StackOverdue.UseSystem();
 	}

 	else//no files
 	{
 		LibrarySimulation StackOverdue("", "");
 		StackOverdue.UseSystem();
 	}
 		
return 0;
}