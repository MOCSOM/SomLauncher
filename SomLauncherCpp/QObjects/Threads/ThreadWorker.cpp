#include "ThreadWorker.h"

Worker::Worker(QObject* thingy, QObject* parent)
	: QObject(nullptr), m_thingy(thingy)
{
	QTimer* timer = new QTimer(this);
	timer->setSingleShot(true);
	timer->start(1000);
	connect(timer, SIGNAL(timeout()), this, SLOT(doWork()));

	QThread* thread = new QThread(parent);
	this->moveToThread(thread);
	thread->start();
}

void Worker::doWork()
{
	QThread* thisthread = this->thread();
	QThread* mainthread = QCoreApplication::instance()->thread();
	delete m_thingy;
}
