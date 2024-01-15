#ifndef MINECRAFT_LOGGEDPROCESS_H_
#define MINECRAFT_LOGGEDPROCESS_H_

#include <QProcess>
#include <QDebug>

#include <sys.h>
#include <thread>

#if defined Q_OS_WIN32
#include <windows.h>
#include <processthreadsapi.h>
#endif

#include "MessageLevel.h"

QStringList reprocess(const QByteArray& data, QString& leftover);

/*
 * This is a basic process.
 * It has line-based logging support and hides some of the nasty bits.
 */
class LoggedProcess : public QProcess
{
    Q_OBJECT

public:
    enum State
    {
        NotRunning,
        Starting,
        FailedToStart,
        Running,
        Finished,
        Crashed,
        Aborted
    };

private:
    QString m_err_leftover;
    QString m_out_leftover;
    bool m_killed = false;
    State m_state = NotRunning;
    int m_exit_code = 0;
    bool m_is_aborting = false;
    bool m_is_detachable = false;

public:
    explicit LoggedProcess(QObject* parent = 0);
    virtual ~LoggedProcess();

    State state() const;
    int exitCode() const;
    qint64 processId() const;

    void setDetachable(bool detachable);

signals:
    void log(QStringList lines, MessageLevel::Enum level);
signals:
    void stateChanged(LoggedProcess::State state);

public slots:
    /**
     * @brief kill the process - equivalent to kill -9
     */
    void kill();


private slots:
    void on_stdErr();
    void on_stdOut();
    void on_exit(int exit_code, QProcess::ExitStatus status);
    void on_error(QProcess::ProcessError error);
    void on_stateChange(QProcess::ProcessState state);

private:
    void changeState(LoggedProcess::State state);
};

#endif // !MINECRAFT_LOGGEDPROCESS_H_
