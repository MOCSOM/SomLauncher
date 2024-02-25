#ifndef UTILS_WEBUTILS_H_
#define UTILS_WEBUTILS_H_

#include <QDebug>
#include <QNetworkRequest>
#include <QNetworkAccessManager>
#include <QUrl>
#include <QNetworkReply>
#include <QNetworkRequest>
#include <QEventLoop>

#include <string>

#include <curlpp/cURLpp.hpp>
#include <curlpp/Easy.hpp>
#include <curlpp/Options.hpp>
#include <curlpp/Exception.hpp>
#include <curlpp/Infos.hpp>

#include "../../Moc/Logger/MocIOStream.h"

namespace web
{
	namespace utils
	{
		int64_t getFileSizeFromUrl(const std::string& url);
	}
}

#endif // !UTILS_WEBUTILS_H_