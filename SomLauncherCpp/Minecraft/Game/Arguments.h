#ifndef ARGUMENTS_H_
#define ARGUMENTS_H_

#include <vector>
#include <string>
#include <map>
#include <algorithm>

#include "Argument.h"
#include "StringArgument.h"
#include "../Utils/Lang.h"

class Arguments {
public:
	Arguments(const std::vector<std::shared_ptr<Argument>>& game, const std::vector<std::shared_ptr<Argument>>& jvm)
		: game(game), jvm(jvm) {}

	Arguments(const std::nullptr_t& null) {}

	const std::vector<std::shared_ptr<Argument>>& getGame() const {
		return game;
	}

	Arguments withGame(const std::vector<std::shared_ptr<Argument>>& game) const {
		return Arguments(game, jvm);
	}

	const std::vector<std::shared_ptr<Argument>>& getJvm() const {
		return jvm;
	}

	Arguments withJvm(const std::vector<std::shared_ptr<Argument>>& jvm) const {
		return Arguments(game, jvm);
	}

	Arguments addGameArguments(const std::vector<std::string>& gameArguments) const {
		std::vector<std::shared_ptr<Argument>> gameArgs = game;
		for (const std::string& arg : gameArguments) {
			gameArgs.push_back(std::make_shared<StringArgument>(arg));
		}
		return Arguments(gameArgs, jvm);
	}

	Arguments addJVMArguments(const std::vector<std::string>& jvmArguments) const {
		std::vector<std::shared_ptr<Argument>> jvmArgs = jvm;
		for (const std::string& arg : jvmArguments) {
			jvmArgs.push_back(std::make_shared<StringArgument>(arg));
		}
		return Arguments(game, jvmArgs);
	}

	static Arguments merge(const Arguments& a, const Arguments& b) {
		std::vector<std::shared_ptr<Argument>> mergedGame = Lang::merge(a.getGame(), b.getGame());
		std::vector<std::shared_ptr<Argument>> mergedJvm = Lang::merge(a.getJvm(), b.getJvm());
		return Arguments(mergedGame, mergedJvm);
	}

	static std::vector<std::string> parseStringArguments(const std::vector<std::string>& arguments, const std::map<std::string, std::string>& keys) {
		std::vector<std::string> parsedArguments;
		for (const std::string& argument : arguments) {
			StringArgument strArg(argument);
			std::vector<std::string> parsed = strArg.toString(keys, std::map<std::string, bool>());
			parsedArguments.insert(parsedArguments.end(), parsed.begin(), parsed.end());
		}
		return parsedArguments;
	}

	static std::vector<std::string> parseArguments(const std::vector<std::shared_ptr<Argument>>& arguments, const std::map<std::string, std::string>& keys) {
		return parseArguments(arguments, keys, std::map<std::string, bool>());
	}

	static std::vector<std::string> parseArguments(const std::vector<std::shared_ptr<Argument>>& arguments, const std::map<std::string, std::string>& keys, const std::map<std::string, bool>& features) {
		std::vector<std::string> parsedArguments;
		for (const std::shared_ptr<Argument>& arg : arguments) {
			std::vector<std::string> parsed = arg->toString(keys, features);
			parsedArguments.insert(parsedArguments.end(), parsed.begin(), parsed.end());
		}
		return parsedArguments;
	}

	static const std::vector<std::shared_ptr<Argument>> DEFAULT_JVM_ARGUMENTS;
	static const std::vector<std::shared_ptr<Argument>> DEFAULT_GAME_ARGUMENTS;

private:
	std::vector<std::shared_ptr<Argument>> game;
	std::vector<std::shared_ptr<Argument>> jvm;
public:

	Arguments() = default;
};

#endif // !ARGUMENTS_H_