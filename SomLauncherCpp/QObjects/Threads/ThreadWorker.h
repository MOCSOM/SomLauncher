#ifndef THREADWORKER_H_
#define THREADWORKER_H_

#include <QObject>
#include <QThread>
#include <QTimer>
#include <QCoreApplication>

class Worker : public QObject
{
	Q_OBJECT
public:
	Worker(QObject* thingy, QObject* parent = 0);
	~Worker() = default;

private slots:
	void doWork();

signals:
	void deleteObject(QObject* thingy);

private:
	QObject* m_thingy;
};

#endif // !THREADWORKER_H_
