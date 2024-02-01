#pragma once


class User
{
	string _name = "";
	string _surname = "";
	string _username = "";
	string _password = "";
	string _access = "";

public:

	User(){}
	User(string username, string password, string name, string surname, string access)
	{
		this->Set_Username(username);
		this->Set_Password(password);
		this->Set_Name(name);
		this->Set_Surname(surname);
		this->Set_Access(access);
	}
	User(const User& other)
		: User(other._username, other._password, other._name, other._surname, other._access) {}

	User& operator=(const User& other)
	{
		this->_username = other._username;
		this->_password = other._password;
		this->_name = other._name;
		this->_surname = other._surname;
		this->_access = other._access;

		return (*this);
	}

	void Set_Username(string username)
	{
		if (username.length() < 3)
			throw InvalidArgumentException("\nUsername Herf Sayi 3-dan Chox Olmalidir.",
				GetTime(), __FILE__, __LINE__);

		this->_username = username;
	}
	void Set_Password(string password)
	{
		if (password.length() < 3)
			throw InvalidArgumentException("\nPassword Herf Sayi 3-dan Chox Olmalidir.",
				GetTime(), __FILE__, __LINE__);

		this->_password = password;
	}
	void Set_Name(string name)
	{
		if (name.length() < 2)
			throw InvalidArgumentException("\nAdin Herf Sayi 2-dan Chox Olmalidir.",
				GetTime(), __FILE__, __LINE__);

		this->_name = name;
	}
	void Set_Surname(string surname)
	{
		if (surname.length() < 2)
			throw InvalidArgumentException("\nSoyadin Herf Sayi 2-dan Chox Olmalidir.",
				GetTime(), __FILE__, __LINE__);

		this->_surname = surname;
	}
	void Set_Access(string access)
	{
		if (access == "__admin__")
			this->_access = "__admin__";
		else
			this->_access = "__guest__";
	}

	string Get_Username() const { return this->_username; }
	string Get_Password() const { return this->_password; }
	string Get_Name() const { return this->_name; }
	string Get_Surname() const { return this->_surname; }
	string Get_Access() const { return this->_access; }

	void show() const
	{
		cout << endl << "\tAccess : " << _access;
		cout << endl << "\tName : " << _name;
		cout << endl << "\tSurname : " << _surname;
		cout << endl << "\tUsername : " << _username;
		cout << endl << "\tPassword : " << _password;
	}

};


class UserDatabase
{
	list<User*> _users;
	size_t _endUser = 0;
	string _fileName = "";

public:

	UserDatabase() {}
	UserDatabase(string fileName)
	{
		this->SetFileName(fileName);
	}
	UserDatabase(const UserDatabase& other)
	{
		for (auto u : other._users)
			_users.push_back(new User(*u));

		_endUser = other._endUser;
	}

	UserDatabase& operator=(const UserDatabase& other)
	{
		if (_users.size() > 0)
			Delete_AllUsers();

		for (auto u : other._users)
			_users.push_back(new User(*u));

		_endUser = other._endUser;
		return (*this);
	}

	void addUser(const User* user)
	{
		_users.push_back(const_cast<User*>(user));
	}

	void Delete_AllUsers()
	{
		for (auto user : _users)
		{
			delete user;
			user = nullptr;
		}
		_users.clear();
	}

	void SetFileName(string file)
	{
		this->_fileName = file;
	}
	
	string GetFileName()const
	{
		return this->_fileName;
	}

	User& getUserByUsername(string username)
	{
		if (_users.size() == 0) {
			throw Exception("\nIstifadechi Sayi 0 dir.", GetTime(), __FILE__, __LINE__);
		}

		for (auto& us : _users)
		{
			if (us->Get_Username() == username)
			{
				return *us;
			}
		}
		throw Exception("\nIstifadechi Tapilmadi.", GetTime(), __FILE__, __LINE__);
	}
	void updateUser(User& oldUser, const User& newUser)
	{
		for (auto& us : _users)
		{
			if (us->Get_Username() == oldUser.Get_Username())
			{
				*(us) = newUser;
				return;
			}
		}
		throw Exception("\nIstifadechi Tapilmadi.",
			GetTime(), __FILE__, __LINE__);
	}

	auto Get_Users() const { return _users; }
	size_t Get_User_Count() const { return _users.size(); }
	size_t Get_End_User() const { return _endUser; }

	bool Check_User(string username)const
	{
		for (auto& us : _users)
			if (us->Get_Username() == username)
				return true;

		return false;
	}
	bool Check_User(string username, string password)const
	{
		for (auto& us : _users)
		{
			if (us->Get_Username() == username)
			{
				if (us->Get_Password() == password)
					return true;
				else
					return false;
			}
		}
		return false;
	}

	void ReadAllUsers()
	{
		ifstream file(_fileName, ios::in);

		if (!file.is_open())
		{
			throw Exception("\nFile Achilmadi.",
				GetTime(), __FILE__, __LINE__);
		}

		string index = "", name = "", surname = "", username = "", password = "", level = "";

		this->Delete_AllUsers(); _endUser = 0;

		while (!file.eof())
		{
			getline(file, index, '^');

			if (!file.eof())
			{
				_endUser++;
				getline(file, name, '^');
				getline(file, surname, '^');
				getline(file, username, '^');
				getline(file, password, '^');
				getline(file, level);

				_users.push_back(new User(username, password, name, surname, level));
			}
		}
		file.close();
	}

	void WriteEndUser()
	{
		ofstream file(_fileName, ios::app);

		if (!file.is_open() || !file)
		{
			throw Exception("\nFile Achilmadi.",
				GetTime(), __FILE__, __LINE__);
		}

		auto us = _users.back();

		if (us != nullptr)
		{
			file << (++_endUser) << ".^"
				<< (us)->Get_Name() << "^"
				<< (us)->Get_Surname() << "^"
				<< (us)->Get_Username() << "^"
				<< (us)->Get_Password() << "^"
				<< (us)->Get_Access() << "\n";
		}
		file.close();
	}

	void WriteAllUsers()const
	{
		ofstream file(_fileName, ios::out);

		if (!file.is_open() || !file)
		{
			throw Exception("\nFile Achilmadi.",
				GetTime(), __FILE__, __LINE__);
		}

		size_t index = 1;
		for (auto& us : _users)
		{
			if (us != nullptr)
			{
				file << (index++) << ".^"
					<< us->Get_Name() << "^"
					<< us->Get_Surname() << "^"
					<< us->Get_Username() << "^"
					<< us->Get_Password() << "^"
					<< us->Get_Access() << "\n";
			}
		}
		file.close();
	}

	~UserDatabase()
	{
		Delete_AllUsers();
	}
};


class Player
{
	string* _username = nullptr; // player username from user database
	string* _playedQuiz = nullptr;
	int* _totalCount = nullptr; // verilen cavablarin cemi sayi
	int* _correctCount = nullptr; // duzgun cavablarin sayi
	int* _wrongCount = nullptr; // sehv cavablarin sayi
	int* _emptyCount = nullptr; // bosh (cavab verilmeyen) cavablarin sayi

public:

	Player(string username, string playedQuiz, int correctCount, int wrongCount, int emptyCount)
	{
		this->Set_Username(username);
		this->Set_PlayedQuizName(playedQuiz);
		this->Set_CorrectCount(correctCount);
		this->Set_EmptyCount(emptyCount);
		this->Set_WrongCount(wrongCount);
		this->Set_TotalCount();
	}
	Player(const Player& player)
		: Player(*(player._username), *(player._playedQuiz), *(player._correctCount), *(player._wrongCount), *(player._emptyCount))
	{}
	~Player()
	{
		if (this->_username != nullptr)
		{
			delete this->_username;
			this->_username = nullptr;
		}
		if (this->_playedQuiz != nullptr)
		{
			delete this->_playedQuiz;
			this->_playedQuiz = nullptr;
		}
		if (this->_totalCount != nullptr)
		{
			delete this->_totalCount;
			this->_totalCount = nullptr;
		}
		if (this->_correctCount != nullptr)
		{
			delete this->_correctCount;
			this->_correctCount = nullptr;
		}
		if (this->_wrongCount != nullptr)
		{
			delete this->_wrongCount;
			this->_wrongCount = nullptr;
		}
		if (this->_emptyCount != nullptr)
		{
			delete this->_emptyCount;
			this->_emptyCount = nullptr;
		}
	}

	Player& operator=(const Player& player)
	{
		this->Set_Username(*(player._username));
		this->Set_PlayedQuizName(*(player._playedQuiz));
		this->Set_CorrectCount(*(player._correctCount));
		this->Set_EmptyCount(*(player._emptyCount));
		this->Set_WrongCount(*(player._wrongCount));
		this->Set_TotalCount();
	}

	void Set_CorrectCount(int correctCount)
	{
		if (correctCount < 0)
			throw InvalidArgumentException("\n Count Menfi Ola Bilmez ! ", GetTime(), __FILE__, __LINE__);

		if (this->_correctCount != nullptr) delete this->_correctCount;

		this->_correctCount = new int(correctCount);
	}
	void Set_WrongCount(int wrongCount)
	{
		if (wrongCount < 0)
			throw InvalidArgumentException("\n Count Menfi Ola Bilmez ! ", GetTime(), __FILE__, __LINE__);

		if (this->_wrongCount != nullptr) delete this->_wrongCount;

		this->_wrongCount = new int(wrongCount);
	}
	void Set_EmptyCount(int emptyCount)
	{
		if (emptyCount < 0)
			throw InvalidArgumentException("\n Count Menfi Ola Bilmez ! ", GetTime(), __FILE__, __LINE__);

		if (this->_emptyCount != nullptr) delete this->_emptyCount;

		this->_emptyCount = new int(emptyCount);
	}
	void Set_TotalCount()
	{
		if(_correctCount == nullptr || _wrongCount == nullptr || _emptyCount == nullptr)
			throw InvalidArgumentException("\n Any Count is Nullptr ! ", GetTime(), __FILE__, __LINE__);

		if (this->_totalCount != nullptr) delete this->_totalCount;

		this->_totalCount = new int((*_correctCount) + (*_wrongCount) + (*_emptyCount));
	}
	void Set_Username(string username)
	{
		if (username.length() < 3)
			throw InvalidArgumentException("\n Len 4-den Kichik Ola Bilmez ! ", GetTime(), __FILE__, __LINE__);

		if (this->_username != nullptr) delete this->_username;

		this->_username = new string(username);
	}
	void Set_PlayedQuizName(string quiz)
	{
		if (quiz.length() < 2)
			throw InvalidArgumentException("\n Len 3-den Kichik Ola Bilmez ! ", GetTime(), __FILE__, __LINE__);

		if (this->_playedQuiz != nullptr) delete this->_playedQuiz;

		this->_playedQuiz = new string(quiz);
	}

	int Get_CorrectCount() { return *_totalCount; }
	int Get_WrongCount() { return *_correctCount; }
	int Get_EmptyCount() { return *_wrongCount; }
	int Get_TotalCount() { return *_emptyCount; }
	string Get_Username() { return *_username; }
	string Get_PlayedQuizName() { return *_playedQuiz; }

	void Show(bool show_name)
	{
		SetColor(12); cout << endl;

		if(show_name) cout << "\nUsername : " << *_username << " | \n\n";

		cout << "Played Quiz Name : " << *_playedQuiz << " | \n\n";
		cout << "Total Answer Count : " << *_totalCount << " | \n";
		cout << "Correct Count : " << *_correctCount << " | \n";
		cout << "Wrong Count : " << *_wrongCount << " | \n";
		cout << "Empty Count : " << *_emptyCount << endl << endl;
		SetColor(dft);
	}

};


class PlayerDatabase
{
	list<Player*> _players;
	size_t _endPlayer = 0;
	string _fileName = "";

public:

	PlayerDatabase() {}
	PlayerDatabase(string fileName)
	{
		this->SetFileName(fileName);
	}
	PlayerDatabase(const PlayerDatabase& other)
	{
		for (auto u : other._players)
			_players.push_back(new Player(*u));

		_endPlayer = other._endPlayer;
	}

	PlayerDatabase& operator=(const PlayerDatabase& other)
	{
		if (_players.size() > 0)
			Delete_AllPlayers();

		for (auto u : other._players)
			_players.push_back(new Player(*u));

		_endPlayer = other._endPlayer;
		return (*this);
	}

	void addPlayer(const Player* player)
	{
		_players.push_back(const_cast<Player*>(player));
	}

	void Delete_AllPlayers()
	{
		for (auto player : _players)
		{
			delete player;
			player = nullptr;
		}
		_players.clear();
	}

	void SetFileName(string file)
	{
		this->_fileName = file;
	}

	string GetFileName()const
	{
		return this->_fileName;
	}

	Player& getPlayerByUsername(string username)
	{
		if (_players.size() == 0) {
			throw Exception("\nOyunchu Sayi 0 dir.", GetTime(), __FILE__, __LINE__);
		}

		for (auto& us : _players)
		{
			if (us->Get_Username() == username)
			{
				return *us;
			}
		}
		throw Exception("\nOyunchu Tapilmadi.", GetTime(), __FILE__, __LINE__);
	}
	void updatePlayer(Player& oldUser, const Player& newUser)
	{
		for (auto& us : _players)
		{
			if (us->Get_Username() == oldUser.Get_Username())
			{
				*(us) = newUser;
				return;
			}
		}
		throw Exception("\nOyunchu Tapilmadi.",
			GetTime(), __FILE__, __LINE__);
	}

	auto Get_Players() const { return _players; }
	size_t Get_Player_Count() const { return _players.size(); }
	size_t Get_End_Player() const { return _endPlayer; }

	bool Check_Player(string username)const
	{
		for (auto& us : _players)
			if (us->Get_Username() == username)
				return true;

		return false;
	}

	void ReadAllPlayers()
	{
		ifstream file(_fileName, ios::in);

		if (!file.is_open())
		{
			throw Exception("\nFile Achilmadi.",
				GetTime(), __FILE__, __LINE__);
		}

		string index = "", username = "", playedQuiz = "", total = "", correct = "", wrong = "", empty = "";

		this->Delete_AllPlayers(); _endPlayer = 0;

		while (!file.eof())
		{
			getline(file, index, '|');

			if (!file.eof())
			{
				_endPlayer++;
				getline(file, username, '|');
				getline(file, playedQuiz, '|');
				getline(file, total, '|');
				getline(file, correct, '|');
				getline(file, wrong, '|');
				getline(file, empty);

				_players.push_back(new Player(username, playedQuiz, stoi(correct), stoi(wrong), stoi(empty)));
			}
		}
		file.close();
	}

	void WriteEndPlayer()
	{
		ofstream file(_fileName, ios::app);

		if (!file.is_open() || !file)
		{
			throw Exception("\nFile Achilmadi.",
				GetTime(), __FILE__, __LINE__);
		}

		auto us = _players.back();

		if (us != nullptr)
		{
			file << (++_endPlayer) << ".|"
				<< (us)->Get_Username() << "|"
				<< (us)->Get_PlayedQuizName() << "|"
				<< (us)->Get_TotalCount() << "|"
				<< (us)->Get_CorrectCount() << "|"
				<< (us)->Get_WrongCount() << "|"
				<< (us)->Get_EmptyCount() << "\n";
		}
		file.close();
	}

	void WriteAllPlayers()const
	{
		ofstream file(_fileName, ios::out);

		if (!file.is_open() || !file)
		{
			throw Exception("\nFile Achilmadi.",
				GetTime(), __FILE__, __LINE__);
		}

		size_t index = 1;
		for (auto& us : _players)
		{
			if (us != nullptr)
			{
				file << (index++) << ".|"
					<< (us)->Get_Username() << "|"
					<< (us)->Get_PlayedQuizName() << "|"
					<< (us)->Get_TotalCount() << "|"
					<< (us)->Get_CorrectCount() << "|"
					<< (us)->Get_WrongCount() << "|"
					<< (us)->Get_EmptyCount() << "\n";
			}
		}
		file.close();
	}

	~PlayerDatabase()
	{
		Delete_AllPlayers();
	}
};
