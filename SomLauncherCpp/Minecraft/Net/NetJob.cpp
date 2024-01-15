#include "NetJob.h"

NetJob::NetJob(QString job_name, std::shared_ptr<QNetworkAccessManager> network)
    : Task(), m_network(network)
{
    setObjectName(job_name);
}

bool NetJob::addNetAction(NetAction::Ptr action)
{
    action->m_index_within_job = downloads.size();
    this->downloads.append(action);
    part_info pi;
    this->parts_progress.append(pi);
    partProgress(this->parts_progress.count() - 1, action->currentProgress(), action->totalProgress());

    if (action->isRunning())
    {
        connect(action.get(), SIGNAL(succeeded(int)), SLOT(partSucceeded(int)));
        connect(action.get(), SIGNAL(failed(int)), SLOT(partFailed(int)));
        connect(action.get(), SIGNAL(netActionProgress(int, qint64, qint64)), SLOT(partProgress(int, qint64, qint64)));
    }
    else
    {
        this->m_todo.append(this->parts_progress.size() - 1);
    }
    return true;
}

NetAction::Ptr NetJob::operator[](int index)
{
    return this->downloads[index];
}

const NetAction::Ptr NetJob::at(const int index)
{
    return this->downloads.at(index);
}

NetAction::Ptr NetJob::first()
{
    if (this->downloads.size())
        return this->downloads[0];
    return NetAction::Ptr();
}

int NetJob::size() const
{
    return this->downloads.size();
}

QStringList NetJob::getFailedFiles()
{
    QStringList failed;
    for (auto& index : this->m_failed)
    {
        failed.push_back(this->downloads[index]->url().toString());
    }
    failed.sort();
    return failed;
}

bool NetJob::canAbort() const
{
    bool canFullyAbort = true;
    // can abort the waiting?
    for (auto& index : this->m_todo)
    {
        auto& part = this->downloads[index];
        canFullyAbort &= part->canAbort();
    }
    // can abort the active?
    for (auto& index : this->m_doing)
    {
        auto& part = this->downloads[index];
        canFullyAbort &= part->canAbort();
    }
    return canFullyAbort;
}

void NetJob::startMoreParts()
{
    if (!isRunning())
    {
        // this actually makes sense. You can put running downloads into a NetJob and then not start it until much later.
        return;
    }
    // OK. We are actively processing tasks, proceed.
    // Check for final conditions if there's nothing in the queue.
    if (!this->m_todo.size())
    {
        if (!this->m_doing.size())
        {
            if (!this->m_failed.size())
            {
                emitSucceeded();
            }
            else if (this->m_aborted)
            {
                emitAborted();
            }
            else
            {
                emitFailed(tr("Job '%1' failed to process:\n%2").arg(objectName()).arg(getFailedFiles().join("\n")));
            }
        }
        return;
    }
    // There's work to do, try to start more parts.
    while (this->m_doing.size() < 6)
    {
        if (!this->m_todo.size())
            return;
        int doThis = this->m_todo.dequeue();
        this->m_doing.insert(doThis);
        auto& part = this->downloads[doThis];
        // connect signals :D
        connect(part.get(), SIGNAL(succeeded(int)), SLOT(partSucceeded(int)));
        connect(part.get(), SIGNAL(failed(int)), SLOT(partFailed(int)));
        connect(part.get(), SIGNAL(aborted(int)), SLOT(partAborted(int)));
        connect(part.get(), SIGNAL(netActionProgress(int, qint64, qint64)),
            SLOT(partProgress(int, qint64, qint64)));
        part->start(this->m_network);
    }
}

void NetJob::executeTask()
{
    // hack that delays early failures so they can be caught easier
    QMetaObject::invokeMethod(this, "startMoreParts", Qt::QueuedConnection);
}

bool NetJob::abort()
{
    bool fullyAborted = true;
    // fail all waiting
    //this->m_failed.unite(this->m_todo);
    this->m_todo.clear();
    // abort active
    auto& toKill = this->m_doing;
    for (auto& index : toKill)
    {
        auto& part = this->downloads[index];
        fullyAborted &= part->abort();
    }
    return fullyAborted;
}

void NetJob::partProgress(int index, qint64 bytesReceived, qint64 bytesTotal)
{
    auto& slot = this->parts_progress[index];
    slot.current_progress = bytesReceived;
    slot.total_progress = bytesTotal;

    int done = this->m_done.size();
    int doing = this->m_doing.size();
    int all = this->parts_progress.size();

    qint64 bytesAll = 0;
    qint64 bytesTotalAll = 0;
    for (auto& partIdx : this->m_doing)
    {
        auto& part = this->parts_progress[partIdx];
        // do not count parts with unknown/nonsensical total size
        if (part.total_progress <= 0)
        {
            continue;
        }
        bytesAll += part.current_progress;
        bytesTotalAll += part.total_progress;
    }

    qint64 inprogress = (bytesTotalAll == 0) ? 0 : (bytesAll * 1000) / bytesTotalAll;
    auto current = static_cast<long long>(done) * 1000 + doing * inprogress;
    auto current_total = all * 1000;
    // HACK: make sure it never jumps backwards.
    // FAIL: This breaks if the size is not known (or is it something else?) and jumps to 1000, so if it is 1000 reset it to inprogress
    if (this->m_current_progress == 1000) 
    {
        this->m_current_progress = inprogress;
    }
    if (this->m_current_progress > current)
    {
        current = this->m_current_progress;
    }
    this->m_current_progress = current;
    setProgress(current, current_total);
}

void NetJob::partSucceeded(int index)
{
    // do progress. all slots are 1 in size at least
    auto& slot = this->parts_progress[index];
    partProgress(index, slot.total_progress, slot.total_progress);

    this->m_doing.remove(index);
    this->m_done.insert(index);
    this->downloads[index].get()->disconnect(this);
    startMoreParts();
}

void NetJob::partFailed(int index)
{
    this->m_doing.remove(index);
    auto& slot = this->parts_progress[index];
    if (slot.failures == 3)
    {
        this->m_failed.insert(index);
    }
    else
    {
        slot.failures++;
        this->m_todo.enqueue(index);
    }
    this->downloads[index].get()->disconnect(this);
    startMoreParts();
}

void NetJob::partAborted(int index)
{
    this->m_aborted = true;
    this->m_doing.remove(index);
    this->m_failed.insert(index);
    this->downloads[index].get()->disconnect(this);
    startMoreParts();
}