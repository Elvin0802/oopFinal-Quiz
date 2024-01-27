#include <iostream>
#include <list>
#include <vector>
#include <conio.h>
#include <Windows.h>
#include <string>
#include <fstream>
#include <algorithm>
#include <memory>
#include <random>

using namespace std;
/*-----------------------------------------------------------------------*/

#define dft 15  // default value for change (set) Color
HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE); // for change (set) Color

/*--------->>  App File Destinations  <<-----------*/
string txt = ".txt";
string AppFolder = "APP txt Files/";
string AppUsers = "Users.txt";
string AppQuizNames = "Quiz Names.txt";
string AppQuizPlayers = "Quiz Players.txt";
/*--------------------------------------------------*/




/*******  Application Headers  ********/

#include "Exception Classes.h"
#include "System Functions.h"
#include "User System.h"
#include "Question Classes.h"
#include "Quiz Classes.h"
#include "Out of Classes.h"
#include "Registration System.h"
#include "Quiz Functions.h"
/*-----------------------------------------*/

//     throw InvalidArgumentException("\n Text ", GetTime(), __FILE__, __LINE__);  // Error atmaq uchun values


void main()
{
	while (true)
	{
		string Level;

		try
		{
			Level = Login_Menu();
		}
		catch (exception& except)
		{
			SetConsoleTextAttribute(h, 4);
			cout << except.what();
			SetConsoleTextAttribute(h, dft);
			system("pause");
		}
		//------------------------------------------------------
		try
		{
			if (Level == "__admin__")
			{
				Admin_Menu();
			}
			else if (Level == "__guest__")
			{
				Guest_Menu();
			}
			else if (Level == "__break__")
			{
				break;
			}
		}
		catch (exception& except)
		{
			SetConsoleTextAttribute(h, 4);
			cout << except.what();
			SetConsoleTextAttribute(h, dft);
			system("pause");
		}
	}



}







/*

 // Print the words using a for each loop

	cout << "Words in the list (using for each loop):" << endl;

	for (const string& word : my_list)
	{
		cout << word << " ";
	}

	cout << endl;

	----------------------------------------------------------------------------------

	// Print the words using a list iterator

	cout << "Words in the list (using list iterator):" << endl;

	for (list<string>::iterator it = my_list.begin(); it != my_list.end(); ++it)
	{
		cout << *it << " ";
	}

	cout << endl;

*/