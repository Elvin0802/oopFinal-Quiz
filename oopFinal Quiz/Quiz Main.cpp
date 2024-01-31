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
string Folder = "txt Files/";
string Users = "Users.txt";
string QuizNames = "Quiz Names.txt";
string Players = "Players.txt";
/*--------------------------------------------------*/


/*--------------------------------------------------*/
string gUserName = "";
/*--------------------------------------------------*/  

/*******  Application Headers  ********/

#include "Exception Classes.h"
#include "System Functions.h"
#include "User System.h"
#include "Question Classes.h"
#include "Quiz Classes.h"
#include "Quiz Functions.h"
#include "Registration System.h"
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
			SetColor(4);
			cout << except.what();
			SetColor(dft);
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
			SetColor(4);
			cout << except.what();
			SetColor(dft);
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