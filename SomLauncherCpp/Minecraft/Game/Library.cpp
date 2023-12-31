#include "Library.h"

Library::Library(Artifact artifact)
	: artifact(artifact)
{
}

Library::Library(Artifact artifact, std::string url, LibrariesDownloadInfo downloads)
	: artifact(artifact), url(url), downloads(downloads)
{
}

Library::Library(
	Artifact artifact, std::string url, LibrariesDownloadInfo downloads,
	std::vector<std::string> checksums, ExtractRules extract, std::map<std::string, std::string> natives,
	std::vector<CompatibilityRule> rules, std::string hint, std::string filename)
	: artifact(artifact), url(url), downloads(downloads),
	checksums(checksums), extract(extract), natives(natives),
	rules(rules), hint(hint), fileName(fileName)
{
}

const std::string& Library::getGroupId() const
{
	return this->artifact.getGroup();
}

const std::string& Library::getArtifactId() const
{
	return this->artifact.getName();
}

const std::string& Library::getName() const
{
	return this->artifact.getName();
}

const std::string& Library::getVersion() const
{
	return this->artifact.getVersion();
}

const std::string& Library::getClassifier()
{
	if (this->artifact.getClassifier().empty())
	{
		if (!this->natives.empty() && this->natives.find(OS) != this->natives.end())
		{
			return this->natives[OS];
		}
		else {
			return "";
		}
	}
	else {
		return this->artifact.getClassifier();
	}
}

const ExtractRules& Library::getExtract() const
{
	return this->extract;
}

bool Library::appliesToCurrentEnvironment() const
{
	return CompatibilityRule::appliesToCurrentEnvironment(this->rules);
}

bool Library::isNative() const
{
	return !this->natives.empty() && appliesToCurrentEnvironment();
}

const LibraryDownloadInfo& Library::getRawDownloadInfo()
{
	if (!this->downloads.empty())
	{
		if (isNative())
		{
			std::unordered_map a = this->downloads.getClassifiers();
			return a[getClassifier()];
		}
		else
		{
			return this->downloads.getArtifact();
		}
	}
	else
	{
		return LibraryDownloadInfo();
	}
}

const std::string& Library::getPath()
{
	LibraryDownloadInfo temp = getRawDownloadInfo();
	if (!temp.empty() && !temp.getPath().empty())
	{
		return temp.getPath();
	}
	else
	{
		return artifact.setClassifier(getClassifier()).getPath();
	}
}

LibraryDownloadInfo Library::getDownload()
{
	LibraryDownloadInfo temp = getRawDownloadInfo();
	std::string path = getPath();
	return LibraryDownloadInfo
	(
		path,
		!temp.empty() ? temp.getUrl() : this->url.empty() ? "https://libraries.minecraft.net/" + path : url + path,
		!temp.empty() ? temp.getSha1() : "",
		!temp.empty() ? temp.getSize() : 0
	);
}

bool Library::hasDownloadURL()
{
	LibraryDownloadInfo temp = getRawDownloadInfo();
	if (!temp.empty())
	{
		return !temp.getUrl().empty();
	}
	else
	{
		return !this->url.empty();
	}
}

const std::vector<std::string>& Library::getChecksums() const
{
	return this->checksums;
}

const std::vector<CompatibilityRule>& Library::getRules() const
{
	return this->rules;
}

const std::string& Library::getHint() const
{
	return this->hint;
}

const std::string& Library::getFileName() const
{
	return this->fileName;
}

bool Library::is(const std::string& groupId, const std::string& artifactId) const
{
	return getGroupId() == groupId && getArtifactId() == artifactId;
}

void Library::setClassifier(const std::string& classifier) const
{
	this->artifact.setClassifier(classifier);
}

void Library::validate() noexcept(false)
{
	if (this->artifact.getName().empty())
	{
		throw JsonParseException("Library.name cannot be null");
	}
}