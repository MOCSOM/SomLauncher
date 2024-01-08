#include "INIFile.h"

INIFile::INIFile()
{
}

bool INIFile::loadFile(QByteArray file)
{
	QTextStream in(file);
	in.setEncoding(QStringConverter::Utf8);

	QStringList lines = in.readAll().split('\n');
	for (int i = 0; i < lines.count(); i++)
	{
		QString& lineRaw = lines[i];
		// Ignore comments.
		int commentIndex = 0;
		QString line = lineRaw;
		// Search for comments until no more escaped # are available
		while ((commentIndex = line.indexOf('#', static_cast<qsizetype>(commentIndex) + 1)) != -1) {
			if (commentIndex > 0 && line.at(static_cast<qsizetype>(commentIndex) - 1) == '\\') {
				continue;
			}
			line = line.left(lineRaw.indexOf('#')).trimmed();
		}

		int eqPos = line.indexOf('=');
		if (eqPos == -1)
			continue;
		QString key = line.left(eqPos).trimmed();
		QString valueStr = line.right(line.length() - eqPos - 1).trimmed();

		valueStr = unescape(valueStr);

		QVariant value(valueStr);
		this->operator[](key) = value;
	}

	return true;
}

bool INIFile::loadFile(QString fileName)
{
	QFile file(fileName);
	if (!file.open(QIODevice::ReadOnly))
		return false;
	bool success = loadFile(file.readAll());
	file.close();
	return success;
}

bool INIFile::saveFile(QString fileName)
{
	QByteArray outArray;
	for (Iterator iter = begin(); iter != end(); iter++)
	{
		QString value = iter.value().toString();
		value = escape(value);
		outArray.append(iter.key().toUtf8());
		outArray.append('=');
		outArray.append(value.toUtf8());
		outArray.append('\n');
	}

	try
	{
		std::ofstream ofs(fileName.toStdWString());
		ofs << outArray;
		ofs.close();
	}
	catch (const std::exception& e)
	{
		qCritical() << e.what();
		return false;
	}

	return true;
}

QVariant INIFile::get(QString key, QVariant def) const
{
	if (!this->contains(key))
		return def;
	else
		return this->operator[](key);
}

void INIFile::set(QString key, QVariant val)
{
	this->operator[](key) = val;
}

QString INIFile::unescape(QString orig)
{
	QString out;
	QChar prev = char(0);
	for (auto c : orig)
	{
		if (prev == '\\')
		{
			if (c == 'n')
				out += '\n';
			else if (c == 't')
				out += '\t';
			else if (c == '#')
				out += '#';
			else
				out += c;
			prev = char(0);
		}
		else
		{
			if (c == '\\')
			{
				prev = c;
				continue;
			}
			out += c;
			prev = char(0);
		}
	}
	return out;
}

QString INIFile::escape(QString orig)
{
	QString out;
	for (auto c : orig)
	{
		if (c == '\n')
			out += "\\n";
		else if (c == '\t')
			out += "\\t";
		else if (c == '\\')
			out += "\\\\";
		else if (c == '#')
			out += "\\#";
		else
			out += c;
	}
	return out;
}