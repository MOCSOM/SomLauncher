#ifndef SETTINGS_INIFILE_H_
#define SETTINGS_INIFILE_H_

#include <QFile>
#include <QTextStream>
#include <QStringList>
#include <QSaveFile>
#include <QDebug>
#include <QString>
#include <QVariant>
#include <QIODevice>

#include <fstream>
#include <filesystem>

// Sectionless INI parser (for instance config files)
class INIFile : public QMap<QString, QVariant>
{
public:
	explicit INIFile();
	~INIFile() = default;

	bool loadFile(QByteArray file);
	bool loadFile(QString fileName);
	bool saveFile(QString fileName);

	QVariant get(QString key, QVariant def) const;
	void set(QString key, QVariant val);
	static QString unescape(QString orig);
	static QString escape(QString orig);
};

#endif // !SETTINGS_INIFILE_H_