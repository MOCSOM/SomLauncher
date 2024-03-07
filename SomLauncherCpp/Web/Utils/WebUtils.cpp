#include "WebUtils.h"

int64_t web::utils::getFileSizeFromUrl(const std::string& url)
{
	int64_t file_size = 0;

	QEventLoop zaloop;
	QNetworkAccessManager manager;

	// ������� URL ��� �������� �����
	QUrl murl = QUrl::fromUserInput(url.c_str());

	// ������ HTTP HEAD ������ ��� ��������� ���������� � ����� (������� ��� ������)
	QNetworkRequest request(murl);
	request.setAttribute(QNetworkRequest::CustomVerbAttribute, "HEAD");

	// ��������� ������
	QNetworkReply* reply = manager.head(request);

	// ������������ � ������� � ���������� �������
	QObject::connect(reply, &QNetworkReply::finished,
		[&]()
		{
			if (reply->error() == QNetworkReply::NoError)
			{
				// �������� ������ ����� �� ���������� ������
				file_size = reply->header(QNetworkRequest::ContentLengthHeader).toLongLong();
				qDebug() << "File size:" << file_size << "bytes" << std::endl;
			}
			else
			{
				qDebug() << "Error:" << reply->errorString() << std::endl;
			}

			// ����������� �������
			reply->deleteLater();
			zaloop.exit();
		});

	zaloop.exec();
	return file_size;
}
