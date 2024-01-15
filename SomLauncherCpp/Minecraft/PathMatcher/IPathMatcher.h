#ifndef PATHMATCHER_IPATHMATCHER_H_
#define PATHMATCHER_IPATHMATCHER_H_

#include <QString>

#include <memory>

class IPathMatcher
{
public:
    typedef std::shared_ptr<IPathMatcher> Ptr;

public:
    IPathMatcher() = default;
    virtual ~IPathMatcher() = default;
    virtual bool matches(const QString& string) const = 0;
};

#endif // !PATHMATCHER_IPATHMATCHER_H_