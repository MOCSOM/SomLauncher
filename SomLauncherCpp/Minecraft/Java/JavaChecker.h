#ifndef JAVA_JAVACHECKER_H_
#define JAVA_JAVACHECKER_H_

#include <QDebug>
#include <QFile>
#include <QMap>
#include <QProcess>
#include <QProcess>
#include <QTimer>

#include <filesystem>
#include <memory>

#include "../Application.h"
#include "../Commandline.h"
#include "../QObjectPtr.h"
#include "JavaUtils.h"
#include "JavaVersion.h"

class JavaChecker;

struct JavaCheckResult
{
	QString path;
	QString mojangPlatform;
	QString realPlatform;
	JavaVersion javaVersion;
	QString javaVendor;
	QString outLog;
	QString errorLog;
	bool is_64bit = false;
	int id;
	enum class Validity
	{
		Errored,
		ReturnedInvalidData,
		Valid
	}
	validity = Validity::Errored;
};

typedef shared_qobject_ptr<QProcess> QProcessPtr;
typedef shared_qobject_ptr<JavaChecker> JavaCheckerPtr;

class JavaChecker : public QObject
{
	Q_OBJECT

private:
	QProcessPtr process;
	QTimer killTimer;
	QString m_stdout;
	QString m_stderr;

public:
	QString m_path;
	QString m_args;
	int m_id = 0;
	int m_minMem = 0;
	int m_maxMem = 0;
	int m_permGen = 64;

public:
	explicit JavaChecker(QObject* parent = nullptr);
	void performCheck();

signals:
	void checkFinished(JavaCheckResult result);

public slots:
	void timeout();
	void finished(int exitcode, QProcess::ExitStatus status);
	void error(QProcess::ProcessError err);
	void stdoutReady();
	void stderrReady();
};

#endif // !JAVA_JAVACHECKER_H_