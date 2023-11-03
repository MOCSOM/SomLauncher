#ifndef LIBRARIESDOWNLOADINFO_H_
#define LIBRARIESDOWNLOADINFO_H_

#include <string>
#include <unordered_map>

#include "LibraryDownloadInfo.h"

class LibrariesDownloadInfo
{
public:
	LibrariesDownloadInfo(const LibraryDownloadInfo& artifact) : artifact(artifact) {}
	LibrariesDownloadInfo() {}
	LibrariesDownloadInfo(const LibraryDownloadInfo& artifact, const std::unordered_map<std::string, LibraryDownloadInfo>& classifiers) : artifact(artifact), classifiers(classifiers) {}
	LibrariesDownloadInfo(const std::nullptr_t& null);

	const LibraryDownloadInfo& getArtifact() const {
		return artifact;
	}

	const std::unordered_map<std::string, LibraryDownloadInfo>& getClassifiers() const {
		return classifiers;
	}

	bool operator==(const std::nullptr_t& null) const
	{
		if (classifiers.empty() && artifact.empty())
		{
			return false;
		}
		return true;
	}

	bool operator!=(const std::nullptr_t& null) const
	{
		return !(*this == null);
	}

private:
	LibraryDownloadInfo artifact;
	std::unordered_map<std::string, LibraryDownloadInfo> classifiers;
};

#endif // !LIBRARIESDOWNLOADINFO_H_
