#pragma once


void Play(shared_ptr<Quiz> quiz)
{
	list<Question*>* suallar = (*quiz).Get_Questions();
	//Shuffle(suallar);
	//shuffle(suallar->begin(), suallar->end(),default_random_engine(random_device()()));

	vector<string> cavablar; // oyunchunun verdiyi cavablar burda saxlanacaq.

	FillWithEmpty(cavablar, suallar->size()); // sual sayi qeder ' bosh ' doldurur

	int key5, choose5 = 0;  // for show menu
	size_t q_index = 0; //for show question 
	size_t q_count = suallar->size();  // for update index
	int ignoreIndex = -2; // for show or dont show - next and prev.

	vector<string> menuForPlay{ " To Answer ", " Next ", " Previous ", " Submit " };

	Question* sual = nullptr;

	while (true)
	{
		system("cls"); SetColor(14);

		cout << "\n\n\t\t~~~~  Sual  > " << (q_index + 1) << " < \n";
		SetColor(10);

		sual = GetQuestionByIndex(suallar, q_index);

		//if (sual == nullptr && q_index < suallar->size()) { q_index++; continue; }

		cout << "\n\t\t" << sual->Get_Question() << endl; SetColor(dft);

		if (q_index == 0) ignoreIndex = 2;
		else if (q_index == (q_count - 1)) ignoreIndex = 1;

		ShowMenu_v(choose5, menuForPlay, ignoreIndex);
		ignoreIndex = -2;

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
				shared_ptr<Answers> A(sual->Get_Answers()); // hazirki sualin cavablari
				vector<string> variantlar{ (*A).Get_Answer1(), (*A).Get_Answer2(),
					(*A).Get_Answer3(), (*A).Get_Answer4() };

				//Shuffle(variantlar);


				int key6, choose6 = 0;

				while (true)
				{
					system("cls"); SetColor(10);
					cout << "\n\n\t\t" << sual->Get_Question() << endl; SetColor(8);

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
						cavablar[q_index] = variantlar[choose6];

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
				string corAnswer = "", quizName = *((*quiz).Get_QuizName());
				int c_index = 0, duzSayi = 0, sehvSayi = 0, boshSayi = 0;

				for (auto s : *suallar)
				{
					corAnswer = s->Get_CorrectAnswer();

					if (cavablar[c_index] == corAnswer)
						duzSayi++;
					else if (cavablar[c_index] == "_empty_")
						boshSayi++;
					else
						sehvSayi++;

					c_index++;
				}

				cout << "\n\n\tUsername : " << gUserName << endl;
				cout << "\n\tQuiz Name : " << quizName << endl;
				cout << "\n\tDogru Cavablarin Sayi : " << duzSayi << endl;
				cout << "\n\tSehv Cavablarin Sayi : " << sehvSayi << endl;
				cout << "\n\tBosh Cavablarin Sayi : " << boshSayi << endl << endl;

				Player* pl = new Player(gUserName, quizName, duzSayi, sehvSayi, boshSayi);

				PlayerDatabase* PlDb = new PlayerDatabase(Folder + Players);

				PlDb->addPlayer(pl);
				PlDb->ReadEndPlayerIndex();
				PlDb->WriteEndPlayer();

				if (PlDb != nullptr) { delete PlDb; PlDb = nullptr; }
				DeleteAllItemsInList(suallar);

				SetColor(11);
				cout << "\n\n\n\tDavam Etmek Uchun Her Hansi Duymeye Basin.\n\n";
				SetColor(dft); cin.get();

				return;
			}
		}
	}
}


void Main_Menu(bool isAdmin)
{
	int key2, choose2 = 0;
	vector<string> menuForMain;

	if (isAdmin) menuForMain.push_back(" Create New Quiz ");

	menuForMain.push_back(" Start Quiz "); menuForMain.push_back(" Show My Score ");
	menuForMain.push_back(" Leaders Board "); menuForMain.push_back(" Exit ");

	while (true)
	{
		system("cls");
		ShowMenu_v(choose2, menuForMain);

		key2 = _getch();
		if (key2 > 96)
		{
			if (key2 == 224)key2 = _getch();
			choose2 = KeyCheck(key2, choose2, 0, (menuForMain.size() - 1));
		}
		else if (key2 == 13)
		{
			if (menuForMain[choose2] == " Create New Quiz ")
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
							cout << "\n\n\t\t\t--- Sual  > " << (newQuiz->Get_QuestionCount() + 1) << " < \n";
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
							SaveQuizNameToDB(string(Folder + QuizNames), *(newQuiz->Get_QuizName()));
							LoadingScreen("Creating", 40, 3);

							break;
						}
					}
				}
			}
			else if (menuForMain[choose2] == " Start Quiz ")
			{
				int key4, choose4 = 0;
				vector<string> quizzes{ " ->~  Exit  ~<- (not quiz) " };

				GetQuizNamesFromDB(string(Folder + QuizNames), quizzes);

				LoadingScreen("Starting", 35, 3);

				while (true)
				{
					system("cls");

					printf("\n\t\t\tSelect Quiz For Starting.\n\n");

					ShowMenu_v(choose4, quizzes);

					key4 = _getch();
					if (key4 > 96)
					{
						if (key4 == 224) key4 = _getch();
						choose4 = KeyCheck(key4, choose4, 0, (quizzes.size() - 1));
					}
					else if (key4 == 13)
					{
						if (quizzes.at(choose4) == " ->~  Exit  ~<- (not quiz) ")
							break;

						shared_ptr<Quiz> playingQuiz(new Quiz(quizzes.at(choose4)));
						playingQuiz->ReadAllQuestions();

						Play(playingQuiz);
						break;
					}

				}
			}
			else if (menuForMain[choose2] == " Show My Score ")
			{
				PlayerDatabase* playerDB = new PlayerDatabase(Folder + Players);

				playerDB->ReadAllPlayers();

				list<Player*> players = playerDB->Get_Players();

				system("cls"); cout << endl << endl;
				for (auto player : players)
				{
					if (player->Get_Username() == gUserName)
					{
						player->Show(false, true);
					}
				}

				SetColor(11);
				cout << "\n\n\n\tDavam Etmek Uchun Her Hansi Duymeye Basin.\n\n";
				SetColor(dft); cin.get();

				if (playerDB != nullptr) { delete playerDB; playerDB = nullptr; }
			}
			else if (menuForMain[choose2] == " Leaders Board ")
			{
				LoadingScreen("Updating", 45, 2);

				int key8, choose8 = 0;
				string quizName = " ->~ Exit ~<- (not quiz) ";
				vector<string> show_quizzes{ quizName };

				GetQuizNamesFromDB(string(Folder + QuizNames), show_quizzes);

				while (true)
				{
					system("cls");

					printf("\n\t\tSelect Quiz For Show Special Leader Board.\n\n");

					ShowMenu_v(choose8, show_quizzes);

					key8 = _getch();
					if (key8 > 96)
					{
						if (key8 == 224) key8 = _getch();
						choose8 = KeyCheck(key8, choose8, 0, (show_quizzes.size() - 1));
					}
					else if (key8 == 13)
					{
						if (show_quizzes.at(choose8) == " ->~ Exit ~<- (not quiz) ")
							break;

						quizName = show_quizzes.at(choose8);
						break;
					}
				}

				PlayerDatabase* plDb = new PlayerDatabase(Folder + Players);
				plDb->ReadAllPlayers();

				list<Player*> players = plDb->Get_Players();

				players.sort(ComparePlayersBySuccessRate);

				system("cls"); cout << endl << endl;

				int END = 1, s_index = 1;
				for (auto P : players)
				{
					if (END == 10)
						break;
					if (P != nullptr && (P->Get_PlayedQuizName() == quizName))
					{
						SetColor(11); cout << "\n" << (s_index++) << " --> ";
						P->Show(true, false);
					}

					END++;
				}

				SetColor(11);
				cout << "\n\n\tDavam Etmek Uchun Her Hansi Duymeye Basin.\n\n";
				SetColor(dft); cin.get();

				if (plDb != nullptr) { delete plDb; plDb = nullptr; }
			}
			else if (menuForMain[choose2] == " Exit ")
			{
				break;
			}
		}
	}

}


string Login_Menu()
{
	int key1, choose1 = 0;
	vector<string> menuForLogin{ " Sign In "," Sign Up " ," Exit " };

	shared_ptr<UserDatabase> appUserDB(new UserDatabase(Folder + Users));
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

					SetColor(6);
					cout << "\n\t\tUsername Daxil Edin : "; getline(cin, un);
					cout << "\n\t\tPassword Daxil Edin : "; getline(cin, ps);
					SetColor(dft);

					if (appUserDB->Check_User(un, ps))
					{
						gUserName = un;
						return (appUserDB->getUserByUsername(un).Get_Access());
					}
					else
					{
						throw Exception("\nUsername ya da Password Yanlish Daxil Edilib.",
							GetTime(), __FILE__, __LINE__);
					}
				}
				else if (choose1 == 1) // Sign Up
				{
					string lvl, n, sn, un, ps;// level, name, surname, username, password

					SetColor(6);
					cout << "\n\t\t\tSeviyye : Admin = a | Guest = g\n\n\t\tSeviyye Sechin : "; getline(cin, lvl);
					cout << "\n\t\tAdinizi Daxil Edin : "; getline(cin, n);
					cout << "\n\t\tSoyadinizi Daxil Edin : "; getline(cin, sn);
					cout << "\n\t\tUsername Daxil Edin : "; getline(cin, un);
					cout << "\n\t\tPassword Daxil Edin : "; getline(cin, ps);
					SetColor(dft);

					if (appUserDB->Check_User(un))
					{
						throw Exception("\nBu Username-li Isdifadechi Var. Basqa Username Daxil Edin.",
							GetTime(), __FILE__, __LINE__);
					}
					else
					{
						if (lvl == "a") lvl = "__admin__";

						appUserDB->addUser(new User(un, ps, n, sn, lvl));

						appUserDB->WriteEndUser();

						LoadingScreen("User Adding", 40, 10);
						SetColor(12);
						cout << "\n\tUser Elave Olundu.\n\n"; system("pause");
						SetColor(dft);
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
				SetColor(4);
				cout << endl << ex.what() << endl;
				SetColor(dft);
				system("pause");
			}
		}
	}
	return ("__none__");
}

