#ifndef STARTPROCESS_H_
#define STARTPROCESS_H_

#include <qdebug.h>

#include <string>
#include <vector>
#include <sstream>

#include <../../../Moc/Logger/MocIOStream.h>

#include "../Additionals/Additionals.h"

namespace client
{
	int startProcess(const std::string& args);
	int startProcess(const std::vector<std::string>& args);

	namespace utils
	{
		int doProcess(std::unique_ptr<wchar_t[]>& args);
	}
}

#endif // !STARTPROCESS_H_