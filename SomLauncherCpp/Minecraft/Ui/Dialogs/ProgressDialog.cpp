#include "ProgressDialog.h"

ProgressDialog::ProgressDialog(QWidget* parent)
    : QDialog(parent), ui(new Ui::ProgressDialog)
{
    ui->setupUi(this);
    this->setWindowFlags(this->windowFlags() & ~Qt::WindowContextHelpButtonHint);
    setSkipButton(false);
    changeProgress(0, 100);
}

ProgressDialog::~ProgressDialog()
{
    delete ui;
}

void ProgressDialog::updateSize()
{
    QSize qSize = QSize(480, minimumSizeHint().height());
    resize(qSize);
    setFixedSize(qSize);
}

int ProgressDialog::execWithTask(Task* task)
{
    this->task = task;
    QDialog::DialogCode result;

    if (!task)
    {
        qDebug() << "Programmer error: progress dialog created with null task.";
        return Accepted;
    }

    if (handleImmediateResult(result))
    {
        return result;
    }

    // Connect signals.
    connect(task, SIGNAL(started()), SLOT(onTaskStarted()));
    connect(task, SIGNAL(failed(QString)), SLOT(onTaskFailed(QString)));
    connect(task, SIGNAL(succeeded()), SLOT(onTaskSucceeded()));
    connect(task, SIGNAL(status(QString)), SLOT(changeStatus(const QString&)));
    connect(task, SIGNAL(progress(qint64, qint64)), SLOT(changeProgress(qint64, qint64)));

    // if this didn't connect to an already running task, invoke start
    if (!task->isRunning())
    {
        task->start();
    }
    if (task->isRunning())
    {
        changeProgress(task->getProgress(), task->getTotalProgress());
        changeStatus(task->getStatus());
        return QDialog::exec();
    }
    else if (handleImmediateResult(result))
    {
        return result;
    }
    else
    {
        return QDialog::Rejected;
    }
}

int ProgressDialog::execWithTask(std::unique_ptr<Task>&& task)
{
    connect(this, &ProgressDialog::destroyed, task.get(), &Task::deleteLater);
    return execWithTask(task.release());
}

int ProgressDialog::execWithTask(std::unique_ptr<Task>& task)
{
    connect(this, &ProgressDialog::destroyed, task.get(), &Task::deleteLater);
    return execWithTask(task.release());
}

void ProgressDialog::setSkipButton(bool present, QString label)
{
    ui->skipButton->setAutoDefault(false);
    ui->skipButton->setDefault(false);
    ui->skipButton->setFocusPolicy(Qt::ClickFocus);
    ui->skipButton->setEnabled(present);
    ui->skipButton->setVisible(present);
    ui->skipButton->setText(label);
    updateSize();
}

Task* ProgressDialog::getTask()
{
    return this->task;
}

void ProgressDialog::onTaskStarted()
{
}

void ProgressDialog::onTaskFailed(QString failure)
{
    reject();
}

void ProgressDialog::onTaskSucceeded()
{
    accept();
}

void ProgressDialog::changeStatus(const QString& status)
{
    ui->statusLabel->setText(status);
    updateSize();
}

void ProgressDialog::changeProgress(qint64 current, qint64 total)
{
    ui->taskProgressBar->setMaximum(total);
    ui->taskProgressBar->setValue(current);
}

void ProgressDialog::keyPressEvent(QKeyEvent* e)
{
    if (ui->skipButton->isVisible())
    {
        if (e->key() == Qt::Key_Escape)
        {
            on_skipButton_clicked(true);
            return;
        }
        else if (e->key() == Qt::Key_Tab)
        {
            ui->skipButton->setFocusPolicy(Qt::StrongFocus);
            ui->skipButton->setFocus();
            ui->skipButton->setAutoDefault(true);
            ui->skipButton->setDefault(true);
            return;
        }
    }
    QDialog::keyPressEvent(e);
}

void ProgressDialog::closeEvent(QCloseEvent* e)
{
    if (this->task && this->task->isRunning())
    {
        e->ignore();
    }
    else
    {
        QDialog::closeEvent(e);
    }
}

bool ProgressDialog::handleImmediateResult(QDialog::DialogCode& result)
{
    if (this->task->isFinished())
    {
        if (this->task->wasSuccessful())
        {
            result = QDialog::Accepted;
        }
        else
        {
            result = QDialog::Rejected;
        }
        return true;
    }
    return false;
}