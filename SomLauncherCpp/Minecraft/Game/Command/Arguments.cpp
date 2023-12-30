#include "Arguments.h"

Arguments::Arguments(const std::vector<std::shared_ptr<Argument>>& game, const std::vector<std::shared_ptr<Argument>>& jvm)
	: game(game), jvm(jvm)
{
}

const std::vector<std::shared_ptr<Argument>>& Arguments::getGame() const
{
	return this->game;
}

Arguments Arguments::withGame(const std::vector<std::shared_ptr<Argument>>& game) const
{
	return Arguments(game, this->jvm);
}

const std::vector<std::shared_ptr<Argument>>& Arguments::getJvm() const
{
	return this->jvm;
}

Arguments Arguments::withJvm(const std::vector<std::shared_ptr<Argument>>& jvm) const
{
	return Arguments(this->game, jvm);
}

Arguments Arguments::addGameArguments(const std::vector<std::string>& game_arguments) const
{
	std::vector<std::shared_ptr<Argument>> game_args = this->game;
	for (const std::string& arg : game_arguments)
	{
		game_args.push_back(std::make_shared<StringArgument>(arg));
	}
	return Arguments(game_args, this->jvm);
}

Arguments Arguments::addJVMArguments(const std::vector<std::string>& jvm_arguments) const
{
	std::vector<std::shared_ptr<Argument>> jvm_args = jvm;
	for (const std::string& arg : jvm_arguments)
	{
		jvm_args.push_back(std::make_shared<StringArgument>(arg));
	}
	return Arguments(this->game, jvm_args);
}

Arguments Arguments::merge(const Arguments& a, const Arguments& b)
{
	std::vector<std::shared_ptr<Argument>> merged_game = Lang::merge(a.getGame(), b.getGame());
	std::vector<std::shared_ptr<Argument>> merged_jvm = Lang::merge(a.getJvm(), b.getJvm());
	return Arguments(merged_game, merged_jvm);
}

std::vector<std::string> Arguments::parseStringArguments(const std::vector<std::string>& arguments,
	const std::map<std::string, std::string>& keys)
{
	std::vector<std::string> parsed_arguments;
	for (const std::string& argument : arguments)
	{
		StringArgument str_arg(argument);
		std::vector<std::string> parsed = str_arg.toString(keys, std::map<std::string, bool>());
		parsed_arguments.insert(parsed_arguments.end(), parsed.begin(), parsed.end());
	}
	return parsed_arguments;
}

std::vector<std::string> Arguments::parseArguments(const std::vector<std::shared_ptr<Argument>>& arguments,
	const std::map<std::string, std::string>& keys,
	const std::map<std::string, bool>& features)
{
	std::vector<std::string> parsed_arguments;
	for (const std::shared_ptr<Argument>& arg : arguments)
	{
		std::vector<std::string> parsed = arg->toString(keys, features);
		parsed_arguments.insert(parsed_arguments.end(), parsed.begin(), parsed.end());
	}
	return parsed_arguments;
}