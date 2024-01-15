#ifndef MINECRAFT_USABLE_H_
#define MINECRAFT_USABLE_H_

#include <cstddef>
#include <memory>

class Usable;

/**
 * Base class for things that can be used by multiple other things and we want to track the use count.
 *
 * @see UseLock
 */
class Usable
{
    friend class UseLock;

private:
    std::size_t m_useCount = 0;

public:
    std::size_t useCount() const;
    bool isInUse() const;

protected:
    virtual void decrementUses();
    virtual void incrementUses();
};

/**
 * Lock class to use for keeping track of uses of other things derived from Usable
 *
 * @see Usable
 */
class UseLock
{
private:
    std::shared_ptr<Usable> m_usable;

public:
    UseLock(std::shared_ptr<Usable> usable);
    ~UseLock();
};

#endif // !MINECRAFT_USABLE_H_