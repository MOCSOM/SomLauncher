#include "GameJavaVersion.h"

GameJavaVersion::GameJavaVersion()
	: component(""), major_version(0)
{
}

GameJavaVersion::GameJavaVersion(const std::string& component, int major_version)
	: component(component), major_version(major_version)
{
}

const std::string& GameJavaVersion::getComponent() const
{
	return this->component;
}

const int& GameJavaVersion::getMajorVersion() const
{
	return this->major_version;
}

bool GameJavaVersion::empty() const
{
	return this->component.empty() && this->major_version == 0;
}
