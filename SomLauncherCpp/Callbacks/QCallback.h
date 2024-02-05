#ifndef CALLBACKS_QCALLBACK_H_
#define CALLBACKS_QCALLBACK_H_

#include <QProgressbar>
#include <QCoreapplication>
#include <QLabel>

#include <iostream>
#include <memory>

#include "CallbackDict.h"
#include "../../../QObjects/SignalLabel.h"
#include "../../../Moc/Logger/MocIOStream.h"
#include "../../../QObjects/Threads/UIThread.h"

class QCallback : public CallbackNull
{
private:
	QProgressBar* progress_bar = nullptr;
	SignalLabel* progress_label = nullptr;
	quint64 total_download_size = 0;

public:
	QCallback() = default;
	~QCallback() = default;

public:
	[[nodiscard]] QProgressBar* getQProgressBar() const { return this->progress_bar; }
	[[nodiscard]] SignalLabel* getQLabelProggress() const { return this->progress_label; }
	[[nodiscard]] quint64 getTotalDownloadSize() const override { return this->total_download_size; }

public:
	void setQProgressBar(QProgressBar* progress_bar) override { this->progress_bar = progress_bar; }
	void setQLabelProggress(SignalLabel* progress_label) override { this->progress_label = progress_label; }
	void setTotalDownloadSize(quint64 value) override { this->total_download_size = value; }

public:
	void setQProgressValue(size_t value);
	void setQLabelProggressValue(QString value);

};

#endif // !CALLBACKS_QCALLBACK_H_
