#include "LibrariesDownloadInfo.h"

LibrariesDownloadInfo::LibrariesDownloadInfo(const LibraryDownloadInfo& artifact)
	: artifact(artifact)
{
}

LibrariesDownloadInfo::LibrariesDownloadInfo(const LibraryDownloadInfo& artifact, const std::unordered_map<std::string, LibraryDownloadInfo>& classifiers)
	: artifact(artifact), classifiers(classifiers)
{
}

const LibraryDownloadInfo& LibrariesDownloadInfo::getArtifact() const
{
	return this->artifact;
}

const std::unordered_map<std::string, LibraryDownloadInfo>& LibrariesDownloadInfo::getClassifiers() const
{
	return this->classifiers;
}

bool LibrariesDownloadInfo::empty() const
{
	return this->classifiers.empty() && this->artifact.empty();
}