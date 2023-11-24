#include "ServerDatConfiguration.h"

void serversdat::configServersDat(const std::filesystem::path& serversdat_path,
	const std::string& server_name, const std::string& server_ip_port)
{
	QByteArray byte_array = serversdat::utils::getByteArrayFromFile(serversdat_path);
	serversdat::utils::editByteArrayServersDat(byte_array, server_name, server_ip_port);
	serversdat::utils::saveByteArrayToFile(serversdat_path, byte_array);
}

void serversdat::createServersDat(const std::filesystem::path& serversdat_path, const std::string& server_name, const std::string& server_ip_port)
{
	QByteArray byte_array =
		serversdat::utils::createdat::generateByteArray(server_name, server_ip_port);
	serversdat::utils::saveByteArrayToFile(serversdat_path, byte_array);
}

QByteArray serversdat::utils::getByteArrayFromFile(const std::filesystem::path& serversdat_path)
{
	QFile file(serversdat_path.u8string().c_str());
	file.open(QIODevice::OpenModeFlag::ReadOnly);
	if (!file.isOpen())
	{
		qWarning() << "servers dat not opened in " << serversdat_path.u8string();
	}

	return file.readAll();
}

void serversdat::utils::editByteArrayServersDat(QByteArray& byte_array,
	const std::string& server_name, const std::string& server_ip_port)
{
	//FIXME: доделать
	//qInfo() << byte_array.toHex().data();
	const char ENDING_BYTES[1]{ '00' };
	const char STARTING_FILE_BYTES[3]{ '0a','00','00' };
	const char STARTING_DIR_BYTES[3]{ '01','00','06' };
	const char STARTING_KEYS_BYTES[3]{ '08','00','02' };

	size_t count = -1;
	for (auto& byte : byte_array)
	{
		++count;
		if (count <= 2)
		{
			continue;
		}
		if (count == byte_array.size())
		{
			continue;
		}

		if (byte_array[count - 3] == 'n' && byte_array[count - 2] == 'a' &&
			byte_array[count - 1] == 'm' && byte_array[count] == 'e')
		{
			size_t iter = count + 3;
			size_t iter_str = -1;
			for (auto& name_chars : server_name)
			{
				++iter;
				++iter_str;

				if (byte_array[iter] == '08' || byte_array[iter] == '00')
				{
					byte_array.insert(iter, name_chars);
					continue;
				}

				byte_array[iter] = server_name[iter_str];
			}
		}
	}
	qInfo() << byte_array.toStdString();
}

void serversdat::utils::saveByteArrayToFile(const std::filesystem::path& serversdat_path,
	const QByteArray& byte_array)
{
	QFile file(serversdat_path.u8string().c_str());
	file.open(QIODevice::OpenModeFlag::WriteOnly);
	if (!file.isOpen())
	{
		qWarning() << "servers dat not opened in " << serversdat_path.u8string();
	}

	file.write(byte_array);
}

QByteArray serversdat::utils::createdat::generateByteArray(const std::string& server_name, const std::string& server_ip_port)
{
	unsigned char start_ip_bytes[]
	{
		0x0A, 0x00, 0x00, 0x09, 0x00, 0x07, 0x73, 0x65, 0x72, 0x76, 0x65, 0x72, 0x73, 0x0A, 0x00,
		0x00, 0x00, 0x01, 0x01, 0x00, 0x06, 0x68, 0x69, 0x64, 0x64, 0x65, 0x6E, 0x00,
		0x08, 0x00, 0x02, 0x69, 0x70, 0x00, server_ip_port.size()
	};

	unsigned char name_bytes[]
	{
		0x08, 0x00, 0x04, 0x6E, 0x61, 0x6D, 0x65, 0x00, server_name.size()
	};

	unsigned char end_bytes[]
	{
		0x00, 0x00
	};

	QByteArray byte_array = QByteArray::fromRawData((char*)start_ip_bytes, 35);

	byte_array += QByteArray::fromRawData(server_ip_port.c_str(), server_ip_port.size());

	byte_array += QByteArray::fromRawData((char*)name_bytes, 9);

	byte_array += QByteArray::fromRawData(server_name.c_str(), server_name.size());

	byte_array += QByteArray::fromRawData((char*)end_bytes, 2);

	//qInfo() << byte_array.toHex().data();//.toStdString();
	return byte_array;
}