#ifndef MODS_H_
#define MODS_H_

#include "../Web/DownloadClasses.h"
#include "../Callbacks/CallbackDict.h"
#include "../Json/Json.h"
#include "../Additionals/Additionals.h"

namespace MinecraftCpp
{
	namespace modpacks
	{
		bool installModPack(Json::JsonValue* json_from_server, const std::string& path, CallbackNull* callback = new CallbackNull());
	}
}

#endif /*MODS_H_*/