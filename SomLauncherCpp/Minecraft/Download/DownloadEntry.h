#ifndef DOWNLOAD_DOWNLOADENTRY_H_
#define DOWNLOAD_DOWNLOADENTRY_H_

#include <QString>
#include <QVector>
#include <QPair>
#include <QUrl>
#include <QByteArray>

#include <filesystem>

#include "../Launcher/LauncherRule.h"

struct DownloadEntry
{
	std::filesystem::path mLocalPath;
	QUrl mUrl;
	uint64_t mSize = 0;
	bool mExtract = false;
	QString mHash;
	Rules mConditions;
};

inline bool operator==(const DownloadEntry& l, const DownloadEntry& r)
{
	return l.mLocalPath == r.mLocalPath;
}
inline uint qHash(const DownloadEntry& t)
{
	return qHash(t.mLocalPath.string().c_str());
}

#endif // !DOWNLOAD_DOWNLOADENTRY_H_