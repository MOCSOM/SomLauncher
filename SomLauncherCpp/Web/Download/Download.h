#ifndef DOWNLOAD_DOWNLOAD_H_
#define DOWNLOAD_DOWNLOAD_H_

#include <QString>
#include <QUrl>
#include <QObject>
#include <QNetworkAccessManager>
#include <QEventLoop>
#include <QTimer>
#include <QThread>
#include <QNetworkReply>
#include <QFileInfo>
#include <QDir>
#include <QByteArray>

#include <filesystem>
#include <memory>
#include <string>

#include "../../Callbacks/CallbackDict.h"
#include "../../QObjects/Threads/UIThread.h"
#include "../../QObjects/Threads/LambdaTask.h"
#include "../../Hashes/Crypto.h"

namespace web
{
	namespace download
	{
		std::filesystem::path downloadFile(
			const std::string& url,
			const std::filesystem::path& destanation_file = "",
			std::shared_ptr<CallbackNull> callback = std::make_shared<CallbackNull>(),
			const std::string& sha1 = "",
			bool lzma_compressed = false);
	}
}

#endif // !DOWNLOAD_DOWNLOAD_H_
