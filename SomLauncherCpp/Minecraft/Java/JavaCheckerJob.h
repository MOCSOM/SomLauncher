#ifndef JAVA_JAVACHECKERJOB_H_
#define JAVA_JAVACHECKERJOB_H_

#include <QtNetwork>
#include <QDebug>

#include <memory>

#include "JavaChecker.h"
#include "../Launch/Task/Task.h"

// FIXME: this just seems horribly redundant
class JavaCheckerJob : public Task
{
	Q_OBJECT

private:
	QString m_job_name;
	QList<JavaCheckerPtr> javacheckers;
	QList<JavaCheckResult> javaresults;
	int num_finished = 0;

public:
	explicit JavaCheckerJob(QString job_name);
	virtual ~JavaCheckerJob() = default;

	bool addJavaCheckerAction(JavaCheckerPtr base);
	QList<JavaCheckResult> getResults();

private slots:
	void partFinished(JavaCheckResult result);

protected:
	virtual void executeTask() override;
};

typedef std::shared_ptr<JavaCheckerJob> JavaCheckerJobPtr;

#endif // !JAVA_JAVACHECKERJOB_H_