#pragma once


class Answers
{
	string _answer1 = "", _answer2 = "", _answer3 = "", _answer4 = "";
	string _correctAnswer = "";

public:

	Answers(string answer_1, string answer_2, string answer_3, string answer_4, string correct_Answer)
	{
		this->Set_Answer1(answer_1);
		this->Set_Answer2(answer_2);
		this->Set_Answer3(answer_3);
		this->Set_Answer4(answer_4);
		this->Set_CorrectAnswer(correct_Answer);
	}
	Answers(const Answers& other)
		: Answers(other._answer1, other._answer2, other._answer3, other._answer4, other._correctAnswer)
	{}

	Answers& operator=(const Answers& other)
	{
		this->_answer1 = other._answer1;
		this->_answer2 = other._answer2;
		this->_answer3 = other._answer3;
		this->_answer4 = other._answer4;
		this->_correctAnswer = other._correctAnswer;

		return (*this);
	}

	string& Check_Answer(string _answer)
	{
		if (_answer != "" || _answer != " ")
			return _answer;

		throw Exception("\nCavabi Duzgun Daxil Edin !\n",
			GetTime(), __FILE__, __LINE__);
	}

	void Set_Answer1(string answer)
	{
		this->_answer1 = Check_Answer(answer);
	}
	void Set_Answer2(string answer)
	{
		this->_answer2 = Check_Answer(answer);
	}
	void Set_Answer3(string answer)
	{
		this->_answer3 = Check_Answer(answer);
	}
	void Set_Answer4(string answer)
	{
		this->_answer4 = Check_Answer(answer);
	}
	void Set_CorrectAnswer(string answer)
	{
		this->_correctAnswer = Check_Answer(answer);
	}

	string Get_Answer1() const { return this->_answer1; }
	string Get_Answer2() const { return this->_answer2; }
	string Get_Answer3() const { return this->_answer3; }
	string Get_Answer4() const { return this->_answer4; }
	string Get_CorrectAnswer() const { return this->_correctAnswer; }

};


class Question
{
	string _question = "";
	Answers* _answers = nullptr;

public:

	Question(string question, const Answers* answers)
	{
		this->Set_Answers(answers);
		this->Set_Question(question);
	}

	Question(const Question& other)
	{
		this->Set_Answers(other._answers);
		this->Set_Question(other._question);
	}

	Question& operator=(const Question& other)
	{
		this->Set_Answers(other._answers);
		this->Set_Question(other._question);
		return(*this);
	}

	void Set_Question(string question)
	{
		if (question == "" || question == " ")
			throw Exception("\nSual Bosh Olmamalidir.\nSuali Duzgun Daxil Edin !\n",
				GetTime(), __FILE__, __LINE__);

		this->_question = question;

		if (this->_question.back() != '?') this->_question += " ?";
	}
	void Set_Answers(const Answers* answers)
	{
		if (_answers != nullptr && answers != nullptr) delete _answers;
		this->_answers = new Answers(*answers);
	}

	Answers* Get_Answers() const { return this->_answers; }
	string Get_CorrectAnswer() const { return (this->_answers->Get_CorrectAnswer()); }
	string Get_Question() const { return this->_question; }

	~Question()
	{
		if (_answers != nullptr)
		{
			delete this->_answers;
			this->_answers = nullptr;
		}
		this->_question = "";
	}
};
