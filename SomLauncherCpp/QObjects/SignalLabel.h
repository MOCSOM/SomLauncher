#ifndef SIGNALLABEL_H_
#define SIGNALLABEL_H_

#include <qlabel.h>

class SignalLabel : public QLabel
{
	Q_OBJECT

public:
	explicit SignalLabel(QWidget* parent = nullptr);
	~SignalLabel() = default;

signals:
	void textChanged(const QString& text);
};

#endif // !SIGNALLABEL_H_