#ifndef ARGUMENTS_H_
#define ARGUMENTS_H_

#include <algorithm>
#include <map>
#include <string>
#include <vector>

#include "../../Utils/Lang.h"
#include "../Command/StringArgument.h"
#include "Argument.h"

class Arguments
{
private:
	std::vector<std::shared_ptr<Argument>> game;
	std::vector<std::shared_ptr<Argument>> jvm;

public:
	static const std::vector<std::shared_ptr<Argument>> DEFAULT_JVM_ARGUMENTS;
	static const std::vector<std::shared_ptr<Argument>> DEFAULT_GAME_ARGUMENTS;

public:
	Arguments() = default;
	Arguments(const std::vector<std::shared_ptr<Argument>>& game, const std::vector<std::shared_ptr<Argument>>& jvm);
	~Arguments() = default;

	const std::vector<std::shared_ptr<Argument>>& getGame() const;

	Arguments withGame(const std::vector<std::shared_ptr<Argument>>& game) const;

	const std::vector<std::shared_ptr<Argument>>& getJvm() const;

	Arguments withJvm(const std::vector<std::shared_ptr<Argument>>& jvm) const;

	Arguments addGameArguments(const std::vector<std::string>& game_arguments) const;

	Arguments addJVMArguments(const std::vector<std::string>& jvm_arguments) const;

	static Arguments merge(const Arguments& a, const Arguments& b);

	static std::vector<std::string> parseStringArguments(const std::vector<std::string>& arguments,
		const std::map<std::string, std::string>& keys);

	static std::vector<std::string> parseArguments(
		const std::vector<std::shared_ptr<Argument>>& arguments,
		const std::map<std::string, std::string>& keys,
		const std::map<std::string, bool>& features = std::map<std::string, bool>());
};

#endif // !ARGUMENTS_H_