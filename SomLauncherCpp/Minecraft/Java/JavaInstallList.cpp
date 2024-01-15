#include "JavaInstallList.h"

bool sortJavas(BaseVersionPtr left, BaseVersionPtr right)
{
    auto rleft = std::dynamic_pointer_cast<JavaInstall>(left);
    auto rright = std::dynamic_pointer_cast<JavaInstall>(right);
    return (*rleft) > (*rright);
}

JavaInstallList::JavaInstallList(QObject* parent)
	: BaseVersionList(parent)
{
}

Task::Ptr JavaInstallList::getLoadTask()
{
    load();
    return getCurrentTask();
}

bool JavaInstallList::isLoaded()
{
    return this->m_status == JavaInstallList::Status::Done;
}

const BaseVersionPtr JavaInstallList::at(int i) const
{
    return this->m_vlist.at(i);
}

int JavaInstallList::count() const
{
    return this->m_vlist.count();
}

void JavaInstallList::sortVersions()
{
    beginResetModel();
    std::sort(this->m_vlist.begin(), this->m_vlist.end(), sortJavas);
    endResetModel();
}

QVariant JavaInstallList::data(const QModelIndex& index, int role) const
{
    if (!index.isValid())
        return QVariant();

    if (index.row() > count())
        return QVariant();

    auto version = std::dynamic_pointer_cast<JavaInstall>(this->m_vlist[index.row()]);
    switch (role)
    {
    case VersionPointerRole:
        return QVariant::fromValue(this->m_vlist[index.row()]);
    case VersionIdRole:
        return version->descriptor();
    case VersionRole:
        return version->id.toString();
    case RecommendedRole:
        return version->recommended;
    case PathRole:
        return version->path;
    case ArchitectureRole:
        return version->arch;
    default:
        return QVariant();
    }
}

JavaInstallList::RoleList JavaInstallList::providesRoles() const
{
    return { VersionPointerRole, VersionIdRole, VersionRole, RecommendedRole, PathRole, ArchitectureRole };
}

void JavaInstallList::updateListData(QList<BaseVersionPtr> versions)
{
    beginResetModel();
    this->m_vlist = versions;
    sortVersions();
    if (this->m_vlist.size())
    {
        auto best = std::dynamic_pointer_cast<JavaInstall>(this->m_vlist[0]);
        best->recommended = true;
    }
    endResetModel();
    this->m_status = Status::Done;
    this->m_loadTask.reset();
}

void JavaInstallList::load()
{
    if (this->m_status != Status::InProgress)
    {
        this->m_status = Status::InProgress;
        this->m_loadTask = std::make_shared<JavaListLoadTask>(this);
        this->m_loadTask->start();
    }
}

Task::Ptr JavaInstallList::getCurrentTask()
{
    if (this->m_status == Status::InProgress)
    {
        return this->m_loadTask;
    }
    return nullptr;
}

JavaListLoadTask::JavaListLoadTask(JavaInstallList* vlist)
    : Task(), m_list(vlist), m_currentRecommended(nullptr)
{
}

void JavaListLoadTask::executeTask()
{
    setStatus(tr("Detecting Java installations..."));

    JavaUtils ju;
    QList<QString> candidate_paths = ju.FindJavaPaths();

    this->m_job = std::make_shared<JavaCheckerJob>("Java detection");
    connect(this->m_job.get(), &Task::finished, this, &JavaListLoadTask::javaCheckerFinished);
    connect(this->m_job.get(), &Task::progress, this, &Task::setProgress);

    qDebug() << "Probing the following Java paths: ";
    int id = 0;
    for (QString candidate : candidate_paths)
    {
        qDebug() << " " << candidate;

        auto candidate_checker = std::make_shared<JavaChecker>();
        candidate_checker->m_path = candidate;
        candidate_checker->m_id = id;
        m_job->addJavaCheckerAction(JavaCheckerPtr(candidate_checker));

        id++;
    }

    this->m_job->start();
}

void JavaListLoadTask::javaCheckerFinished()
{
    QList<JavaInstallPtr> candidates;
    auto results = this->m_job->getResults();

    qDebug() << "Found the following valid Java installations:";
    for (JavaCheckResult result : results)
    {
        if (result.validity == JavaCheckResult::Validity::Valid)
        {
            JavaInstallPtr javaVersion = std::make_shared<JavaInstall>();

            javaVersion->id = result.javaVersion;
            javaVersion->arch = result.mojangPlatform;
            javaVersion->path = result.path;
            candidates.append(javaVersion);

            qDebug() << " " << javaVersion->id.toString() << javaVersion->arch << javaVersion->path;
        }
    }

    QList<BaseVersionPtr> javas_bvp;
    for (auto& java : candidates)
    {
        //qDebug() << java->id << java->arch << " at " << java->path;
        BaseVersionPtr bp_java = std::dynamic_pointer_cast<BaseVersion>(java);

        if (bp_java)
        {
            javas_bvp.append(java);
        }
    }

    this->m_list->updateListData(javas_bvp);
    emitSucceeded();
}