#ifndef WEB_NETACTION_H_
#define WEB_NETACTION_H_

#include <QObject>
#include <QUrl>
#include <memory>
#include <QNetworkReply>

#include "../QObjects/QObjectPtr.h"

enum JobStatus
{
	Job_NotStarted,
	Job_InProgress,
	Job_Finished,
	Job_Failed,
	Job_Aborted,
	/*
	 * FIXME: @NUKE this confuses the task failing with us having a fallback in the form of local data. Clear up the confusion.
	 * Same could be true for aborted task - the presence of pre-existing result is a separate concern
	 */
	Job_Failed_Proceed
};

class NetAction : public QObject
{
	Q_OBJECT

public:
	shared_qobject_ptr<QNetworkAccessManager> m_network;

	/// index within the parent job, FIXME: nuke
	int m_index_within_job = 0;

	/// the network reply
	unique_qobject_ptr<QNetworkReply> m_reply;

	/// source URL
	QUrl m_url;

	qint64 m_progress = 0;
	qint64 m_total_progress = 1;

protected:
	JobStatus m_status = Job_NotStarted;

protected:
	explicit NetAction() : QObject(nullptr) {};

public:
	using Ptr = shared_qobject_ptr<NetAction>;

	virtual ~NetAction() {};

	bool isRunning() const
	{
		return m_status == Job_InProgress;
	}
	bool isFinished() const
	{
		return m_status >= Job_Finished;
	}
	bool wasSuccessful() const
	{
		return m_status == Job_Finished || m_status == Job_Failed_Proceed;
	}

	qint64 totalProgress() const
	{
		return m_total_progress;
	}
	qint64 currentProgress() const
	{
		return m_progress;
	}
	virtual bool abort()
	{
		return false;
	}
	virtual bool canAbort()
	{
		return false;
	}
	QUrl url() const
	{
		return m_url;
	}

protected:
	virtual void startImpl() = 0;

signals:
	void started(int index);
signals:
	void netActionProgress(int index, qint64 current, qint64 total);
signals:
	void succeeded(int index);
signals:
	void failed(int index);
signals:
	void aborted(int index);

protected slots:
	virtual void downloadProgress(qint64 bytesReceived, qint64 bytesTotal) = 0;
	virtual void downloadError(QNetworkReply::NetworkError error) = 0;
	virtual void downloadFinished() = 0;
	virtual void downloadReadyRead() = 0;

public slots:
	void start(shared_qobject_ptr<QNetworkAccessManager> network)
	{
		m_network = network;
		startImpl();
	}
};

#endif // !WEB_NETACTION_H_
