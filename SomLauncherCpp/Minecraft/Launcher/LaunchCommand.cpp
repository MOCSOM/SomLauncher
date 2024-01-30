#include "LaunchCommand.h"

QStringList commandline::generateCommand(const GameProfile& profile)
{
	QStringList arg_t;

	/*arg_t.push_back(customizer.javapath());*/

	// JVM args:
	arg_t.push_back("-Xmx1024m");
	arg_t.push_back("-Xmn128m");
	arg_t.push_back("-Djava.library.path=" + QString(profile.getNativesPath().string().c_str()));

	arg_t.push_back("-cp");
	auto& versionTool = profile;
	auto& dependeny_libraries = versionTool.getClasspathLibraries();

	QStringList classpath_t;
	for (const auto& l : dependeny_libraries)
	{
		classpath_t.push_back(l.path.string().c_str());
	}

	/*for (const auto& l : versionTool.natives_libraries)
	{
		customizer.extract(customizer.libpath() + "/" + l, customizer.natpath());
	}*/

	classpath_t.push_back(/*customizer.verpath() +*/ QString(("/" + versionTool.getJarPath().string()).c_str()));
	arg_t.push_back(classpath_t.join(GameProfile::ClasspathEntry::classpath_separator));

	// Game args:
	/*customizer.replace_map["${version_name}"] = versionTool.getName();
	customizer.replace_map["${game_directory}"] = customizer.gamepath();
	customizer.replace_map["${assets_root}"] = customizer.asspath();
	customizer.replace_map["${assets_index_name}"] = versionTool.getAssetsIndex();
	customizer.replace_map["${version_type}"] = "__";*/

	arg_t.push_back(versionTool.getMainClass());
	for (const auto& gameArg : versionTool.getGameArgs())
	{
		arg_t.push_back(gameArg.name + " " + gameArg.value);
	}

	if (profile.isFullscreen())
	{
		arg_t.push_back("--fullscreen");
	}

	arg_t.push_back("--width");
	arg_t.push_back(QString::number(profile.getWindowWidth()));
	arg_t.push_back("--height");
	arg_t.push_back(QString::number(profile.getWindowHeight()));

	if (!profile.getServerAddress().isEmpty())
	{
		arg_t.push_back("--serverip");
		arg_t.push_back(profile.getServerAddress().host());
		arg_t.push_back("--serverport");
		arg_t.push_back(QString::number(profile.getServerAddress().port()));
	}

	return arg_t;
}