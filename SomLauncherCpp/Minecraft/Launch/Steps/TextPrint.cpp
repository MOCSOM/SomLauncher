#include "TextPrint.h"

TextPrint::TextPrint(LaunchTask* parent, const QStringList& lines, MessageLevel::Enum level)
    : LaunchStep(parent), m_lines(lines), m_level(level)
{
}

TextPrint::TextPrint(LaunchTask* parent, const QString& line, MessageLevel::Enum level)
    : LaunchStep(parent), m_level(level)
{
    this->m_lines.append(line);
}

void TextPrint::executeTask()
{
    emit logLines(this->m_lines, this->m_level);
    emitSucceeded();
}

bool TextPrint::canAbort() const
{
    return true;
}

bool TextPrint::abort()
{
    emitFailed("Aborted.");
    return true;
}