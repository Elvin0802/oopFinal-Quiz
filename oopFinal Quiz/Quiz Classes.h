#pragma once


class Quiz
{
	list<Question*>* _questions = nullptr;
	string* _quizName = nullptr;
	string* _fileName = nullptr;

public:

	Quiz(string QuizName)
	{
		_questions = new list<Question*>();
		this->Set_QuizName(QuizName);
		this->Set_FileName(string(QuizName + txt));
	}
	Quiz(const Quiz& quiz)
		: Quiz(*(quiz._quizName))
	{}

	Quiz& operator=(const Quiz& quiz)
	{
		this->Set_QuizName(*(quiz._quizName));
		this->Set_FileName(*(quiz._fileName));

		for (auto q : *(quiz._questions))
		{
			_questions->push_back(q);
		}

		return (*this);
	}

	void Set_QuizName(string QuizName)
	{
		if (QuizName == "" || QuizName == " ")
			throw Exception("\nQuiz Adi Bosh Olmamalidir.\nQuiz Adini Duzgun Daxil Edin !\n",
				GetTime(), __FILE__, __LINE__);

		if (this->_quizName != nullptr) delete this->_quizName;

		this->_quizName = new string(QuizName);
	}
	void Set_FileName(string FileName)
	{
		if (FileName == "" || FileName == " ")
			throw Exception("\nFile Adi Bosh Olmamalidir.\nFile Adini Duzgun Daxil Edin !\n",
				GetTime(), __FILE__, __LINE__);

		if (this->_fileName != nullptr) delete this->_fileName;

		this->_fileName = new string(AppFolder + FileName);
	}

	string* Get_QuizName() const { return this->_quizName; }
	string* Get_FileName() const { return this->_fileName; }
	size_t Get_QuestionCount() const { return (this->_questions->size()); }
	list<Question*>* Get_Questions() const { return this->_questions; }

	void AddQuestion(const Question* quest) const
	{
		_questions->push_back(const_cast<Question*>(quest));
	}

	void DeleteAllQuestions()
	{
		for (auto q : *_questions)
		{
			delete q;
			q = nullptr;
		}
		_questions->clear();
	}

	void ReadAllQuestions()
	{
		ifstream file(*_fileName, ios::in);

		if (!file.is_open())
		{
			throw Exception("\nFile Achilmadi.",
				GetTime(), __FILE__, __LINE__);
		}

		string index = "";
		string question = "";
		string a1 = "", a2 = "", a3 = "", a4 = "";
		string correctA = "";

		this->DeleteAllQuestions();

		while (!file.eof())
		{
			file >> index;

			if (!file.eof())
			{
				file >> question >> a1 >> a2 >> a3 >> a4 >> correctA;

				Answers* answers = new Answers(a1, a2, a3, a4, correctA);

				_questions->push_back(new Question(question, answers));
				delete answers;
			}
		}
		file.close();
	}

	void WriteEndQuestion()
	{
		ofstream file(*_fileName, ios::app);

		if (!file.is_open() || !file)
		{
			throw Exception("\nFile Achilmadi.",
				GetTime(), __FILE__, __LINE__);
		}

		auto us = _questions->end();

		if (*us != nullptr)
		{
			auto answers = (*us)->Get_Answers();

			file << _questions->size() << ". "
				<< (*us)->Get_Question() << " "
				<< answers->Get_Answer1() << " "
				<< answers->Get_Answer2() << " "
				<< answers->Get_Answer3() << " "
				<< answers->Get_Answer4() << " "
				<< answers->Get_CorrectAnswer() << "\n";
		}
		file.close();
	}

	void WriteAllQuestions()
	{
		ofstream file(*_fileName, ios::out);

		if (!file.is_open() || !file)
		{
			throw Exception("\nFile Achilmadi.",
				GetTime(), __FILE__, __LINE__);
		}

		size_t index = _questions->size();
		for (auto& us : *(_questions))
		{
			if (us != nullptr)
			{
				auto answers = us->Get_Answers();

				file << index << ". "
					<< us->Get_Question() << " "
					<< answers->Get_Answer1() << " "
					<< answers->Get_Answer2() << " "
					<< answers->Get_Answer3() << " "
					<< answers->Get_Answer4() << " "
					<< answers->Get_CorrectAnswer() << "\n";
			}
		}
		file.close();
	}

	~Quiz()
	{
		if (this->_quizName != nullptr)
		{
			delete this->_quizName;
			this->_quizName = nullptr;
		}
		if (this->_fileName != nullptr)
		{
			delete this->_fileName;
			this->_fileName = nullptr;
		}
		if (this->_questions != nullptr)
		{
			this->DeleteAllQuestions();
			delete this->_questions;
			this->_questions = nullptr;
		}
	}

};
