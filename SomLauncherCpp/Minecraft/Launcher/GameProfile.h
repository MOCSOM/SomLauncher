#ifndef LAUNCHER_GAMEPROFILE_H_
#define LAUNCHER_GAMEPROFILE_H_

#include <QUrl>
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonDocument>
#include <QFile>
#include <QDir>
#include <QUuid>
#include <QString>
#include <QtSystemDetection>

#include <filesystem>

#include <SomJson.h>

#include "../Download/DownloadEntry.h"
#include "LauncherRule.h"
#include "../Download/DownloadHelper.h"
//#include "ClasspathListModel.h"

DownloadEntry downloadEntryFromJson(const QString& path, Json::JsonValue& v);

class GameProfile
{
public:
	class GameArg
	{
	public:
		QString name;
		QString value;
		Rules conditions;

	public:
		GameArg(const QString& name = QString(), const QString& value = QString());
		~GameArg() = default;
	};

	/**
	 * \brief not all arguments have it's own value
	 */
	class JavaArg
	{
	public:
		QString name;
		Rules conditions;
	};

	class ClasspathEntry
	{
	public:
		QString name;
		std::filesystem::path path;
		static char classpath_separator;

	public:
		ClasspathEntry(const std::filesystem::path& path, const QString& name = QString());
		~ClasspathEntry() = default;
	};

private:
	QUuid mUuid;
	QString version_name;
	QString minecraft_version;
	QString mName;
	QString user_name;
	QString mMainClass;
	QString mAssetsIndex;
	QString mJavaVersionName = "java-runtime-alpha";
	std::filesystem::path java_path;

	QVector<DownloadEntry> mDownloads;
	QVector<GameArg> mGameArgs;
	QVector<JavaArg> mJavaArgs;
	QVector<ClasspathEntry> classpath_libraries;
	QUrl server_address;
	std::filesystem::path natives_path;
	std::filesystem::path jar_path;
	std::filesystem::path instance_path;

	bool mIsFullscreen = false;
	unsigned short mWindowWidth = 854;
	unsigned short mWindowHeight = 500;
	bool is_demo = false;

public:
	void makeClean();

public:
	[[nodiscard]] const QUuid& getUuid() const noexcept { return mUuid; }
	[[nodiscard]] const QString& getName() const noexcept { return mName; }
	[[nodiscard]] const QString& getMainClass() const noexcept { return mMainClass; }
	[[nodiscard]] const QString& getAssetsIndex() const noexcept { return mAssetsIndex; }
	[[nodiscard]] const QVector<DownloadEntry>& getDownloads() const noexcept { return mDownloads; }
	[[nodiscard]] const QVector<GameArg>& getGameArgs() const noexcept { return mGameArgs; }
	[[nodiscard]] const QVector<JavaArg>& getJavaArgs() const noexcept { return mJavaArgs; }
	[[nodiscard]] const QVector<ClasspathEntry>& getClasspathLibraries() const noexcept { return classpath_libraries; }
	[[nodiscard]] bool isFullscreen() const noexcept { return mIsFullscreen; }
	[[nodiscard]] unsigned short getWindowWidth() const noexcept { return mWindowWidth; }
	[[nodiscard]] unsigned short getWindowHeight() const noexcept { return mWindowHeight; }
	[[nodiscard]] const QString& getJavaVersionName() const noexcept { return mJavaVersionName; }
	[[nodiscard]] const QUrl& getServerAddress() const noexcept { return server_address; }
	[[nodiscard]] const std::filesystem::path& getNativesPath() const noexcept { return natives_path; }
	[[nodiscard]] const std::filesystem::path& getJarPath() const noexcept { return jar_path; }
	[[nodiscard]] const std::filesystem::path& getInstancePath() const noexcept { return /*this->instance_path.empty() ? instancePath() : */this->instance_path; }
	[[nodiscard]] const QString& getVersionName() const noexcept { return version_name; }
	[[nodiscard]] const bool& isDemo() const noexcept { return is_demo; }
	[[nodiscard]] const QString& getMinecraftVersion() const noexcept { return minecraft_version; }
	[[nodiscard]] const QString& getUsername() const noexcept { return user_name; }
	[[nodiscard]] const std::filesystem::path& getjavaPath() const noexcept { return java_path; }

public:
	void setUuid(const QUuid& uuid) noexcept { mUuid = uuid; }
	void setName(const QString& name) noexcept { mName = name; }
	void setMainClass(const QString& mainClass) noexcept { mMainClass = mainClass; }
	void setAssetsIndex(const QString& assetsIndex) noexcept { mAssetsIndex = assetsIndex; }
	void setDownloads(const QVector<DownloadEntry>& downloads) noexcept { mDownloads = downloads; }
	void setGameArgs(const QVector<GameArg>& gameArgs) noexcept { mGameArgs = gameArgs; }
	void setJavaArgs(const QVector<JavaArg>& javaArgs) noexcept { mJavaArgs = javaArgs; }
	void setClasspathLibraries(const QVector<ClasspathEntry>& libraries) noexcept { classpath_libraries = libraries; }
	void setFullscreen(bool isFullscreen) noexcept { mIsFullscreen = isFullscreen; }
	void setWindowWidth(unsigned short width) noexcept { mWindowWidth = width; }
	void setWindowHeight(unsigned short height) noexcept { mWindowHeight = height; }
	void setJavaVersionName(const QString& javaVersionName) noexcept { mJavaVersionName = javaVersionName; }
	void setServerAddress(const QUrl& serverAddress) noexcept { server_address = serverAddress; }
	void setNativesPath(const std::filesystem::path& nativesPath) noexcept { natives_path = nativesPath; }
	void setJarPath(const std::filesystem::path& jarPath) noexcept { jar_path = jarPath; }
	void setInstancePath(const std::filesystem::path& instancePath) noexcept { instance_path = instancePath; }
	void setVersionName(const QString& version_name) noexcept { this->version_name = version_name; }
	void setDemo(const bool& demo) noexcept { this->is_demo = demo; }
	void setMinecraftVersion(const QString& minecraft_version) noexcept { this->minecraft_version = minecraft_version; }
	void setUsername(const QString& user_name) noexcept { this->user_name = user_name; }
	void setjavaPath(const std::filesystem::path& java_path) noexcept { this->java_path = java_path; }

public:
	std::filesystem::path instancePath(const std::filesystem::path& minecraft_path = std::filesystem::path()) noexcept;
	std::filesystem::path setupNativesPath(const std::filesystem::path& minecraft_path = std::filesystem::path()) noexcept;


	//public:
	//	void save();
	//
	//	Json::JsonValue toJson();
	//
	//	static void fromName(GameProfile& dst, const QUuid& uuid, const QString& name);
};


#endif // !LAUNCHER_GAMEPROFILE_H_