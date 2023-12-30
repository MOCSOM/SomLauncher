#ifndef LIBRARIESDOWNLOADINFO_H_
#define LIBRARIESDOWNLOADINFO_H_

#include <string>
#include <unordered_map>

#include "LibraryDownloadInfo.h"

class LibrariesDownloadInfo
{
private:
	LibraryDownloadInfo artifact;
	std::unordered_map<std::string, LibraryDownloadInfo> classifiers;

public:
	LibrariesDownloadInfo() = default;
	LibrariesDownloadInfo(const LibraryDownloadInfo& artifact);
	LibrariesDownloadInfo(const LibraryDownloadInfo& artifact,
		const std::unordered_map<std::string, LibraryDownloadInfo>& classifiers);

public:
	const LibraryDownloadInfo& getArtifact() const;
	const std::unordered_map<std::string, LibraryDownloadInfo>& getClassifiers() const;

public:
	bool isEmpty() const;
};

#endif // !LIBRARIESDOWNLOADINFO_H_
