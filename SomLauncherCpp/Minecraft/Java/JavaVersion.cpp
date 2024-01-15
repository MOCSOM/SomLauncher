#include "JavaVersion.h"

JavaVersion::JavaVersion(const QString& rhs)
{
    operator=(rhs);
}

JavaVersion& JavaVersion::operator=(const QString& javaVersionString)
{
    this->m_string = javaVersionString;

    auto getCapturedInteger = [](const QRegularExpressionMatch& match, const QString& what) -> int
        {
            auto str = match.captured(what);
            if (str.isEmpty())
            {
                return 0;
            }
            return str.toInt();
        };

    QRegularExpression pattern;
    if (javaVersionString.startsWith("1."))
    {
        pattern = QRegularExpression("1[.](?<major>[0-9]+)([.](?<minor>[0-9]+))?(_(?<security>[0-9]+)?)?(-(?<prerelease>[a-zA-Z0-9]+))?");
    }
    else
    {
        pattern = QRegularExpression("(?<major>[0-9]+)([.](?<minor>[0-9]+))?([.](?<security>[0-9]+))?(-(?<prerelease>[a-zA-Z0-9]+))?");
    }

    auto match = pattern.match(this->m_string);
    this->m_parseable = match.hasMatch();
    this->m_major = getCapturedInteger(match, "major");
    this->m_minor = getCapturedInteger(match, "minor");
    this->m_security = getCapturedInteger(match, "security");
    this->m_prerelease = match.captured("prerelease");
    return *this;
}

bool JavaVersion::operator<(const JavaVersion& rhs)
{
    if (this->m_parseable && rhs.m_parseable)
    {
        auto major = m_major;
        auto rmajor = rhs.m_major;

        // HACK: discourage using java 9
        if (major > 8)
            major = -major;
        if (rmajor > 8)
            rmajor = -rmajor;

        if (major < rmajor)
            return true;
        if (major > rmajor)
            return false;
        if (this->m_minor < rhs.m_minor)
            return true;
        if (this->m_minor > rhs.m_minor)
            return false;
        if (this->m_security < rhs.m_security)
            return true;
        if (this->m_security > rhs.m_security)
            return false;

        // everything else being equal, consider prerelease status
        bool thisPre = !this->m_prerelease.isEmpty();
        bool rhsPre = !rhs.m_prerelease.isEmpty();
        if (thisPre && !rhsPre)
        {
            // this is a prerelease and the other one isn't -> lesser
            return true;
        }
        else if (!thisPre && rhsPre)
        {
            // this isn't a prerelease and the other one is -> greater
            return false;
        }
        else if (thisPre && rhsPre)
        {
            // both are prereleases - use natural compare...
            return Strings::naturalCompare(this->m_prerelease, rhs.m_prerelease, Qt::CaseSensitive) < 0;
        }
        // neither is prerelease, so they are the same -> this cannot be less than rhs
        return false;
    }
    else return Strings::naturalCompare(this->m_string, rhs.m_string, Qt::CaseSensitive) < 0;
}

bool JavaVersion::operator==(const JavaVersion& rhs)
{
    if (this->m_parseable && rhs.m_parseable)
    {
        return this->m_major == rhs.m_major &&
            this->m_minor == rhs.m_minor &&
            this->m_security == rhs.m_security &&
            this->m_prerelease == rhs.m_prerelease;
    }
    return this->m_string == rhs.m_string;
}

bool JavaVersion::operator>(const JavaVersion& rhs)
{
    return (!operator<(rhs)) && (!operator==(rhs));
}

bool JavaVersion::requiresPermGen() const
{
    if (this->m_parseable)
    {
        return this->m_major < 8;
    }
    return true;
}

QString JavaVersion::toString() const
{
    return this->m_string;
}

int JavaVersion::major() const
{
    return this->m_major;
}

int JavaVersion::minor() const
{
    return this->m_minor;
}

int JavaVersion::security() const
{
    return this->m_security;
}
