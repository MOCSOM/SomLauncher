#ifndef GAME_RELEASETYPE_H_
#define GAME_RELEASETYPE_H_

#include <string>

struct ReleaseType
{
public:
	enum eReleaseType
	{
		RELEASE,
		SNAPSHOT,
		MODIFIED,
		OLD_BETA,
		OLD_ALPHA,
		UNKNOWN
	}
	type;

private:
	std::string id;

public:
	ReleaseType();
	ReleaseType(const std::string& id, eReleaseType type = eReleaseType::UNKNOWN);
	~ReleaseType() = default;

public:
	const std::string& getId() const;

public:
	bool empty() const;
};

#endif // !GAME_RELEASETYPE_H_