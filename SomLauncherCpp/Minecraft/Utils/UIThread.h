#ifndef UTILS_UITHREAD_H
#define UTILS_UITHREAD_H

#include <QObject>
#include <functional>

class UIThread : public QObject
{
	Q_OBJECT

private:
	UIThread() = default;

private slots:
	void execute(void* function);

public:
	static void run(const std::function<void()>& function);
};

#endif // !UTILS_UITHREAD_H
