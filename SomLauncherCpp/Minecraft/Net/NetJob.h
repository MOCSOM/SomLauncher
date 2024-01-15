#ifndef NET_NETJOB_H_
#define NET_NETJOB_H_

#include <QQueue>
#include <QSet>
#include <QtNetwork>

#include "../Launch/Task/Task.h"
#include "Download.h"
#include "HttpMetaCache.h"
#include "NetAction.h"

class NetJob;

class NetJob : public Task
{
    Q_OBJECT

private:
    std::shared_ptr<QNetworkAccessManager> m_network;

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

public:
    using Ptr = std::shared_ptr<NetJob>;

    explicit NetJob(QString job_name, std::shared_ptr<QNetworkAccessManager> network);
    virtual ~NetJob() = default;

    bool addNetAction(NetAction::Ptr action);

    NetAction::Ptr operator[](int index);
    const NetAction::Ptr at(const int index);
    NetAction::Ptr first();
    int size() const;
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
};

#endif // !NET_NETJOB_H_