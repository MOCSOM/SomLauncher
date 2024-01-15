#ifndef DIALOGS_PROGRESSDIALOG_H_
#define DIALOGS_PROGRESSDIALOG_H_

#include "ui_ProgressDialog.h"

#include <QDebug>
#include <QDialog>
#include <QKeyEvent>

#include <memory>

#include "../../Launch/Task/Task.h"

class ProgressDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ProgressDialog(QWidget* parent = 0);
    ~ProgressDialog();

    void updateSize();

    int execWithTask(Task* task);
    int execWithTask(std::unique_ptr<Task>&& task);
    int execWithTask(std::unique_ptr<Task>& task);

    void setSkipButton(bool present, QString label = QString());

    Task* getTask();

public slots:
    void onTaskStarted();
    void onTaskFailed(QString failure);
    void onTaskSucceeded();

    void changeStatus(const QString& status);
    void changeProgress(qint64 current, qint64 total);


private slots:
    void on_skipButton_clicked(bool checked);

protected:
    virtual void keyPressEvent(QKeyEvent* e);
    virtual void closeEvent(QCloseEvent* e);

private:
    bool handleImmediateResult(QDialog::DialogCode& result);

private:
    Ui::ProgressDialog* ui;

    Task* task;
};

#endif // !DIALOGS_PROGRESSDIALOG_H_
