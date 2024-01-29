#pragma once


void Admin_Menu()
{
	int key2, choose2 = 0;
	vector<string> menuForAdmin{ " Create New Quiz ", " Start Quiz " ," Show My Score " ," Leaders Board "," Exit " };

	while (true)
	{
		system("cls");
		ShowMenu_v(choose2, menuForAdmin);

		key2 = _getch();
		if (key2 > 96)
		{
			if (key2 == 224)key2 = _getch();
			choose2 = KeyCheck(key2, choose2, 0, (menuForAdmin.size() - 1));
		}
		else if (key2 == 13)
		{
			if (choose2 == 0)
			{
				string quiz_name;

				SetColor(8);
				cout << "\n\t >>>> Quiz Adini Daxil Edin : "; getline(cin, quiz_name);
				SetColor(dft);

				Quiz* newQuiz = new Quiz(quiz_name);

				int key3, choose3 = 0;
				vector<string> menuForAdd{ " Add New Question ", " Back to Menu ", " Save and Exit " };

				while (true)
				{
					system("cls");
					ShowMenu_v(choose3, menuForAdd);

					key3 = _getch();
					if (key3 > 96)
					{
						if (key3 == 224)key3 = _getch();
						choose3 = KeyCheck(key3, choose3, 0, (menuForAdd.size() - 1));
					}
					else if (key3 == 13)
					{
						if (choose3 == 0)
						{
							string question = "", answer1 = "", answer2 = "", answer3 = "", answer4 = "";
							string correctAnswer = "";

							system("cls"); SetColor(7);
							cout << "\n\n\t\t---)  Sual  > " << (newQuiz->Get_QuestionCount() + 1) << " < \n";
							SetColor(dft);

							cout << "\n---  Suali Daxil Edin :: "; getline(cin, question);

							cout << "\n---  I Cavabi Daxil Edin :: "; getline(cin, answer1);
							cout << "\n---  II Cavabi Daxil Edin :: "; getline(cin, answer2);
							cout << "\n---  III Cavabi Daxil Edin :: "; getline(cin, answer3);
							cout << "\n---  IV Cavabi Daxil Edin :: "; getline(cin, answer4);

							do {
								cout << "\n---  Duzgun Cavabi Sechin ( 1, 2, 3, 4. yazin ) :: "; getline(cin, correctAnswer);

								if (correctAnswer == "1") correctAnswer = answer1;
								else if (correctAnswer == "2") correctAnswer = answer2;
								else if (correctAnswer == "3") correctAnswer = answer3;
								else if (correctAnswer == "4") correctAnswer = answer4;
								else
								{
									cout << "\n\n- 1, 2, 3 ya da 4  - YAZIN !\n Bashqa Sechim Olmaz !!!\n";
									correctAnswer = ""; Sleep(1200); continue;
								}
							} while (correctAnswer == "");

							Answers* answers = new Answers(answer1, answer2, answer3, answer4, correctAnswer);

							newQuiz->AddQuestion(new Question(question, answers));

							delete answers;
						}
						else if (choose3 == 1)
						{
							delete newQuiz;
							break;
						}
						else if (choose3 == 2)
						{
							newQuiz->WriteAllQuestions();
							SaveQuizNameToDB(string(AppFolder + AppQuizPlayers), *(newQuiz->Get_QuizName()));
							break;
						}
					}
				}
			}
			else if (choose2 == 1)
			{
				int key4, choose4 = 0;
				auto quizzes = GetQuizNamesFromDB(string(AppFolder + AppQuizNames));

				while (true)
				{
					system("cls");
					ShowMenu_v(choose4, quizzes);

					key4 = _getch();
					if (key4 > 96)
					{
						if (key4 == 224) key4 = _getch();
						choose4 = KeyCheck(key4, choose4, 0, (quizzes.size() - 1));
					}
					else if (key4 == 13)
					{
						shared_ptr<Quiz> playingQuiz(new Quiz(quizzes.at(choose4)));
						playingQuiz->ReadAllQuestions();


						/*

						play funksiyasi yaz. quiz pointer alsin. next , prev , submit orda olsun.


						*/

					}

				}
			}
			else if (choose2 == 2)
			{
				// user class show
			}
			else if (choose2 == 3)
			{

				//vector ilk 10 show
			}
			else if (choose2 == 4)
			{
				// exit
			}
		}
	}

}



void Play(shared_ptr<Quiz> quiz)
{
	auto suallar = (*quiz).Get_Questions();
	Shuffle(suallar);

	vector<string> cavablar; // oyunchunun verdiyi cavablar burda saxlanacaq.

	int key5, choose5 = 0;  // for show menu
	size_t q_index = 0; //for show question 
	size_t q_count = suallar->size();  // for update index

	vector<string> menuForPlay{ " To Answer ", " Next " ," Previous " ," Submit " };

	Question* sual = nullptr;

	while (true)
	{
		system("cls"); SetColor(14);

		cout << "\n\n\t\t~~~~  Sual  > " << (q_index + 1) << " < \n";
		SetColor(10);

		sual = GetQuestionByIndex(suallar, q_index);

		if (sual == nullptr && q_index < suallar->size()) { q_index++; continue; }

		cout << "\n\t\t" << sual->Get_Question() << endl;
		SetColor(dft);
		ShowMenu_v(choose5, menuForPlay);

		key5 = _getch();
		if (key5 > 96)
		{
			if (key5 == 224)key5 = _getch();
			choose5 = KeyCheck(key5, choose5, 0, (menuForPlay.size() - 1));
		}
		else if (key5 == 13)
		{
			if (choose5 == 0)
			{
				system("cls");	SetColor(10);
				cout << "\n\n\t\t" << sual->Get_Question() << endl;	SetColor(dft);

				shared_ptr<Answers> A(sual->Get_Answers()); // hazirki sualin cavablari
				vector<string> variantlar{ (*A).Get_Answer1(), (*A).Get_Answer2(),
					(*A).Get_Answer3(),(*A).Get_Answer4() };
				
				Shuffle(variantlar);
				int key6, choose6 = 0;

				while (true)
				{
					if (choose6 == 0) SetColor(2);
					cout << "\n\tA ) " << (variantlar)[0]; SetColor(8);
					if (choose6 == 1) SetColor(2);
					cout << "\n\tB ) " << (variantlar)[1]; SetColor(8);
					if (choose6 == 2) SetColor(2);
					cout << "\n\tC ) " << (variantlar)[2]; SetColor(8);
					if (choose6 == 3) SetColor(2);
					cout << "\n\tD ) " << (variantlar)[3]; SetColor(dft);

					key6 = _getch();
					if (key6 > 96)
					{
						if (key6 == 224)key6 = _getch();
						choose6 = KeyCheck(key6, choose6, 0, (variantlar.size() - 1));
					}
					else if (key6 == 13)
					{
						if (choose6 == 0)
							cavablar[q_index] = variantlar[0];
						else if (choose6 == 1)
							cavablar[q_index] = variantlar[1];
						else if (choose6 == 2)
							cavablar[q_index] = variantlar[2];
						else if (choose6 == 3)
							cavablar[q_index] = variantlar[3];
						
						break;
					}
				}
			}
			else if (choose5 == 1)
			{
				if (q_index < (q_count - 1)) q_index++;
			}
			else if (choose5 == 2)
			{
				if (q_index > 0) q_index--;
			}
			else if (choose5 == 3)
			{
				// submit , delete question* sual;
			}
		}
	}
}


void Guest_Menu()
{

}



string Login_Menu()
{
	int key1, choose1 = 0;
	vector<string> menuForLogin{ " Sign In "," Sign Up " ," Exit " };

	shared_ptr<UserDatabase> appUserDB(new UserDatabase(AppFolder + AppUsers));
	appUserDB->ReadAllUsers();

	while (true)
	{
		system("cls");
		ShowMenu_v(choose1, menuForLogin);

		key1 = _getch();
		if (key1 > 96)
		{
			if (key1 == 224)key1 = _getch();

			choose1 = KeyCheck(key1, choose1, 0, (menuForLogin.size() - 1));
		}
		else if (key1 == 13)
		{
			try
			{
				if (choose1 == 0) // Sign In
				{
					string un, ps;// username, password

					SetConsoleTextAttribute(h, 6);
					cout << "\n\t\tUsername Daxil Edin : "; getline(cin, un);
					cout << "\n\t\tPassword Daxil Edin : "; getline(cin, ps);
					SetConsoleTextAttribute(h, dft);

					if (appUserDB->Check_User(un, ps))
					{
						return (appUserDB->getUserByUsername(un).Get_Access());
					}
					else
					{
						throw DatabaseException("\nUsername ya da Password Yanlish Daxil Edilib.",
							GetTime(), __FILE__, __LINE__);
					}
				}
				else if (choose1 == 1) // Sign Up
				{
					string lvl, n, sn, un, ps;// level, name, surname, username, password

					SetConsoleTextAttribute(h, 6);
					cout << "\n\t\t\tSeviyye : Admin = a | Guest = g\n\n\t\tSeviyye Sechin : "; getline(cin, lvl);
					cout << "\n\t\tAdinizi Daxil Edin : "; getline(cin, n);
					cout << "\n\t\tSoyadinizi Daxil Edin : "; getline(cin, sn);
					cout << "\n\t\tUsername Daxil Edin : "; getline(cin, un);
					cout << "\n\t\tPassword Daxil Edin : "; getline(cin, ps);
					SetConsoleTextAttribute(h, dft);

					if (appUserDB->Check_User(un))
					{
						throw DatabaseException("\nBu Username-li Isdifadechi Var. Basqa Username Daxil Edin.",
							GetTime(), __FILE__, __LINE__);
					}
					else
					{
						if (lvl == "a") lvl = "__admin__";

						appUserDB->addUser(new User(un, ps, n, sn, lvl));

						appUserDB->WriteEndUser();

						SetConsoleTextAttribute(h, 12);
						cout << "\n\tUser Elave Olundu.\n\n"; system("pause");
						SetConsoleTextAttribute(h, dft);
					}
				}
				else if (choose1 == 2) // Exit
				{
					appUserDB->WriteAllUsers();
					return ("__break__");
				}
			}
			catch (exception& ex)
			{
				SetConsoleTextAttribute(h, 4);
				cout << endl << boolalpha << ex.what() << endl;
				cout << endl << boolalpha;
				SetConsoleTextAttribute(h, dft);
				system("pause");
			}
		}
	}
	return ("__none__");
}

