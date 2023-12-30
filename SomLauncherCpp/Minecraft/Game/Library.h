#ifndef LIBRARY_H_
#define LIBRARY_H_

#include <map>
#include <string>
#include <vector>

#include "../PlatformDefines.h"

#include "../Game/Artifact.h"
#include "../Utils/Validation.h"
#include "CompatibilityRule.h"
#include "ExtractRules.h"
#include "LibrariesDownloadInfo.h"

class Library : public Validation
{
public:
	Artifact artifact;
	std::string url;
	LibrariesDownloadInfo downloads;
	ExtractRules extract;
	std::map<std::string, std::string> natives;
	std::vector<CompatibilityRule> rules;
	std::vector<std::string> checksums;
	std::string hint;
	std::string fileName;

public:
	Library(Artifact artifact);
	Library(Artifact artifact, std::string url, LibrariesDownloadInfo downloads);
	Library(Artifact artifact, std::string url, LibrariesDownloadInfo downloads,
		std::vector<std::string> checksums, ExtractRules extract, std::map<std::string, std::string> natives,
		std::vector<CompatibilityRule> rules, std::string hint, std::string filename);

public:
	const std::string& getGroupId() const;
	const std::string& getArtifactId() const;
	const std::string& getName() const;
	const std::string& getVersion() const;
	const std::string& getClassifier();
	const ExtractRules& getExtract() const;
	const LibraryDownloadInfo& getRawDownloadInfo();
	const std::string& getPath();
	LibraryDownloadInfo getDownload();
	bool hasDownloadURL();
	const std::vector<std::string>& getChecksums() const;
	const std::vector<CompatibilityRule>& getRules() const;
	const std::string& getHint() const;
	const std::string& getFileName() const;

public:
	bool appliesToCurrentEnvironment() const;
	bool isNative() const;
	bool is(const std::string& groupId, const std::string& artifactId) const;
	void setClassifier(const std::string& classifier) const;
	void validate() noexcept(false) override;
};
#endif // !LIBRARY_H_
