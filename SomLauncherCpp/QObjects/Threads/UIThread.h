#ifndef THREADS_UITHREAD_H_
#define THREADS_UITHREAD_H_

#include <QObject>
#include <QThread>

#include <functional>

class UIThread : public QObject
{
	Q_OBJECT

private:
	UIThread() = default;

public:
	~UIThread() = default;

private slots:
	void execute(void* function);

public:
	static void run(const std::function<void()>& function);
};

#endif // !THREADS_UITHREAD_H_
