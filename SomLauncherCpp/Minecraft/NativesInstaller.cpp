#include "NativesInstaller.h"

std::vector<std::string> MinecraftCpp::natives::getNativesUrls()
{
	//FIXME: Поменять определение natives на автоматику и сделать на разные платформы
	std::vector<std::string> returned_urls =
	{
		"https://build.lwjgl.org/stable/" + OS + "/" + ARCH + "/lwjgl.dll",
		"https://build.lwjgl.org/stable/" + OS + "/" + ARCH + "/glfw.dll",
		"https://build.lwjgl.org/stable/" + OS + "/" + ARCH + "/jemalloc.dll",
		"https://build.lwjgl.org/stable/" + OS + "/" + ARCH + "/OpenAL.dll",
		"https://build.lwjgl.org/stable/" + OS + "/" + ARCH + "/lwjgl_opengl.dll",
		"https://build.lwjgl.org/stable/" + OS + "/" + ARCH + "/lwjgl_stb.dll"
	};
	return returned_urls;
}

void MinecraftCpp::natives::downloadNatives(const std::filesystem::path& path, std::shared_ptr<CallbackNull> callback)
{
	std::filesystem::create_directory(path);

	for (auto& elem : getNativesUrls())
	{
		DownloadFile(elem, path, callback);
	}
}
