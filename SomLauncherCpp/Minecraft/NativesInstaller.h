#ifndef NATIVESINSTALLER_H_
#define NATIVESINSTALLER_H_

#include <vector>
#include <filesystem>

#include "../Web/DownloadClasses.h"

namespace MinecraftCpp
{
	namespace natives
	{
		std::vector<std::filesystem::path> getNativesUrls();
		void downloadNatives(const std::filesystem::path& path, CallbackNull* callback = new CallbackNull());
	}
}

#endif // !NATIVESINSTALLER_H_