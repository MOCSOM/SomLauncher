#ifndef STATUS_MINECRAFTSTATUS_H_
#define STATUS_MINECRAFTSTATUS_H_

#include <QDebug>

#include <string>
#include <sstream>

#include <nlohmann/json.hpp>

#include <curlpp/cURLpp.hpp>
#include <curlpp/Easy.hpp>
#include <curlpp/Options.hpp>
#include <curlpp/Exception.hpp>
#include <curlpp/Infos.hpp>

#include "../../../Moc/Logger/MocIOStream.h"

namespace web
{
	namespace minecraft
	{
		namespace status
		{
			nlohmann::json getMinecraftStatusServer(const std::string& server_ip);
		}
	}
}


#endif // !STATUS_MINECRAFTSTATUS_H_