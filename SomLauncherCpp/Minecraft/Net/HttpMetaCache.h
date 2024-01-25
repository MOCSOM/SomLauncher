#ifndef NET_HTTPMETACACHE_H_
#define NET_HTTPMETACACHE_H_

#include <QString>
#include <QMap>
#include <QTimer>
#include <QFileInfo>
#include <QFile>
#include <QDateTime>
#include <QCryptographicHash>
#include <QDebug>
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>

#include <memory>
#include <filesystem>
#include <fstream>

class MetaEntry
{
	friend class HttpMetaCache;

protected:
	QString baseId;
	QString basePath;
	QString relativePath;
	QString md5sum;
	QString etag;
	qint64 local_changed_timestamp = 0;
	QString remote_changed_timestamp; // QString for now, RFC 2822 encoded time
	bool stale = true;

protected:
	MetaEntry() = default;

public:
	bool isStale() const;
	void setStale(bool stale);
	QString getFullPath();
	QString getRemoteChangedTimestamp();
	void setRemoteChangedTimestamp(QString remote_changed_timestamp);
	void setLocalChangedTimestamp(qint64 timestamp);
	QString getETag();
	void setETag(QString etag);
	QString getMD5Sum();
	void setMD5Sum(QString md5sum);
};

typedef std::shared_ptr<MetaEntry> MetaEntryPtr;

class HttpMetaCache : public QObject
{
	Q_OBJECT

private:
	struct EntryMap
	{
		QString base_path;
		QMap<QString, MetaEntryPtr> entry_list;
	};
	QMap<QString, EntryMap> m_entries;
	QString m_index_file;
	QTimer saveBatchingTimer;

public:
	// supply path to the cache index file
	HttpMetaCache(QString path = QString());
	~HttpMetaCache();

	// get the entry solely from the cache
	// you probably don't want this, unless you have some specific caching needs.
	MetaEntryPtr getEntry(QString base, QString resource_path);

	// get the entry from cache and verify that it isn't stale (within reason)
	MetaEntryPtr resolveEntry(QString base, QString resource_path, QString expected_etag = QString());

	// add a previously resolved stale entry
	bool updateEntry(MetaEntryPtr stale_entry);

	// evict selected entry from cache
	bool evictEntry(MetaEntryPtr entry);

	void addBase(QString base, QString base_root);

	// (re)start a timer that calls SaveNow later.
	void SaveEventually();
	void Load();
	QString getBasePath(QString base);

public slots:
	void SaveNow();

private:
	// create a new stale entry, given the parameters
	MetaEntryPtr staleEntry(QString base, QString resource_path);
};

#endif // !NET_HTTPMETACACHE_H_