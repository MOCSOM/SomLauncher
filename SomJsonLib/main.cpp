#include "pch.h"
#include "SomJson.h"

#include <iostream>

int main()
{
	Json::SomJson json;
	std::cout << json["dad"].get_number() << std::endl;
	std::cout << json.to_string() << std::endl;
}