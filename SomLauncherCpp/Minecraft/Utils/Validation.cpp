#include "Validation.h"

JsonParseException::JsonParseException(const std::string& message)
	: message(message)
{
}

const char* JsonParseException::what() const noexcept
{
	return this->message.c_str();
}

void Validation::requireNonNull(const void* object, const std::string& message)
{
	if (object == nullptr)
	{
		throw JsonParseException(message);
	}
}
