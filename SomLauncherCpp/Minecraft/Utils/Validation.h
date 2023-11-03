#ifndef VALIDATION_H_
#define VALIDATION_H_

#include <exception>
#include <string>

class JsonParseException : public std::exception {
public:
	JsonParseException(const std::string& message) : message(message) {}
	const char* what() const noexcept override {
		return message.c_str();
	}

private:
	std::string message;
};

class Validation {
public:
	virtual void validate() {
		// Empty default implementation, can be overridden by subclasses.
	}

	static void requireNonNull(const void* object, const std::string& message) {
		if (object == nullptr) {
			throw JsonParseException(message);
		}
	}
};

#endif // !VALIDATION_H_
