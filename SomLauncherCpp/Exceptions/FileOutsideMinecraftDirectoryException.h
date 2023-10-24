#ifndef FILEOUTSIDEMINECRAFTDIRECOTYEXCEPTION_H_
#define FILEOUTSIDEMINECRAFTDIRECOTYEXCEPTION_H_

#include <exception>
#include <filesystem>

class FileOutsideMinecraftDirectoryException : public std::exception
{
private:
	std::filesystem::path path;
	std::filesystem::path minecraft_directory;

	std::string out_message;

public:
	FileOutsideMinecraftDirectoryException() = default;
	~FileOutsideMinecraftDirectoryException() = default;
	FileOutsideMinecraftDirectoryException(const std::filesystem::path& path, const std::filesystem::path& minecraft_directory);

	const char* what() const noexcept;

	bool operator==(const FileOutsideMinecraftDirectoryException& other) const;
	bool operator!=(const FileOutsideMinecraftDirectoryException& other) const;
};

#endif /*FILEOUTSIDEMINECRAFTDIRECOTYEXCEPTION_H_*/