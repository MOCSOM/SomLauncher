#include "Usable.h"

std::size_t Usable::useCount() const
{
    return this->m_useCount;
}

bool Usable::isInUse() const
{
    return this->m_useCount > 0;
}

void Usable::decrementUses()
{
    this->m_useCount--;
}

void Usable::incrementUses()
{
    this->m_useCount++;
}

UseLock::UseLock(std::shared_ptr<Usable> usable)
    : m_usable(usable)
{
    // this doesn't use shared pointer use count, because that wouldn't be correct. this count is separate.
    this->m_usable->incrementUses();
}

UseLock::~UseLock()
{
    this->m_usable->decrementUses();
}
