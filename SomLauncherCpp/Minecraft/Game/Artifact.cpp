#include "Artifact.h"

Artifact::Artifact()
{
}

Artifact::Artifact(const std::string& group,
	const std::string& name,
	const std::string& version,
	const std::string& classifier,
	const std::string& extension)
	: group(group), name(name), version(version),
	classifier(classifier), extension(extension.empty() ? "jar" : extension)
{
	std::string file_name = name + "-" + version;
	if (!classifier.empty())
	{
		file_name += "-" + classifier;
	}
	file_name += "." + extension;
	this->fileName = file_name;
	this->path = group + "/" + name + "/" + version + "/" + file_name;
	std::string descriptor = group + ":" + name + ":" + version;
	if (!classifier.empty())
	{
		descriptor += ":" + classifier;
	}
	if (extension != "jar")
	{
		descriptor += "@" + extension;
	}
	this->descriptor = descriptor;
}

Artifact Artifact::fromDescriptor(std::string& descriptor)
{
	std::string group, name, version, classifier, extension;
	size_t pos = 0;
	std::string delimiter = ":";
	int index = 0;
	while ((pos = descriptor.find(delimiter)) != std::string::npos)
	{
		std::string token = descriptor.substr(0, pos);
		if (index == 0)
		{
			group = token;
		}
		else if (index == 1)
		{
			name = token;
		}
		else if (index == 2)
		{
			version = token;
		}
		else if (index == 3)
		{
			classifier = token;
		}
		descriptor.erase(0, pos + delimiter.length());
		index++;
	}
	if (!descriptor.empty())
	{
		extension = descriptor;
	}
	return Artifact(group, name, version, classifier, extension);
}

const std::string& Artifact::getGroup() const
{
	return group;
}

const std::string& Artifact::getName() const
{
	return name;
}

const std::string& Artifact::getVersion() const
{
	return version;
}

const std::string& Artifact::getClassifier() const
{
	return classifier;
}

Artifact Artifact::setClassifier(const std::string& newClassifier) const
{
	return Artifact(this->group, this->name, this->version, newClassifier, this->extension);
}

const std::string& Artifact::getExtension() const
{
	return extension;
}

const std::string& Artifact::getFileName() const
{
	return fileName;
}

const std::string& Artifact::getPath() const
{
	return path;
}

std::string Artifact::getDescriptor() const
{
	return descriptor;
}