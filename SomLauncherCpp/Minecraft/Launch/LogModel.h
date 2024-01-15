#ifndef LAUNCH_LOGMODEL_H_
#define LAUNCH_LOGMODEL_H_

#include <QAbstractListModel>
#include <QString>

#include "../MessageLevel.h"

class LogModel : public QAbstractListModel
{
    Q_OBJECT

private /* types */:
    struct entry
    {
        MessageLevel::Enum level;
        QString line;
    };

private: /* data */
    QVector <entry> m_content;
    int m_maxLines = 1000;
    // first line in the circular buffer
    int m_firstLine = 0;
    // number of lines occupied in the circular buffer
    int m_numLines = 0;
    bool m_stopOnOverflow = false;
    QString m_overflowMessage = "OVERFLOW";
    bool m_suspended = false;
    bool m_lineWrap = true;

private:
    Q_DISABLE_COPY(LogModel)

public:
    explicit LogModel(QObject* parent = 0);
    ~LogModel() = default;

    int rowCount(const QModelIndex& parent = QModelIndex()) const;
    QVariant data(const QModelIndex& index, int role) const;

    void append(MessageLevel::Enum level, QString line);
    void clear();

    void suspend(bool suspend);
    bool suspended() const;

    QString toPlainText();

    int getMaxLines() const;
    void setMaxLines(int maxLines);
    void setStopOnOverflow(bool stop);
    void setOverflowMessage(const QString& overflowMessage);

    void setLineWrap(bool state);
    bool wrapLines() const;

    enum Roles
    {
        LevelRole = Qt::UserRole
    };
};

#endif // !LAUNCH_LOGMODEL_H_
