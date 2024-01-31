#pragma once


// Get Current Time in Text (string).
string GetTime()
{
	time_t now;
	time(&now);

	char* dt = new char[26];

	ctime_s(dt, 26, &now);

	return string(dt);
}

// Change Choice for vector index with keyboard buttons.
int KeyCheck(int key, int choice, int min, int max)
{
	if (key == 72) {
		choice--;
		if (choice < min) choice = max;
	}
	else if (key == 77) {
		choice--;
		if (choice < min) choice = max;
	}
	else if (key == 75) {
		choice++;
		if (choice > max) choice = min;
	}
	else if (key == 80) {
		choice++;
		if (choice > max) choice = min;
	}
	else if (key == 119) {
		choice--;
		if (choice < min) choice = max;
	}
	else if (key == 97) {
		choice++;
		if (choice > max) choice = min;
	}
	else if (key == 115) {
		choice++;
		if (choice > max) choice = min;
	}
	else if (key == 100) {
		choice--;
		if (choice < min) choice = max;
	}

	return choice;
}

// Change Console Text Color.
void SetColor(int color)
{
	SetConsoleTextAttribute(h, color);
}

// Save Quiz Name To DataBase (File).
void SaveQuizNameToDB(string dbName, string qName)
{
	ofstream file(dbName, ios::app);

	if (!file.is_open() || !file)
	{
		throw Exception("\nFile Achilmadi.", GetTime(), __FILE__, __LINE__);
	}

	file << "--> " << qName << endl;

	file.close();
}

// Get Quiz Names From DataBase (File).
auto GetQuizNamesFromDB(string dbName)
{
	ifstream file(dbName, ios::in);

	if (!file.is_open())
	{
		throw Exception("\nFile Achilmadi.",
			GetTime(), __FILE__, __LINE__);
	}
	vector<string> quizNames;

	string index = "", q_name = "";

	while (!file.eof())
	{
		file >> index;
		if (!file.eof())
		{
			file >> q_name;
			quizNames.push_back(q_name);
		}
	}
	file.close();
	return quizNames;
}

// Show Vector Menu Elements with Colored Choose.
void ShowMenu_v(int Choose, const vector<string>& Vector, int _ignore = -1)
{
	size_t end = Vector.size();

	cout << endl << endl;
	for (size_t sl = 0; sl < end; sl++)
	{
		if (sl == _ignore)
			continue;

		if (Choose == sl)
		{
			SetConsoleTextAttribute(h, 3);
			cout << "\n\t\t" << Vector[sl] << endl;
			SetConsoleTextAttribute(h, dft);
		}
		else
			cout << "\n\t\t" << Vector[sl] << endl;
	}
}




//		Lazimsizdi.  Silersen.

// 
//// Show List Menu Elements with Colored Choose.
//void ShowMenu_v(string Choose, const list<string>& List)
//{
//	for (auto str : List)
//	{
//		if (str == Choose)
//		{
//			SetConsoleTextAttribute(h, 3);
//			cout << "\t\t" << str << endl;
//			SetConsoleTextAttribute(h, dft);
//		}
//		else
//			cout << "\t\t" << str << endl;
//	}
//}