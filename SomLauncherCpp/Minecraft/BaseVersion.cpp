#include "BaseVersion.h"

bool BaseVersion::operator<(BaseVersion& a)
{
    return name() < a.name();
}

bool BaseVersion::operator>(BaseVersion& a)
{
    return name() > a.name();
}
