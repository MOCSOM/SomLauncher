#ifndef GAME_GAMEJAVAVERSION_H_
#define GAME_GAMEJAVAVERSION_H_

#include <string>

class GameJavaVersion
{
private:
	std::string component;
	int major_version;

public:
	GameJavaVersion();
	GameJavaVersion(const std::string& component, int major_version);
	~GameJavaVersion() = default;

public:
	const std::string& getComponent() const;
	const int& getMajorVersion() const;

public:
	bool empty() const;

public:
	static GameJavaVersion JAVA_17;
	static GameJavaVersion JAVA_16;
	static GameJavaVersion JAVA_8;
};

GameJavaVersion GameJavaVersion::JAVA_17 = GameJavaVersion("java-runtime-beta", 17);
GameJavaVersion GameJavaVersion::JAVA_16 = GameJavaVersion("java-runtime-alpha", 16);
GameJavaVersion GameJavaVersion::JAVA_8 = GameJavaVersion("jre-legacy", 8);

#endif // !GAME_GAMEJAVAVERSION_H_