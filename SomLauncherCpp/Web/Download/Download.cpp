#include "Download.h"

std::filesystem::path web::download::downloadFile(const std::string& url, const std::filesystem::path& destanation_file,
	std::shared_ptr<CallbackNull> callback, const std::string& sha1, bool lzma_compressed)
{
	QFileInfo fi(destanation_file);
	if (fi.exists() && fi.isFile())
	{
		//Do stuff...
	}


	DownloadManager download_manager(destanation_file);
	download_manager.downloadFile(QUrl::fromUserInput(url.c_str()));

	return destanation_file;
}
