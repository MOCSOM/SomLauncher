#include "NativesInstaller.h"

std::vector<std::pair<std::string, std::string>> MinecraftCpp::natives::getNativesUrls()
{
	std::string lwjgl_version = "3.3.3";
	std::vector<std::pair<std::string, std::string>> returned_urls =
	{
		{"https://build.lwjgl.org/release/" + lwjgl_version + "/" + OS + "/" + ARCH + "/lwjgl.dll", "2bf57942dff5360889f0e89c58d5acdc54e5f1ea"},
		{"https://build.lwjgl.org/release/" + lwjgl_version + "/" + OS + "/" + ARCH + "/glfw.dll", "2e19147110b9872a52814956bab151a7aa80ce58"},
		{"https://build.lwjgl.org/release/" + lwjgl_version + "/" + OS + "/" + ARCH + "/jemalloc.dll", "6403f8243ea983a225b3bcda6c821a0029ad9ee2"},
		{"https://build.lwjgl.org/release/" + lwjgl_version + "/" + OS + "/" + ARCH + "/OpenAL.dll", "96014cec517f2c55a0329a71cd99e68cab7d3242"},
		{"https://build.lwjgl.org/release/" + lwjgl_version + "/" + OS + "/" + ARCH + "/lwjgl_opengl.dll", "dc0249933f6fc2c0dafa53a3b710056597c8ee19"},
		{"https://build.lwjgl.org/release/" + lwjgl_version + "/" + OS + "/" + ARCH + "/lwjgl_stb.dll", "af3b372e2b366c5e681cd3b0640fd9fc41e0a265"}
	};
	return returned_urls;
}

void MinecraftCpp::natives::downloadNatives(const std::filesystem::path& path, std::shared_ptr<CallbackNull> callback)
{
	std::filesystem::create_directory(path);

	auto natives = getNativesUrls();
	for (auto& elem : natives)
	{
		DownloadFile(elem.first, path, callback, elem.second);
	}
}
