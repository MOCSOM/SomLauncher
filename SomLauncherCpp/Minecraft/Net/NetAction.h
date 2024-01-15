#ifndef NET_NETACTION_H_
#define NET_NETACTION_H_

#include <QNetworkReply>
#include <QObject>
#include <QUrl>

#include <memory>

enum JobStatus
{
    Job_NotStarted,
    Job_InProgress,
    Job_Finished,
    Job_Failed,
    Job_Aborted,
    /*
     * FIXME: this confuses the task failing with us having a fallback in the form of local data. Clear up the confusion.
     * Same could be true for aborted task - the presence of pre-existing result is a separate concern
     */
    Job_Failed_Proceed
};

class NetAction : public QObject
{
    Q_OBJECT

public:
    std::shared_ptr<QNetworkAccessManager> m_network;

    /// index within the parent job, FIXME: nuke
    int m_index_within_job = 0;

    /// the network reply
    std::shared_ptr<QNetworkReply> m_reply;

    /// source URL
    QUrl m_url;

    qint64 m_progress = 0;
    qint64 m_total_progress = 1;

protected:
    JobStatus m_status = Job_NotStarted;

protected:
    explicit NetAction();
    ~NetAction() = default;

public:
    using Ptr = std::shared_ptr<NetAction>;

    bool isRunning() const;
    bool isFinished() const;
    bool wasSuccessful() const;

    qint64 totalProgress() const;
    qint64 currentProgress() const;
    virtual bool abort();
    virtual bool canAbort();
    QUrl url() const;

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
    void start(std::shared_ptr<QNetworkAccessManager> network);

protected:
    virtual void startImpl() = 0;
};

#endif // !NET_NETACTION_H_
