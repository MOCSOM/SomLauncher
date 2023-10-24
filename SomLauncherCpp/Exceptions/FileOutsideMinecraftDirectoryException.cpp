#include "FileOutsideMinecraftDirectoryException.h"

const char* FileOutsideMinecraftDirectoryException::what() const noexcept
{
	return this->out_message.c_str();
}

bool FileOutsideMinecraftDirectoryException::operator==(const FileOutsideMinecraftDirectoryException& other) const
{
	return (this->path == other.path) && (this->minecraft_directory == other.minecraft_directory);
}

bool FileOutsideMinecraftDirectoryException::operator!=(const FileOutsideMinecraftDirectoryException& other) const
{
	return !(*this == other);
}

FileOutsideMinecraftDirectoryException::FileOutsideMinecraftDirectoryException(const std::filesystem::path& path, const std::filesystem::path& minecraft_direcotry)
	: path(path), minecraft_directory(minecraft_directory)
{
	this->out_message += "Tried to place " + this->path.string() + " outside " + this->minecraft_directory.string();
}