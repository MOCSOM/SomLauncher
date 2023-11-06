#include "NativesInstaller.h"

std::vector<std::filesystem::path> MinecraftCpp::natives::getNativesUrls()
{
	//FIXME: Поменять определение natives на автоматику и сделать на разные платформы
	std::vector<std::filesystem::path> returned_urls =
	{
		"https://build.lwjgl.org/stable/windows/x64/lwjgl.dll",
		"https://build.lwjgl.org/stable/windows/x64/glfw.dll",
		"https://build.lwjgl.org/stable/windows/x64/jemalloc.dll",
		"https://build.lwjgl.org/stable/windows/x64/OpenAL.dll",
		"https://build.lwjgl.org/stable/windows/x64/lwjgl_opengl.dll",
		"https://build.lwjgl.org/stable/windows/x64/lwjgl_stb.dll"
	};
	return returned_urls;
}

void MinecraftCpp::natives::downloadNatives(const std::filesystem::path& path, CallbackNull* callback)
{
	std::filesystem::create_directory(path);

	for (auto& elem : getNativesUrls())
	{
		DownloadFile(elem.u8string(), path.u8string(), callback);
	}
}
