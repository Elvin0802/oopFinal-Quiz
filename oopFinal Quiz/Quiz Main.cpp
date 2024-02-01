#include <iostream>
#include <Windows.h>
#include <vector>
#include <list>
#include <string>
#include <fstream>
#include <algorithm>
#include <conio.h>
#include <memory>
#include <random>

using namespace std;
/*-----------------------------------------------------------------------*/

#define dft 15  // default value for change (set) Color
HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE); // for change (set) Color

/*--------->>  App File Destinations  <<-----------*/
string txt = ".txt";
string Folder = "txt Files/";
string QuizFolder = "Quiz-ler/";
string Users = "Users.txt";
string QuizNames = "Quiz Names.txt";
string Players = "Players.txt";
/*--------------------------------------------------*/


/*-------------------------*/
string gUserName = ""; // for Save player to file.
/*-------------------------*/  

/*******  Application Headers  ********/

#include "Exception Classes.h"
#include "System Functions.h"
#include "User System.h"
#include "Question Classes.h"
#include "Quiz Classes.h"
#include "Quiz Functions.h"
#include "Registration System.h"
/*-----------------------------------------*/


void main()
{
	LoadingScreen("Loading",50);

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
				LoadingScreen("Exiting", 35);
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
