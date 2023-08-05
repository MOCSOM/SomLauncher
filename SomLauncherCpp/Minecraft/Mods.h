#ifndef MODS_H_     // equivalently, #if !defined HEADER_H_
#define MODS_H_

#include "../Web/DownloadClasses.h"
#include "../Callbacks/CallbackDict.h"
#include "../Json/Json.h"
#include "../Additionals/Additionals.h"

namespace MinecraftCpp
{
	namespace modpacks
	{
		bool install_mod_pack(wchar_t* versionid, wchar_t* path, CallbackNull* callback = new CallbackNull());
	}
}

#endif /*MODS_H_*/