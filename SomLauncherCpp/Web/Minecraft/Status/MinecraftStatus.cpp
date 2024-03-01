#include "MinecraftStatus.h"

nlohmann::json web::minecraft::status::getMinecraftStatusServer(const std::string& server_ip)
{
	std::string api_url = "https://api.mcsrvstat.us/3";
	nlohmann::json result;
	try
	{
		std::stringstream response;
		curlpp::Cleanup cleaner;
		curlpp::Easy request;

		request.setOpt(curlpp::options::Verbose(true));
		request.setOpt(curlpp::options::Url(api_url + "/" + Additionals::String::split(server_ip, ':')[0]));
		request.setOpt(curlpp::options::WriteStream(&response));

		request.perform();
		long http_code = curlpp::infos::ResponseCode::get(request);


		if (http_code != 200)
		{
			qWarning() << "code not 200";
		}

		result = nlohmann::json::parse(response.str());
	}
	catch (curlpp::LogicError& e)
	{
		qWarning() << e.what();
	}
	catch (curlpp::RuntimeError& e)
	{
		qWarning() << e.what();
	}

	return result;
}
