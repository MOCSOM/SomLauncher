﻿#ifndef FUNTHREAD_H_
#define FUNTHREAD_H_

#include <QThread>

class FunctionThread : public QThread 
{
    Q_OBJECT

public:
    using FunctionType = void(*)(); // Определяем тип указателя на функцию

    FunctionThread(FunctionType func);

protected:
    void run() override;

private:
    FunctionType m_function;
};

#endif /*!FUNTHREAD_H_*/