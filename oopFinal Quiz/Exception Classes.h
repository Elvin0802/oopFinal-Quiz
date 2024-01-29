#pragma once


class Exception : public exception
{
	string _text = "";
	string _time = "";
	string _source = "";
	size_t _line = 0;
	string _completed_message = "";

public:

	Exception(string Text, string Time, string Source, size_t Line)
		: exception(Text.c_str())
	{
		this->_text = Text;
		this->_time = Time;
		this->_source = Source;
		this->_line = Line;
		this->_completed_message
			= "\n\n\t---  Description of Exception  ---" + _text
			+ "\n--  Exception Source :  " + _source
			+ "\n--  Exception Time :  " + _time
			+ "--  Exception Line :  " + to_string(_line)
			+ "\n\n\n";
	}

	string Get_Message()const
	{
		return this->_completed_message;
	}

	char const* what() const override
	{
		return this->_completed_message.c_str();
	}

};


class DatabaseException : public Exception
{
	string _text = "\n\t>>>>  Database Exception  <<<<\n";

public:

	DatabaseException(string Text, string Time, string Source, size_t Line)
		: Exception(Text, Time, Source, Line)
	{}

	char const* what() const override
	{
		return (_text + Exception::Get_Message()).c_str();
	}
};


class InvalidArgumentException : public Exception
{
	string _text = "\n\t>>>>  Invalid Argument Exception  <<<<\n";

public:

	InvalidArgumentException(string Text, string Time, string Source, size_t Line)
		: Exception(Text, Time, Source, Line)
	{}

	char const* what() const override
	{
		return (_text + Exception::Get_Message()).c_str();
	}
};
