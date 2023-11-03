#ifndef MINECRAFTOPTIONS_H_
#define MINECRAFTOPTIONS_H_

#include <iostream>
#include <vector>
#include <unordered_map>
#include <string>

#include "Utils/Auth/AuthInfo.h"
#include "Game/Argument.h"

namespace MinecraftCpp
{
	namespace option
	{
		enum ProcessPriority
		{
			LOW,
			BELOW_NORMAL,
			NORMAL,
			ABOVE_NORMAL,
			HIGH
		};

		class LaunchOptions
		{
		public:
			std::filesystem::path gameDir = "";
			std::string java;
			std::string versionName;
			std::string versionType;
			std::string profileName;
			std::vector<std::string> gameArguments;
			std::vector<std::string> overrideJavaArguments;
			std::vector<std::string> javaArguments;
			std::vector<std::string> javaAgents;
			std::unordered_map<std::string, std::string> environmentVariables;
			int minMemory = 0;
			int maxMemory = 0;
			int metaspace = 0;
			int width = 0;
			int height = 0;
			bool fullscreen = 0;
			std::string serverIp;
			std::string wrapper;
			//Proxy proxy;
			std::string proxyUser;
			std::string proxyPass;
			bool noGeneratedJVMArgs = 0;
			std::string preLaunchCommand;
			std::string postExitCommand;
			//NativesDirectoryType nativesDirType;
			std::string nativesDir;
			ProcessPriority processPriority = NORMAL;
			//Renderer renderer;
			bool useNativeGLFW = 0;
			bool useNativeOpenAL = 0;
			bool daemon = 0;
			AuthInfo auth_info = AuthInfo("debug", UUID(), "none", "none", "none");

		public:
			LaunchOptions() {}
			~LaunchOptions() = default;
		};
	}
}

#endif // !MINECRAFTOPTIONS_H_