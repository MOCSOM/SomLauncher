#pragma once

#include <filesystem>

#include <Windows.h>

#include "qzipreader_p.h"
#include "qzipwriter_p.h"

namespace Additionals
{
	namespace archives
	{
		void compressFile(std::string zipfile, std::string directory);

		void decompressFile(const QZipReader& zip, const QZipReader::FileInfo& file, const std::string& directory);

		std::string decompressArchive(const QZipReader& zip, const std::string& directory);

	}	
}