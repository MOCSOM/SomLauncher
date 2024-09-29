#ifndef STARTPROCESS_H_
#define STARTPROCESS_H_

#include <qdebug.h>
#include <QProcess>
#include <QVector>
#include <QEventLoop>
#include <QApplication>
#include <QThread>

#include <string>
#include <vector>
#include <sstream>

#include <../../../Moc/Logger/MocIOStream.h>

#include "../Additionals/Additionals.h"

namespace client
{
	int startProcess(const std::string& args);
	int startProcess(const std::vector<std::string>& args);
	int startProcess(const std::vector<std::wstring>& args);
	int startProcess(const std::vector<std::wstring>& args, const std::filesystem::path& output_file);
	int startProcess(std::vector<std::variant<std::string, std::filesystem::path, std::wstring>>& args, std::filesystem::path instance_path);

	namespace utils
	{
		int doProcess(std::unique_ptr<wchar_t[]>& args, const std::filesystem::path& output_file, std::filesystem::path workdir_path);
		int doProcess(QStringList& args, const std::filesystem::path& output_file, std::filesystem::path workdir_path);
	}
}

#endif // !STARTPROCESS_H_