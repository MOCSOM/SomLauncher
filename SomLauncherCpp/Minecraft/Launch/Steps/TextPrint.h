#ifndef STEPS_TEXTPRINT_H_
#define STEPS_TEXTPRINT_H_

#include "../LaunchStep.h"
#include "../../LoggedProcess.h"
#include "../../Java/JavaChecker.h"

/*
 * FIXME: maybe do not export
 */

class TextPrint : public LaunchStep
{
    Q_OBJECT

private:
    QStringList m_lines;
    MessageLevel::Enum m_level;

public:
    explicit TextPrint(LaunchTask* parent, const QStringList& lines, MessageLevel::Enum level);
    explicit TextPrint(LaunchTask* parent, const QString& line, MessageLevel::Enum level);
    virtual ~TextPrint() = default;

    virtual void executeTask();
    virtual bool canAbort() const;
    virtual bool abort();
};

#endif // !STEPS_TEXTPRINT_H_