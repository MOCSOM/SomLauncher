#ifndef DOWNLOAD_DOWNLOADHELPER_H_
#define DOWNLOAD_DOWNLOADHELPER_H_

#include <QPair>
#include <QString>
#include <QUrl>
#include <QDir>
#include <QMainWindow>
#include <QEventLoop>
#include <QNetworkAccessManager>
#include <QObject>
#include <QNetworkReply>
#include <QTimer>
#include <QThread>

#include "DownloadEntry.h"
//#include "Settings.h"
#include "../Launcher/GameProfile.h"
#include "../Utils/Crypto.h"
#include "../Utils/UIThread.h"
//#include "Model/User.h"

//#include "../../Form/SomLauncherMainWindow.h"

//class SomLauncherMainWindow;

class DownloadHelper
{
private:
	typedef QPair<std::filesystem::path, QUrl> D; // just for convenience

	QList<D> mDownloadList;
	quint64 mTotalDownloadSize = 0;

	QObject* mLauncher;
	QDir mGameDir;


public:
	explicit DownloadHelper(QObject* launcher = nullptr);

	void addDownloadList(const QList<DownloadEntry>& downloads, const std::filesystem::path& path, bool withHashCheck);
	void performDownload();
	void gameDownload(const GameProfile& profile, bool withUpdate);
	void setStatusUI(const QString& status);
};

#endif // !DOWNLOAD_DOWNLOADHELPER_H_