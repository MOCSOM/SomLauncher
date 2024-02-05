#ifndef THREADS_LAMBDATASK_H_
#define THREADS_LAMBDATASK_H_

#include <qrunnable.h>
#include <QThread>

class Interrupted {};

template <typename T>
class LambdaTask : public QRunnable
{
private:
	T mData;

public:
	explicit LambdaTask(const T& data);

	void run() override;
};


/**
 * \brief Helper factory for simple instancing
 */
template<typename T>
static LambdaTask<T>* lambda(const T& data);

static void interruptionCheck()
{
	if (QThread::currentThread()->isInterruptionRequested())
	{
		throw Interrupted();
	}
}

//-------------------------------------------------------------------

template<typename T>
inline LambdaTask<T>::LambdaTask(const T& data)
	: mData(data)
{
}

template<typename T>
inline void LambdaTask<T>::run()
{
	try
	{
		mData();
	}
	catch (Interrupted)
	{
	}
}

template<typename T>
inline LambdaTask<T>* lambda(const T& data)
{
	return new LambdaTask<T>(data);
}

#endif // !THREADS_LAMBDATASK_H_


