#include <iostream>
#include <Windows.h>
#include <algorithm>
#include <vector>
#include <list>
#include <random>
#include <string>
#include <fstream>
#include <conio.h>
#include <memory>

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


/*--------------------------------------------------*/
string gUserName = ""; // for Save player to file.
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


void main()
{
	LoadingScreen("Loading", 35);

	while (true)
	{
		string Level;

		try
		{
			Level = Login_Menu();
		}
		catch (exception& except)
		{
			SetColor(4); cout << except.what();
			SetColor(dft); Pause();
		}
		//------------------------------------------------------
		try
		{
			if (Level == "__admin__")
			{
				Main_Menu(true);
			}
			else if (Level == "__guest__")
			{
				Main_Menu(false);
			}
			else if (Level == "__break__")
			{
				LoadingScreen("Exiting", 35);
				break;
			}
		}
		catch (Exception& except)
		{
			SetColor(4); cout << except.Get_Message(); Pause();
		}
		catch (exception& except)
		{
			SetColor(4); cout << except.what(); Pause();
		}
	}
}