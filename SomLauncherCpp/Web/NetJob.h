#ifndef WEB_NETJOB_H_
#define WEB_NETJOB_H_

#include <QtNetwork>
#include "NetAction.h"
#include "Net/QDownload.h"
#include "Net/HttpMetaCache.h"
#include "../Tasks/Task.h"

#include "../QObjects/QObjectPtr.h"

class NetJob : public Task
{
	Q_OBJECT
public:
	using Ptr = shared_qobject_ptr<NetJob>;

	explicit NetJob(QString job_name, shared_qobject_ptr<QNetworkAccessManager> network) : Task(), m_network(network)
	{
		setObjectName(job_name);
	}
	virtual ~NetJob() = default;

	bool addNetAction(NetAction::Ptr action);

	NetAction::Ptr operator[](int index)
	{
		return downloads[index];
	}
	const NetAction::Ptr at(const int index)
	{
		return downloads.at(index);
	}
	NetAction::Ptr first()
	{
		if (downloads.size())
			return downloads[0];
		return NetAction::Ptr();
	}
	int size() const
	{
		return downloads.size();
	}
	QStringList getFailedFiles();

	bool canAbort() const override;

private slots:
	void startMoreParts();

public slots:
	virtual void executeTask() override;
	virtual bool abort() override;

private slots:
	void partProgress(int index, qint64 bytesReceived, qint64 bytesTotal);
	void partSucceeded(int index);
	void partFailed(int index);
	void partAborted(int index);

private:
	shared_qobject_ptr<QNetworkAccessManager> m_network;

	struct part_info
	{
		qint64 current_progress = 0;
		qint64 total_progress = 1;
		int failures = 0;
	};
	QList<NetAction::Ptr> downloads;
	QList<part_info> parts_progress;
	QQueue<int> m_todo;
	QSet<int> m_doing;
	QSet<int> m_done;
	QSet<int> m_failed;
	qint64 m_current_progress = 0;
	bool m_aborted = false;
};

#endif // !WEB_NETJOB_H_
