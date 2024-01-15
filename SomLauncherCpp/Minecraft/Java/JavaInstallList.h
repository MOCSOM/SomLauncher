#ifndef JAVA_JAVAINSTALLLIST_H_
#define JAVA_JAVAINSTALLLIST_H_

#include <QAbstractListModel>
#include <QDebug>
#include <QObject>
#include <QRegularExpression>
#include <QtNetwork>
#include <qxmlstream.h>

#include "../BaseVersionList.h"
#include "../Launch/Task/Task.h"

#include "../MMCStrings.h"
#include "../VersionFilterData.h"
#include "JavaCheckerJob.h"
#include "JavaCheckerJob.h"
#include "JavaInstall.h"
#include "JavaInstallList.h"
#include "JavaUtils.h"

class JavaListLoadTask;

bool sortJavas(BaseVersionPtr left, BaseVersionPtr right);

class JavaInstallList : public BaseVersionList
{
    Q_OBJECT

private:
    enum class Status
    {
        NotDone,
        InProgress,
        Done
    };

protected:
    Status m_status = Status::NotDone;
    std::shared_ptr<JavaListLoadTask> m_loadTask;
    QList<BaseVersionPtr> m_vlist;

public:
    explicit JavaInstallList(QObject* parent = 0);
    ~JavaInstallList() noexcept = default;

    Task::Ptr getLoadTask() override;
    bool isLoaded() override;
    const BaseVersionPtr at(int i) const override;
    int count() const override;
    void sortVersions() override;

    QVariant data(const QModelIndex& index, int role) const override;
    RoleList providesRoles() const override;

public slots:
    void updateListData(QList<BaseVersionPtr> versions) override;

protected:
    void load();
    Task::Ptr getCurrentTask();
};


class JavaListLoadTask : public Task
{
    Q_OBJECT

protected:
    std::shared_ptr<JavaCheckerJob> m_job;
    JavaInstallList* m_list;
    JavaInstall* m_currentRecommended;

public:
    explicit JavaListLoadTask(JavaInstallList* vlist);
    virtual ~JavaListLoadTask() = default;

    void executeTask() override;

public slots:
    void javaCheckerFinished();
};

#endif // !JAVA_JAVAINSTALLLIST_H_