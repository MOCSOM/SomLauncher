#ifndef TERMINATEPROGRAMMEXCEPTION_H_
#define TERMINATEPROGRAMMEXCEPTION_H_

#include <exception>

class TerminateProgrammException : public std::exception
{
	int returned_id = 0;
public:

	TerminateProgrammException() = default;

	TerminateProgrammException(int returned_id)
		: returned_id(returned_id)
	{
	}

	const char* what() const
	{
		return "programm has been terminate";
	}

	int getReturnedId() const
	{
		return this->returned_id;
	}

	bool operator==(const TerminateProgrammException& other) const
	{
		return this->returned_id == other.returned_id;
	}

	bool operator!=(const TerminateProgrammException& other) const
	{
		return !(*this == other);
	}
};

#endif // !TERMINATEPROGRAMMEXCEPTION_H_
