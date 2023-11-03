#ifndef LIBRARY_H_
#define LIBRARY_H_

#include <string>
#include <map>
#include <vector>

#include "../Utils/Validation.h"
#include "../Game/Artifact.h"
#include "LibrariesDownloadInfo.h"
#include "ExtractRules.h"

class Library : public Validation {
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

	Library(Artifact artifact) {
		this->artifact = artifact;
	}

	Library(Artifact artifact, std::string url, LibrariesDownloadInfo downloads) {
		this->artifact = artifact;
		this->url = url;
		this->downloads = downloads;
	}

	Library(Artifact artifact, std::string url, LibrariesDownloadInfo downloads, std::vector<std::string> checksums, ExtractRules extract, std::map<std::string, std::string> natives, std::vector<CompatibilityRule> rules, std::string hint, std::string filename) {
		this->artifact = artifact;
		this->url = url;
		this->downloads = downloads;
		this->checksums = checksums;
		this->extract = extract;
		this->natives = natives;
		this->rules = rules;
		this->hint = hint;
		this->fileName = filename;
	}

	std::string getGroupId() {
		return artifact.getGroup();
	}

	std::string getArtifactId() {
		return artifact.getName();
	}

	std::string getName() {
		return artifact.getName();
	}

	std::string getVersion() {
		return artifact.getVersion();
	}

	std::string getClassifier() {
		if (artifact.getClassifier().empty()) {
			if (!natives.empty() && natives.find(OS) != natives.end()) {
				return natives[OS];
			}
			else {
				return "";
			}
		}
		else {
			return artifact.getClassifier();
		}
	}

	ExtractRules getExtract() {
		return extract;
	}

	bool appliesToCurrentEnvironment() {
		return CompatibilityRule::appliesToCurrentEnvironment(rules);
	}

	bool isNative() {
		return !natives.empty() && appliesToCurrentEnvironment();
	}

	LibraryDownloadInfo getRawDownloadInfo() {
		if (downloads != nullptr) {
			if (isNative()) {
				std::unordered_map a = downloads.getClassifiers();
				return a[getClassifier()];
			}
			else {
				return downloads.getArtifact();
			}
		}
		else {
			return LibraryDownloadInfo();
		}
	}

	std::string getPath() {
		LibraryDownloadInfo temp = getRawDownloadInfo();
		if (!temp.empty() && !temp.getPath().empty()) {
			return temp.getPath();
		}
		else {
			return artifact.setClassifier(getClassifier()).getPath();
		}
	}

	LibraryDownloadInfo getDownload() {
		LibraryDownloadInfo temp = getRawDownloadInfo();
		std::string path = getPath();
		return LibraryDownloadInfo(
			path,
			!temp.empty() ? temp.getUrl() : url.empty() ? "https://libraries.minecraft.net/" + path : url + path,
			!temp.empty() ? temp.getSha1() : "",
			!temp.empty() ? temp.getSize() : 0
		);
	}

	bool hasDownloadURL() {
		LibraryDownloadInfo temp = getRawDownloadInfo();
		if (!temp.empty()) {
			return !temp.getUrl().empty();
		}
		else {
			return !url.empty();
		}
	}

	std::vector<std::string> getChecksums() {
		return checksums;
	}

	std::vector<CompatibilityRule> getRules() {
		return rules;
	}

	std::string getHint() {
		return hint;
	}

	std::string getFileName() {
		return fileName;
	}

	bool is(const std::string& groupId, const std::string& artifactId) {
		return getGroupId() == groupId && getArtifactId() == artifactId;
	}

	void setClassifier(const std::string& classifier) {
		artifact.setClassifier(classifier);
	}

	void validate() override {
		if (artifact.getName().empty()) {
			throw JsonParseException("Library.name cannot be null");
		}
	}
};
#endif // !LIBRARY_H_
