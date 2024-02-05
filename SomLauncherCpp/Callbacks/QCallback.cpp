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
