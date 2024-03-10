#include "FunThread.h"

FunctionThread::FunctionThread(FunctionType func, QObject* parent)
	: QThread(parent), m_function(func) {}

void FunctionThread::run()
{
	if (this->m_function)
	{
		this->m_function(); // Вызываем переданную функцию в другом потоке
	}
}