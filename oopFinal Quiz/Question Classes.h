#pragma once


class Answers
{
	string _answer1 = "", _answer2 = "", _answer3 = "", _answer4 = "";
	string _correctAnswer = "";

public:

	Answers(string answer_1, string answer_2, string answer_3, string answer_4, string correct_Answer)
		: _answer1(Set_Answer(answer_1)), _answer2(Set_Answer(answer_2))
		, _answer3(Set_Answer(answer_3)), _answer4(Set_Answer(answer_4))
		, _correctAnswer(Set_Answer(correct_Answer))
	{}
	Answers(const Answers& other)
		: Answers(other._answer1, other._answer2, other._answer3, other._answer4, other._correctAnswer)
	{}

	Answers& operator=(const Answers& other)
	{
		this->_answer1 = Set_Answer(other._answer1);
		this->_answer2 = Set_Answer(other._answer2);
		this->_answer3 = Set_Answer(other._answer3);
		this->_answer4 = Set_Answer(other._answer4);
		this->_correctAnswer = Set_Answer(other._correctAnswer);

		return (*this);
	}

	string& Set_Answer(string answer)
	{
		if (answer != "" || answer != " ")
			return answer;

		throw Exception("\nCavabi Duzgun Daxil Edin !\n",
			GetTime(), __FILE__, __LINE__);
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
	size_t _score = 0;

public:

	Question(string question, const Answers* answers, size_t score)
	{
		this->Set_Answers(answers);
		this->Set_Question(question);
		this->Set_Score(score);
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
	}
	void Set_Answers(const Answers* answers)
	{
		if (_answers != nullptr && answers != nullptr) delete _answers;
		this->_answers = new Answers(*answers);
	}
	void Set_Score(size_t score)
	{
		if (score >= 0 && score <= 1000)
		{
			this->_score = score;
			return;
		}
		throw Exception("\nXal 0 dan Boyuk ve 1000 den Kicik Olmalidir !\n",
			GetTime(), __FILE__, __LINE__);
	}

	Answers* Get_Answers() const { return this->_answers; }
	string Get_Question() const { return this->_question; }
	size_t Get_Score() const { return this->_score; }

	~Question()
	{
		if (_answers != nullptr)
		{
			delete this->_answers;
			this->_answers = nullptr;
		}
		this->_question = "";
		this->_score = 0;
	}
};
