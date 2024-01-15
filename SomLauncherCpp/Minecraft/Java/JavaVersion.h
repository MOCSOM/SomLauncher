#ifndef JAVA_JAVAVERSION_H_
#define JAVA_JAVAVERSION_H_

#include <QString>
#include <QRegularExpression>
#include <QString>

#include "../MMCStrings.h"

// NOTE: apparently the GNU C library pollutes the global namespace with these... undef them.
#ifdef major
#undef major
#endif
#ifdef minor
#undef minor
#endif

class JavaVersion
{
private:
    QString m_string;
    int m_major = 0;
    int m_minor = 0;
    int m_security = 0;
    bool m_parseable = false;
    QString m_prerelease;

public:
    JavaVersion() = default;
    JavaVersion(const QString& rhs);

    JavaVersion& operator=(const QString& rhs);

    bool operator<(const JavaVersion& rhs);
    bool operator==(const JavaVersion& rhs);
    bool operator>(const JavaVersion& rhs);

    bool requiresPermGen() const;

    QString toString() const;

    int major() const;
    int minor() const;
    int security() const;
};

#endif // !JAVA_JAVAVERSION_H_