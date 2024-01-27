#pragma once


class User
{
	string _name = "";
	string _surname = "";
	string _username = "";
	string _password = "";
	string _access = "";
	size_t _totalScore = 0;

public:

	User(string username, string password, string name, string surname, string access)
	{
		this->Set_Username(username);
		this->Set_Password(password);
		this->Set_Name(name);
		this->Set_Surname(surname);
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
		if (username.length() < 6)
			throw InvalidArgumentException("\nUsername Herf Sayi 6-dan Chox Olmalidir.",
				GetTime(), __FILE__, __LINE__);
		if (!(int(username.front()) >= 65 && int(username.front()) <= 90))
			throw InvalidArgumentException("\nUsername-in Ilk Herfi Boyuk Olmalidir.",
				GetTime(), __FILE__, __LINE__);

		this->_username = username;
	}
	void Set_Password(string password)
	{
		if (password.length() < 6)
			throw InvalidArgumentException("\nPassword Herf Sayi 6-dan Chox Olmalidir.",
				GetTime(), __FILE__, __LINE__);

		this->_password = password;
	}
	void Set_Name(string name)
	{
		if (name.length() < 4)
			throw InvalidArgumentException("\nAdin Herf Sayi 4-dan Chox Olmalidir.",
				GetTime(), __FILE__, __LINE__);

		this->_name = name;
	}
	void Set_Surname(string surname)
	{
		if (surname.length() < 4)
			throw InvalidArgumentException("\nSoyadin Herf Sayi 4-dan Chox Olmalidir.",
				GetTime(), __FILE__, __LINE__);

		this->_surname = surname;
	}
	void Set_Access(string access)
	{
		if (access == "a" || access == "A")
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

public:

	UserDatabase() {}
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

	bool Check_User(string username)
	{
		for (auto& us : _users)
			if (us->Get_Username() == username)
				return true;

		return false;
	}
	bool Check_User(string username, string password)
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

	void ReadAllUsers(string dest)
	{
		ifstream file(dest, ios::in);

		if (!file.is_open())
		{
			throw Exception("\nFile Achilmadi.",
				GetTime(), __FILE__, __LINE__);
		}

		string index = "", name = "", surname = "", username = "", password = "", level = "";

		_users.clear(); _endUser = 0;

		while (!file.eof())
		{
			file >> index;

			if (!file.eof())
			{
				_endUser++;
				file >> name >> surname >> username >> password >> level;

				_users.push_back(new User(username, password, name, surname, level));
			}
		}
		file.close();
	}

	void WriteEndUser(string dest)
	{
		ofstream file(dest, ios::app);

		if (!file.is_open() || !file)
		{
			throw Exception("\nFile Achilmadi.",
				GetTime(), __FILE__, __LINE__);
		}

		auto us = _users.end();

		if (*us != nullptr)
		{
			file << (_endUser++) << ". "
				<< (*us)->Get_Name() << " "
				<< (*us)->Get_Surname() << " "
				<< (*us)->Get_Username() << " "
				<< (*us)->Get_Password() << " "
				<< (*us)->Get_Access() << "\n";
		}
		file.close();
	}

	void WriteAllUsers(string dest)
	{
		ofstream file(dest, ios::out);

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
				file << (index++) << ". "
					<< us->Get_Name() << " "
					<< us->Get_Surname() << " "
					<< us->Get_Username() << " "
					<< us->Get_Password() << " "
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
