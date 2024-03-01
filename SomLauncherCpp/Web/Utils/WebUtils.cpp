#include "WebUtils.h"

int64_t web::utils::getFileSizeFromUrl(const std::string& url)
{
	int64_t file_size = 0;

	QEventLoop zaloop;
	QNetworkAccessManager manager;

	// Создаем URL для загрузки файла
	QUrl murl = QUrl::fromUserInput(url.c_str());

	// Делаем HTTP HEAD запрос для получения информации о файле (включая его размер)
	QNetworkRequest request(murl);
	request.setAttribute(QNetworkRequest::CustomVerbAttribute, "HEAD");

	// Выполняем запрос
	QNetworkReply* reply = manager.head(request);

	// Подключаемся к сигналу о завершении запроса
	QObject::connect(reply, &QNetworkReply::finished,
		[&]()
		{
			if (reply->error() == QNetworkReply::NoError)
			{
				// Получаем размер файла из заголовков ответа
				file_size = reply->header(QNetworkRequest::ContentLengthHeader).toLongLong();
				qDebug() << "File size:" << file_size << "bytes" << std::endl;
			}
			else
			{
				qDebug() << "Error:" << reply->errorString() << std::endl;
			}

			// Освобождаем ресурсы
			reply->deleteLater();
			zaloop.exit();
		});

	zaloop.exec();
	return file_size;
}
