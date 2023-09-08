#include "Archives.h"

void Additionals::archives::compressFile(std::string zipfile, std::string directory)
{
	QZipWriter c_zip(zipfile.c_str());
	c_zip.addDirectory(directory.c_str());
	c_zip.close();
}

void Additionals::archives::decompressFile(const QZipReader& zip, const QZipReader::FileInfo& file, const std::string& directory)
{
	std::filesystem::path d_file_path(directory);
	d_file_path = d_file_path.parent_path();

	DWORD attrib = GetFileAttributesW(d_file_path.wstring().c_str());
	if (attrib == INVALID_FILE_ATTRIBUTES || !(attrib & FILE_ATTRIBUTE_DIRECTORY))
	{
		if (!std::filesystem::create_directories(d_file_path))
		{
			// Обработка ошибки создания директории
			int error = GetLastError();
		}
	}

	QFile new_file(directory.c_str());

	new_file.open(QIODevice::WriteOnly);

	new_file.write(zip.fileData(file.filePath));

	new_file.close();
}


std::string Additionals::archives::decompressArchive(const QZipReader& zip, const std::string& directory)
{
	std::filesystem::path d_file_path(directory);
	d_file_path = d_file_path.parent_path();

	DWORD attrib = GetFileAttributesW(d_file_path.wstring().c_str());
	if (attrib == INVALID_FILE_ATTRIBUTES || !(attrib & FILE_ATTRIBUTE_DIRECTORY))
	{
		if (!std::filesystem::create_directories(d_file_path))
		{
			// Обработка ошибки создания директории
			int error = GetLastError();
		}
	}

	std::string return_val = "";
	bool is_first = true;

	for (auto& file : zip.fileInfoList())
	{
		if (file.isDir)
		{
			std::filesystem::create_directories(directory + "\\" + file.filePath.toStdString());
			if (is_first == true)
			{
				return_val = directory + "\\" + file.filePath.toStdString();
				is_first = false;
			}
			continue;
		}

		QFile new_file((directory + "\\" + file.filePath.toStdString()).c_str());

		new_file.open(QIODevice::WriteOnly);

		new_file.write(zip.fileData(file.filePath));

		new_file.close();
	}
	return return_val;
}