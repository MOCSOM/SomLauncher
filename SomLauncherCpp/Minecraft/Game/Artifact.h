#ifndef ARTIFACT_H_
#define ARTIFACT_H_

#include <string>
#include <sstream>
#include <stdexcept>

class Artifact
{
private:
	std::string group;
	std::string name;
	std::string version;
	std::string classifier;
	std::string extension;
	std::string fileName;
	std::string path;
	std::string descriptor;

public:
	Artifact();
	Artifact(const std::string& group, const std::string& name, const std::string& version,
		const std::string& classifier = "", const std::string& extension = "");

	static Artifact fromDescriptor(std::string& descriptor);

	const std::string& getGroup() const;

	const std::string& getName() const;

	const std::string& getVersion() const;

	const std::string& getClassifier() const;

	Artifact setClassifier(const std::string& newClassifier) const;

	const std::string& getExtension() const;

	const std::string& getFileName() const;

	const std::string& getPath() const;

	std::string getDescriptor() const;
};

#endif // !ARTIFACT_H_