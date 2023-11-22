#ifndef SERVERDATCONFIGURATION_H_
#define SERVERDATCONFIGURATION_H_

#include <qbytearray.h>
#include <qfile.h>
#include <qdebug.h>

#include <filesystem>
#include <string>

namespace serversdat
{
	void configServersDat(const std::filesystem::path& serversdat_path,
		const std::string& server_name, const std::string& server_ip_port);

	void createServersDat(const std::filesystem::path& serversdat_path,
		const std::string& server_name, const std::string& server_ip_port);

	namespace utils
	{
		namespace createdat
		{
			QByteArray generateByteArray(const std::string& server_name,
				const std::string& server_ip_port);
		}
		namespace filedat
		{
		}
		QByteArray getByteArrayFromFile(const std::filesystem::path& serversdat_path);
		void editByteArrayServersDat(QByteArray& byte_array,
			const std::string& server_name, const std::string& server_ip_port);
		void saveByteArrayToFile(const std::filesystem::path& serversdat_path,
			const QByteArray& byte_array);
	}
}

#endif // !SERVERDATCONFIGURATION_H_