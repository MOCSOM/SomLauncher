#ifndef DOWNLOAD_DOWNLOAD_H_
#define DOWNLOAD_DOWNLOAD_H_

#include <QNetworkRequest>
#include <QNetworkReply>
#include <QJsonDocument>
#include <QJsonObject>
#include <QDir>
#include <QThreadPool>

#include "DownloadEntry.h"
#include "DownloadHelper.h"
#include "../Utils/Crypto.h"
#include "../Launcher/GameProfile.h"

namespace download
{
	bool loadDownloads(GameProfile& profile);

	namespace utils
	{
		QVector<DownloadEntry> getDownloads(const QJsonObject& object);
		QString javaLibNameToPath(const QString& name);

		namespace versionjson
		{
			bool downloadJsons(const GameProfile& profile);

			namespace fabric
			{
				bool downloadJsonFabric(const GameProfile& profile);
			}
			namespace forge
			{

			}
		}
	}
}

#endif // !DOWNLOAD_DOWNLOAD_H_