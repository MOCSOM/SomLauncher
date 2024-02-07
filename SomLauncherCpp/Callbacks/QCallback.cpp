#include "QCallback.h"

void QCallback::setQProgressValue(size_t value)
{
	UIThread::run(
		[&, value]()
		{
			if (this->getQProgressBar())
			{
				this->getQProgressBar()->setValue(value);
			}
		}
	);
}

void QCallback::setQLabelProggressValue(QString value)
{
	UIThread::run(
		[&, value]()
		{
			if (this->getQLabelProggress())
			{
				this->getQLabelProggress()->setText(value);
			}
		}
	);
}

void QCallback::setQLabelDownloadSpeed(QString value)
{
	UIThread::run(
		[&, value]()
		{
			if (this->getQLabelDownloadSpeed())
			{
				this->getQLabelDownloadSpeed()->setText(value);
			}
		}
	);
}

void QCallback::setQLabelDownloadTime(QString value)
{
	UIThread::run(
		[&, value]()
		{
			if (this->getQLabelDownloadTime())
			{
				this->getQLabelDownloadTime()->setText(value);
			}
		}
	);
}
