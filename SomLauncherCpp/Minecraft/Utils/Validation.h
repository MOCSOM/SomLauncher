#ifndef VALIDATION_H_
#define VALIDATION_H_

#include <exception>
#include <string>

class JsonParseException : public std::exception
{
private:
	std::string message;

public:
	JsonParseException() = default;
	JsonParseException(const std::string& message);
	~JsonParseException() = default;

public:
	const char* what() const noexcept override;
};

class Validation
{
public:
	virtual void validate() = 0;

	static void requireNonNull(const void* object, const std::string& message);
};

#endif // !VALIDATION_H_
