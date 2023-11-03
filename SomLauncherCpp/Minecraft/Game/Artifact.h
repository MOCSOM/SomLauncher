#ifndef ARTIFACT_H_
#define ARTIFACT_H_

#include <string>
#include <sstream>
#include <stdexcept>

class Artifact {
public:
	Artifact() {}
	Artifact(const std::string& group, const std::string& name, const std::string& version) : Artifact(group, name, version, "") {}
	Artifact(const std::string& group, const std::string& name, const std::string& version, const std::string& classifier) : Artifact(group, name, version, classifier, "") {}
	Artifact(const std::string& group, const std::string& name, const std::string& version, const std::string& classifier, const std::string& extension) :
		group(group), name(name), version(version), classifier(classifier), extension(extension.empty() ? "jar" : extension) {
		std::string fileName = name + "-" + version;
		if (!classifier.empty()) {
			fileName += "-" + classifier;
		}
		fileName += "." + extension;
		this->fileName = fileName;
		this->path = group + "/" + name + "/" + version + "/" + fileName;
		std::string descriptor = group + ":" + name + ":" + version;
		if (!classifier.empty()) {
			descriptor += ":" + classifier;
		}
		if (extension != "jar") {
			descriptor += "@" + extension;
		}
		this->descriptor = descriptor;
	}

	static Artifact fromDescriptor(std::string& descriptor) {
		std::string group, name, version, classifier, extension;
		size_t pos = 0;
		std::string delimiter = ":";
		int index = 0;
		while ((pos = descriptor.find(delimiter)) != std::string::npos) {
			std::string token = descriptor.substr(0, pos);
			if (index == 0) {
				group = token;
			}
			else if (index == 1) {
				name = token;
			}
			else if (index == 2) {
				version = token;
			}
			else if (index == 3) {
				classifier = token;
			}
			descriptor.erase(0, pos + delimiter.length());
			index++;
		}
		if (!descriptor.empty()) {
			extension = descriptor;
		}
		return Artifact(group, name, version, classifier, extension);
	}

	const std::string& getGroup() const {
		return group;
	}

	const std::string& getName() const {
		return name;
	}

	const std::string& getVersion() const {
		return version;
	}

	const std::string& getClassifier() const {
		return classifier;
	}

	Artifact setClassifier(const std::string& newClassifier) const {
		return Artifact(group, name, version, newClassifier, extension);
	}

	const std::string& getExtension() const {
		return extension;
	}

	const std::string& getFileName() const {
		return fileName;
	}

	const std::string& getPath() const {
		return path;
	}

	std::string getDescriptor() const {
		return descriptor;
	}

private:
	std::string group;
	std::string name;
	std::string version;
	std::string classifier;
	std::string extension;
	std::string fileName;
	std::string path;
	std::string descriptor;
};

#endif // !ARTIFACT_H_