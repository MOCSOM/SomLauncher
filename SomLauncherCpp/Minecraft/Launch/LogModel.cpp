#include "LogModel.h"

LogModel::LogModel(QObject* parent)
    : QAbstractListModel(parent)
{
    this->m_content.resize(this->m_maxLines);
}

int LogModel::rowCount(const QModelIndex& parent) const
{
    if (parent.isValid())
        return 0;

    return this->m_numLines;
}

QVariant LogModel::data(const QModelIndex& index, int role) const
{
    if (index.row() < 0 || index.row() >= this->m_numLines)
        return QVariant();

    auto row = index.row();
    auto realRow = (row + this->m_firstLine) % this->m_maxLines;
    if (role == Qt::DisplayRole || role == Qt::EditRole)
    {
        return this->m_content[realRow].line;
    }
    if (role == LevelRole)
    {
        return this->m_content[realRow].level;
    }

    return QVariant();
}

void LogModel::append(MessageLevel::Enum level, QString line)
{
    if (this->m_suspended)
    {
        return;
    }
    int lineNum = (this->m_firstLine + this->m_numLines) % this->m_maxLines;
    // overflow
    if (this->m_numLines == this->m_maxLines)
    {
        if (this->m_stopOnOverflow)
        {
            // nothing more to do, the buffer is full
            return;
        }
        beginRemoveRows(QModelIndex(), 0, 0);
        this->m_firstLine = (this->m_firstLine + 1) % this->m_maxLines;
        --this->m_numLines;
        endRemoveRows();
    }
    else if (this->m_numLines == this->m_maxLines - 1 && this->m_stopOnOverflow)
    {
        level = MessageLevel::Fatal;
        line = this->m_overflowMessage;
    }
    beginInsertRows(QModelIndex(), this->m_numLines, this->m_numLines);
    ++this->m_numLines;
    this->m_content[lineNum].level = level;
    this->m_content[lineNum].line = line;
    endInsertRows();
}

void LogModel::clear()
{
    beginResetModel();
    this->m_firstLine = 0;
    this->m_numLines = 0;
    endResetModel();
}

void LogModel::suspend(bool suspend)
{
    this->m_suspended = suspend;
}

bool LogModel::suspended() const
{
    return this->m_suspended;
}

QString LogModel::toPlainText()
{
    QString out;
    out.reserve(this->m_numLines * 80);
    for (int i = 0; i < this->m_numLines; i++)
    {
        QString& line = this->m_content[(this->m_firstLine + i) % m_maxLines].line;
        out.append(line + '\n');
    }
    out.squeeze();
    return out;
}

int LogModel::getMaxLines() const
{
    return this->m_maxLines;
}

void LogModel::setMaxLines(int maxLines)
{
    // no-op
    if (maxLines == this->m_maxLines)
    {
        return;
    }
    // if it all still fits in the buffer, just resize it
    if (this->m_firstLine + this->m_numLines < this->m_maxLines)
    {
        this->m_maxLines = maxLines;
        this->m_content.resize(maxLines);
        return;
    }
    // otherwise, we need to reorganize the data because it crosses the wrap boundary
    QVector<entry> newContent;
    newContent.resize(maxLines);
    if (this->m_numLines <= maxLines)
    {
        // if it all fits in the new buffer, just copy it over
        for (int i = 0; i < this->m_numLines; i++)
        {
            newContent[i] = this->m_content[(this->m_firstLine + i) % this->m_maxLines];
        }
        this->m_content.swap(newContent);
    }
    else
    {
        // if it doesn't fit, part of the data needs to be thrown away (the oldest log messages)
        int lead = this->m_numLines - maxLines;
        beginRemoveRows(QModelIndex(), 0, lead - 1);
        for (int i = 0; i < maxLines; i++)
        {
            newContent[i] = this->m_content[(this->m_firstLine + lead + i) % this->m_maxLines];
        }
        this->m_numLines = this->m_maxLines;
        this->m_content.swap(newContent);
        endRemoveRows();
    }
    this->m_firstLine = 0;
    this->m_maxLines = maxLines;
}

void LogModel::setStopOnOverflow(bool stop)
{
    this->m_stopOnOverflow = stop;
}

void LogModel::setOverflowMessage(const QString& overflowMessage)
{
    this->m_overflowMessage = overflowMessage;
}

void LogModel::setLineWrap(bool state)
{
    if (this->m_lineWrap != state)
    {
        this->m_lineWrap = state;
    }
}

bool LogModel::wrapLines() const
{
    return m_lineWrap;
}