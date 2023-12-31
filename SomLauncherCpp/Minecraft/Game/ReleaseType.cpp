#include "ReleaseType.h"

ReleaseType::ReleaseType()
	: id(""), type(eReleaseType::UNKNOWN)
{
}

ReleaseType::ReleaseType(const std::string& id, eReleaseType type)
	: id(id), type(type)
{
}

const std::string& ReleaseType::getId() const
{
	return this->id;
}

bool ReleaseType::empty() const
{
	return this->id.empty() && this->type == eReleaseType::UNKNOWN;
}
