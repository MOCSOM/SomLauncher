#ifndef ARCHIVES_H_
#define ARCHIVES_H_

#include <filesystem>

#include <windows.h>

#include "qzipreader_p.h"
#include "qzipwriter_p.h"

namespace Additionals
{
	namespace archives
	{
		void compressFile(std::string zipfile, std::string directory);

		void decompressFile(const QZipReader& zip, const QZipReader::FileInfo& file, const std::filesystem::path& directory);

		//TODO: Изменить возвращаемое значение
		std::filesystem::path decompressArchive(const QZipReader& zip, const std::filesystem::path& directory);
	}
}

#endif /*ARCHIVES_H_*/