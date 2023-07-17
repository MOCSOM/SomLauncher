#include "Minecraftus.h"




wchar_t*& MCCL::Option::MinecraftOptions::get(wchar_t* param, wchar_t* writ)
{
    //16 полей
    /*wchar_t* username;
    wchar_t* uuid;
    wchar_t* token;
    wchar_t* executablePath;
    wchar_t* jvmArguments;
    wchar_t* launcherName;
    wchar_t* launcherVersion;
    wchar_t* gameDirectory;
    bool	 demo;
    bool	 customResolution;
    wchar_t* resolutionWidth;
    wchar_t* resolutionHeight;
    wchar_t* server;
    wchar_t* port;
    wchar_t* nativesDirectory;
    bool	 enableLoggingConfig;*/

    if (System::String(param) == System::String(L"username"))
    {
        if (writ == NULL)
        {
            return this->username;
        }
        else if (this->username == NULL)
        {
            this->username = writ;
            return this->username;
        }
        else
        {
            return this->username;
        }
    }
    else if (System::String(param) == System::String(L"uuid"))
    {
        if (writ == NULL)
        {
            return this->uuid;
        }
        else if (this->uuid == NULL)
        {
            this->uuid = writ;
            return this->uuid;
        }
        else
        {
            return this->uuid;
        }
    }
    else if (System::String(param) == System::String(L"token"))
    {
        if (writ == NULL)
        {
            return this->token;
        }
        else if (this->token == NULL)
        {
            this->token = writ;
            return this->token;
        }
        else
        {
            return this->token;
        }
    }
    else if (System::String(param) == System::String(L"executablePath"))
    {
        if (writ == NULL)
        {
            return this->executablePath;
        }
        else if (this->executablePath == NULL)
        {
            this->executablePath = writ;
            return this->executablePath;
        }
        else
        {
            return this->executablePath;
        }
    }
    else if (System::String(param) == System::String(L"jvmArguments"))
    {
        if (writ == NULL)
        {
            return this->jvmArguments;
        }
        else if (this->jvmArguments == NULL)
        {
            this->jvmArguments = writ;
            return this->jvmArguments;
        }
        else
        {
            return this->jvmArguments;
        }
    }
    else if (System::String(param) == System::String(L"launcherName"))
    {
        if (writ == NULL)
        {
            return this->launcherName;
        }
        else if (this->uuid == NULL)
        {
            this->launcherName = writ;
            return this->launcherName;
        }
        else
        {
            return this->launcherName;
        }
    }
    else if (System::String(param) == System::String(L"launcherVersion"))
    {
        if (writ == NULL)
        {
            return this->launcherVersion;
        }
        else if (this->launcherVersion == NULL)
        {
            this->launcherVersion = writ;
            return this->launcherVersion;
        }
        else
        {
            return this->launcherVersion;
        }
    }
    else if (System::String(param) == System::String(L"gameDirectory"))
    {
        if (writ == NULL)
        {
            return this->gameDirectory;
        }
        else if (this->gameDirectory == NULL)
        {
            this->gameDirectory = writ;
            return this->gameDirectory;
        }
        else
        {
            return this->gameDirectory;
        }
    }
    else if (System::String(param) == System::String(L"resolutionWidth"))
    {
        if (writ == NULL)
        {
            return this->resolutionWidth;
        }
        else if (this->resolutionWidth == NULL)
        {
            this->resolutionWidth = writ;
            return this->resolutionWidth;
        }
        else
        {
            return this->resolutionWidth;
        }
    }
    else if (System::String(param) == System::String(L"resolutionHeight"))
    {
        if (writ == NULL)
        {
            return this->resolutionHeight;
        }
        else if (this->resolutionHeight == NULL)
        {
            this->resolutionHeight = writ;
            return this->resolutionHeight;
        }
        else
        {
            return this->resolutionHeight;
        }
    }
    else if (System::String(param) == System::String(L"server"))
    {
        if (writ == NULL)
        {
            return this->server;
        }
        else if (this->server == NULL)
        {
            this->server = writ;
            return this->server;
        }
        else
        {
            return this->server;
        }
    }
    else if (System::String(param) == System::String(L"port"))
    {
        if (writ == NULL)
        {
            return this->port;
        }
        else if (this->port == NULL)
        {
            this->port = writ;
            return this->port;
        }
        else
        {
            return this->port;
        }
    }
    else if (System::String(param) == System::String(L"nativesDirectory"))
    {
        if (writ == NULL)
        {
            return this->nativesDirectory;
        }
        else if (this->nativesDirectory == NULL)
        {
            this->nativesDirectory = writ;
            return this->nativesDirectory;
        }
        else
        {
            return this->nativesDirectory;
        }
    }
    else
    {
        return this->NULLES;
    }
}

bool MCCL::Option::MinecraftOptions::get(wchar_t* param, bool writ, int a)
{
    if (System::String(param) == System::String(L"demo"))
    {
        if (writ == NULL)
        {
            return this->demo;
        }
        else if (this->demo == NULL)
        {
            this->demo = writ;
            return this->demo;
        }
        else
        {
            return this->demo;
        }
    }
    else if (System::String(param) == System::String(L"customResolution"))
    {
        if (writ == NULL)
        {
            return this->customResolution;
        }
        else if (this->customResolution == NULL)
        {
            this->customResolution = writ;
            return this->customResolution;
        }
        else
        {
            return this->customResolution;
        }
    }
    else if (System::String(param) == System::String(L"enableLoggingConfig"))
    {
        if (writ == NULL)
        {
            return this->enableLoggingConfig;
        }
        else if (this->enableLoggingConfig == NULL)
        {
            this->enableLoggingConfig = writ;
            return this->enableLoggingConfig;
        }
        else
        {
            return this->enableLoggingConfig;
        }
    }
    else
    {
        return nullptr;
    }
}

bool MCCL::Option::MinecraftOptions::is_exist(wchar_t* param)
{
    if (param == L"username")
    {
        return true;
    }
    else if (param == L"uuid")
    {
        return true;
    }
    else if (param == L"token")
    {
        return true;
    }
    else if (param == L"executablePath")
    {
        return true;
    }
    else if (param == L"jvmArguments")
    {
        return true;
    }
    else if (param == L"launcherName")
    {
        return true;
    }
    else if (param == L"launcherVersion")
    {
        return true;
    }
    else if (param == L"gameDirectory")
    {
        return true;
    }
    else if (param == L"resolutionWidth")
    {
        return true;
    }
    else if (param == L"resolutionHeight")
    {
        return true;
    }
    else if (param == L"server")
    {
        return true;
    }
    else if (param == L"port")
    {
        return true;
    }
    else if (param == L"nativesDirectory")
    {
        return true;
    }
    if (param == L"demo")
    {
        return true;
    }
    else if (param == L"customResolution")
    {
        return true;
    }
    else if (param == L"enableLoggingConfig")
    {
        return true;
    }
    else
    {
        return false;
    }
}


bool MCCL::install_minecraft_version(wchar_t* versionid, wchar_t* minecraft_directory, CallbackNull callback)
{
    /*
    Install a Minecraft Version. Fore more Information take a look at the documentation"
    */
    Json::JsonParcer json_manifest;

    wchar_t* full_dir = JoinW({ minecraft_directory , L"versions" , versionid, StrDogW(versionid, L".json") });

    wchar_t* download_dir = JoinW({ minecraft_directory, L"downloads" });

    if (!System::IO::Directory::Exists(System::String(download_dir).ToString())) {
        int out_mkdir = _wmkdir(download_dir);
        System::Console::Write("java dir is maked with status: ");
        System::Console::WriteLine(out_mkdir);
    }

    if (System::IO::File::Exists(System::String(full_dir).ToString()))
    {
        if (System::IO::File::GetAttributes(System::String(full_dir).ToString()) != System::IO::FileAttributes::Directory)
        {
            do_version_install(versionid, minecraft_directory, callback);
            return true;
        }
    }
    
    wchar_t* version_manifest_file = DownloadFile(L"https://launchermeta.mojang.com/mc/game/version_manifest.json",
        download_dir, callback);

    auto version_list = json_manifest.ParseFile(System::String(version_manifest_file).ToString());

    for each (auto var in version_list->get_value("versions")->get_value_list())
    {
        if (var->get_value("id")->to_string() == System::String(versionid).ToString())
        {
            do_version_install(versionid, minecraft_directory, callback, var->get_value("url")->to_stringW());
            return true;
        }
    }
	return false;
}

bool MCCL::do_version_install(wchar_t* versionid, wchar_t* path, CallbackNull callback, wchar_t* url)
{
    /*
    Install the given version
    */

    Json::JsonParcer json_verid;
    wchar_t* path_ver_json = JoinW({ path, L"versions", versionid, StrDogW(versionid, L".json") });

    // Download and read versions.json
    if (url != NULL) 
    {
        DownloadFile(url, path_ver_json, callback);
    }
    auto versiondata = json_verid.ParseFile(System::String(path_ver_json).ToString());

    // For Forge
    if (versiondata->is_exist("inheritsFrom"))
    {
        install_minecraft_version(versiondata->get_value("inheritsFrom")->to_stringW(), path);
        versiondata = inherit_json(versiondata, path);
    }
    install_libraries(versiondata, path, callback);
    install_assets(versiondata, path, callback);

    //Download logging config
    wchar_t* logger_file = NULL;
    if (versiondata->is_exist("logging"))
    {
        if (versiondata->get_value("logging")->to_int() != 0)
        {
            logger_file = JoinW({ path, L"assets", L"log_configs", versiondata->get_value("logging")->get_value("client")->get_value("file")->get_value("id")->to_stringW() });
            DownloadFile(versiondata->get_value("logging")->get_value("client")->get_value("file")->get_value("url")->to_stringW(), logger_file, callback); //to with sha
        }
    }

    //Download minecraft.jar
    if (versiondata->is_exist("downloads"))
    {
        DownloadFile(versiondata->get_value("downloads")->get_value("client")->get_value("url")->to_stringW(), JoinW({ path, L"versions", versiondata->get_value("id")->to_stringW(), StrDogW(versiondata->get_value("id")->to_stringW(), L".jar")}), callback);
    }

    //Need to copy jar for old forge versions
    if (!(System::IO::File::GetAttributes(System::String(JoinW({ path, L"versions", versiondata->get_value("id")->to_stringW(), StrDogW(versiondata->get_value("id")->to_stringW(), L".jar") })).ToString()) != System::IO::FileAttributes::Directory) && versiondata->is_exist("inheritsFrom"))
    {
        System::IO::File::Copy(System::String(JoinW({ path, L"versions", versiondata->get_value("id")->to_stringW(), StrDogW(versiondata->get_value("id")->to_stringW(), L".jar") })).ToString(), System::String(JoinW({path, L"versions", versiondata->get_value("inheritsFrom")->to_stringW(), StrDogW(versiondata->get_value("inheritsFrom")->to_stringW(), L".jar")})).ToString());
    }

    //Install java runtime if needed
    if (versiondata->is_exist("javaVersion"))
    {
        install_jvm_runtime(versiondata->get_value("javaVersion")->get_value("component")->to_stringW(), path, callback);
    }

    return true;
}

Json::JsonValue^ MCCL::inherit_json(Json::JsonValue^ original_data, wchar_t* path)
{
    /*
    Implement the inheritsFrom function
    See https://github.com/tomsik68/mclauncher-api/wiki/Version-Inheritance-&-Forge
    */
    auto inherit_version = original_data->get_value("inheritsFrom");

    wchar_t* path_inh_json = JoinW({ path, L"versions", inherit_version->to_stringW(), StrDogW(inherit_version->to_stringW(), L".json")});
    Json::JsonParcer json_inherit;
    auto new_data = json_inherit.ParseFile(System::String(path_inh_json).ToString());
    for each(auto var in original_data->get_value()) 
    {
        if (var->second->get_type() == Json::JsonTypes::ARRAY && new_data->get_value(var->first)->get_type() == Json::JsonTypes::ARRAY)
        {
            new_data->get_value(var->first)->operator=(var->second + new_data->get_value(var->first));
        }
        else if (var->second->get_type() == Json::JsonTypes::OBJECT && new_data->get_value(var->first)->get_type() == Json::JsonTypes::OBJECT)
        {
            for each (auto variable in var->second->get_value())
            {
                if (variable->second->get_type() == Json::JsonTypes::ARRAY)
                {
                    new_data->get_value(var->first)->get_value(variable->first)->operator=(new_data->get_value(var->first)->get_value(variable->first) + variable->second);
                }
            }
        }
        else
        {
            if (new_data->is_exist(var->first))
            {
                new_data->get_value(var->first)->operator=(var->second);
            }
            else
            {
                new_data->add_value(var->first, var->second);
            }
        }
    }
    return new_data;
}

wchar_t* MCCL::get_minecraft_command__(wchar_t* version, wchar_t* minecraft_directory, MCCL::Option::MinecraftOptions options)
{
    /*
    Returns a command for launching Minecraft.For more information take a look at the documentation.
    */
    if (!System::IO::File::Exists(System::String(JoinW({ minecraft_directory, L"versions", version, StrDogW(version, L".json") })).ToString()) || System::IO::File::GetAttributes(System::String(JoinW({minecraft_directory, L"versions", version})).ToString()) != System::IO::FileAttributes::Directory)
    {
        System::Console::WriteLine("Version Not Found");
        System::Console::WriteLine(System::String(version).ToString());
        return nullptr;
    }

    Json::JsonParcer json_parcer;
    auto data = json_parcer.ParseFile(System::String(JoinW({ minecraft_directory, L"versions", version, StrDogW(version, L".json") })).ToString());

    if (data->is_exist("inheritsFrom"))
    {
        data = MCCL::inherit_json(data, minecraft_directory);
    }
    options.nativesDirectory = options.get(L"nativesDirectory", JoinW({ minecraft_directory, L"versions", data["id"]->to_stringW(), L"natives" }));
    //options.nativesDirectory = JoinW({ minecraft_directory, L"versions", data["id"]->to_stringW(), L"natives" });
    options.classpath = MCCL::get_libraries(data, minecraft_directory);

    wchar_t* command = NULL;

    // Add Java executable
    if (options.executablePath != NULL)
    {
        command = StrDogW(command, options.executablePath);
        command = StrDogW(command, L" ");
    }
    else if (data->is_exist(L"javaVersion"))
    {
        wchar_t* java_path = MCCL::get_executable_path(data["javaVersion"]["component"]->to_stringW(), minecraft_directory);
        if (java_path == nullptr)
        {
            command = StrDogW(command, L"java");
            command = StrDogW(command, L" ");
        }
        else
        {
            command = StrDogW(command, java_path);
            command = StrDogW(command, L" ");
        }
    }
    else
    {
        command = StrDogW(command, L"java");
        command = StrDogW(command, L" ");
    }
    if (options.jvmArguments != NULL)
    {
        command = StrDogW(command, options.jvmArguments);
        command = StrDogW(command, L" ");
    }

    // Newer Versions have jvmArguments in version.json
    if (data->get_value("arguments")->get_type() == Json::JsonTypes::OBJECT)
    {
        if (data->get_value("arguments")->is_exist("jvm"))
        {
            command = StrDogW(command, MCCL::get_arguments(data["arguments"]["jvm"], data, minecraft_directory, options));
            command = StrDogW(command, L" ");
        }
        else
        {
            command = StrDogW(command, StrDogW(L"-Djava.library.path=", options.nativesDirectory));
            command = StrDogW(command, L" ");
            command = StrDogW(command, L"-cp");
            command = StrDogW(command, L" ");
            command = StrDogW(command, options.classpath);
            command = StrDogW(command, L" ");
        }
    }
    else
    {
        command = StrDogW(command, StrDogW(L"-Djava.library.path=", options.nativesDirectory));
        command = StrDogW(command, L" ");
        command = StrDogW(command, L"-cp");
        command = StrDogW(command, L" ");
        command = StrDogW(command, options.classpath);
        command = StrDogW(command, L" ");
    }

    //The argument for the logger file (Неработает т к false)
    // TODO теперь работает передлать get
    /* 
    if options.get("enableLoggingConfig", False):
        if "logging" in data:
            if len(data["logging"]) != 0:
                logger_file = os.path.join(path, "assets", "log_configs", data["logging"]["client"]["file"]["id"])
                command.append(data["logging"]["client"]["argument"].replace("${path}", logger_file))
    */

    command = StrDogW(command, data["mainClass"]->to_stringW());
    command = StrDogW(command, L" ");
    if (data->is_exist("minecraftArguments"))
    {
        // For older versions
        command = StrDogW(command, MCCL::get_arguments_string(data, minecraft_directory, options));
        command = StrDogW(command, L" ");
    }
    else
    {
        command = StrDogW(command, MCCL::get_arguments(data->get_value("arguments")->get_value("game"), data, minecraft_directory, options));
        command = StrDogW(command, L" ");
    }

    if (options.server != NULL)
    {
        command = StrDogW(command, L"--server");
        command = StrDogW(command, L" ");
        command = StrDogW(command, options.server);
        command = StrDogW(command, L" ");
        if (options.port != NULL)
        {
            command = StrDogW(command, L"--port");
            command = StrDogW(command, L" ");
            command = StrDogW(command, options.port);
            command = StrDogW(command, L" ");
        }
    }
    return command;
}

wchar_t* MCCL::get_libraries(Json::JsonValue^ data, wchar_t* path)
{
    /*
    Returns the argument with all libs that come after -cp
    */
    wchar_t* classpath_seperator = MCCL::get_classpath_separator();
    wchar_t* libstr = L"";
    wchar_t* native = L"";
    MCCL::Option::MinecraftOptions empty;
    int debug = 0;
    if (data["libraries"]->get_count() == 1)
    {
        for each (auto var in data->get_value("libraries")[0]->get_value_list())
        {
            if (!(MCCL::parse_rule_list(var, L"rules", empty)))
            {
                continue;
            }
            libstr = StrDogW(libstr, StrDogW(MCCL::get_library_path(var->get_value("name")->to_stringW(), path), classpath_seperator));
            native = MCCL::get_natives(var);
            if (System::String(native) != System::String(L""))
            {
                if (var->is_exist("downloads"))
                {
                    libstr = StrDogW(libstr, StrDogW(JoinW({ path, L"libraries", var->get_value("downloads")->get_value("classifiers")->get_value(System::String(native).ToString())->get_value("path")->to_stringW() }), classpath_seperator));
                }
                else
                {
                    libstr = StrDogW(libstr, StrDogW(MCCL::get_library_path(StrDogW(var->get_value("name")->to_stringW(), StrDogW(L"-", native)), path), classpath_seperator));
                }
            }
        }

        if (data->is_exist("jar"))
        {
            libstr = StrDogW(libstr, JoinW({ path, L"versions", data->get_value("jar")->to_stringW(), StrDogW(data->get_value("jar")->to_stringW(), L".jar") }));
        }
        else
        {
            libstr = StrDogW(libstr, JoinW({ path, L"versions", data->get_value("id")->to_stringW(), StrDogW(data->get_value("id")->to_stringW(), L".jar") }));
        }
    }
    else
    {
        for each (auto var in data->get_value("libraries")->get_value_list())
        {
            if (!(MCCL::parse_rule_list(var, L"rules", empty)))
            {
                continue;
            }
            libstr = StrDogW(libstr, StrDogW(MCCL::get_library_path(var->get_value("name")->to_stringW(), path), classpath_seperator));
            native = MCCL::get_natives(var);
            if (System::String(native) != System::String(L""))
            {
                if (var->is_exist("downloads"))
                {
                    libstr = StrDogW(libstr, StrDogW(JoinW({ path, L"libraries", var->get_value("downloads")->get_value("classifiers")->get_value(System::String(native).ToString())->get_value("path")->to_stringW() }), classpath_seperator));
                }
                else
                {
                    libstr = StrDogW(libstr, StrDogW(MCCL::get_library_path(StrDogW(var->get_value("name")->to_stringW(), StrDogW(L"-", native)), path), classpath_seperator));
                }
            }
        }

        if (data->is_exist("jar"))
        {
            libstr = StrDogW(libstr, JoinW({ path, L"versions", data->get_value("jar")->to_stringW(), StrDogW(data->get_value("jar")->to_stringW(), L".jar") }));
        }
        else
        {
            libstr = StrDogW(libstr, JoinW({ path, L"versions", data->get_value("id")->to_stringW(), StrDogW(data->get_value("id")->to_stringW(), L".jar") }));
        }
    }
    

    return libstr;
}

bool MCCL::start_minecraft(wchar_t* java_path, wchar_t* args)
{    
    wchar_t* path;

    path = StrDogW(java_path, L" ");
    path = StrDogW(path, args);

    //STARTUPINFO si;
    //PROCESS_INFORMATION pi;
    //bool out;

    //ZeroMemory(&si, sizeof(si));
    //si.cb = sizeof(si);
    //ZeroMemory(&pi, sizeof(pi));

    //out = CreateProcessW(
    //    java_path,           // Module name
    //    args,           // Command line
    //    NULL,           // Process handle not inheritable
    //    NULL,           // Thread handle not inheritable
    //    FALSE,          // Set handle inheritance to FALSE
    //    0,              // Creation flags
    //    NULL,           // Use parent's environment block
    //    NULL,           // Use parent's starting directory 
    //    &si,            // Pointer to STARTUPINFO structure
    //    &pi             // Pointer to PROCESS_INFORMATION structure
    //);

    //// Wait until child process exits.
    //WaitForSingleObject(pi.hProcess, INFINITE);

    //// Close process and thread handles. 
    //CloseHandle(pi.hProcess);
    //CloseHandle(pi.hThread);

    return _wsystem(path);
}

wchar_t* MCCL::get_classpath_separator()
{
    /*
    Returns the classpath seperator for the current os
    */
    if (System::String(OS) == System::String(L"Windows"))
    {
        return L";";
    }
    else
    {
        return L":";
    }
}

bool MCCL::parse_rule_list(Json::JsonValue^ data, wchar_t* rule_string, MCCL::Option::MinecraftOptions options)
{
    /*
    Parse a list of rules
    */
    if (!data->is_exist(System::String(rule_string).ToString()))
    {
        return true;
    }
    for each (auto var in data->get_value(System::String(rule_string).ToString())->get_value_list())
    {
        if (!MCCL::parse_single_rule(var, options))
        {
            return false;
        }
    }
    return true;
}

bool MCCL::parse_single_rule(Json::JsonValue^ rule, MCCL::Option::MinecraftOptions options)
{
    /*
    Parse a single rule from the versions.json
    */
    bool returnvalue = false;
    if (rule["action"]->to_string() == System::String("allow").ToString())
    {
        returnvalue = false;
    }
    else if (rule["action"]->to_string() == System::String("disallow").ToString())
    {
        returnvalue = true;
    }
    if (rule->is_exist("os"))
    {
        for each (auto var in rule["os"]->get_value())
        {
            if (var->first == "name")
            {
                if (var->second->to_string() == System::String("windows").ToString() && System::String(OS) != System::String(L"Windows"))
                {
                    return returnvalue;
                }
                else if (var->second->to_string() == System::String("osx").ToString() && System::String(OS) != System::String(L"Darwin"))
                {
                    return returnvalue;
                }
                else if (var->second->to_string() == System::String("linux").ToString() && System::String(OS) != System::String(L"Linux"))
                {
                    return returnvalue;
                }
            }
            else if (var->first == System::String("arch").ToString())
            {
                if (var->second->to_string() == System::String("x86").ToString() && System::String(ARCH) != System::String(L"x86"))
                {
                    return returnvalue;
                }
            }
            else if (var->first == System::String("version").ToString())
            {
                if (var->second->to_string() != System::String(OS).ToString())
                {
                    return returnvalue;
                }
            }
        }
    }
    if (rule->is_exist("features"))
    {
        for each (auto var in rule["features"]->get_value())
        {
            if (var->first == System::String("has_custom_resolution").ToString() && !options.get(L"customResolution", false))
            {
                return returnvalue;
            }
            else if (var->first == System::String("is_demo_user").ToString() && !options.get(L"demo", false))
            {
                return returnvalue;
            }
        }
    }
    return !returnvalue;
}

wchar_t* MCCL::get_library_path(wchar_t* name, wchar_t* path)
{
    /*
    Returns the path from a libname
    */

    wchar_t* libpath = JoinW({ path, L"libraries" });

    array<System::String^>^ parts = System::String(name).ToString()->Split(':');
    System::String^ base_path = parts[0];
    System::String^ libname = parts[1];
    System::String^ version = parts[2];
    System::String^ fileend;

    for each (auto var in base_path->Split('.'))
    {
        pin_ptr<const wchar_t> wch = PtrToStringChars(var);
        libpath = JoinW({ libpath, const_cast<wchar_t*>(wch) });
    }
    if (version->Contains("@"))
    {
        array<System::String^>^ splt = version->Split('@', 2);
        version = splt[0];
        fileend = splt[1];
    }
    else
    {
        fileend = "jar";
    }
    // construct a filename with the remaining parts

    pin_ptr<const wchar_t> wch_libname = PtrToStringChars(libname);
    pin_ptr<const wchar_t> wch_version = PtrToStringChars(version);
    pin_ptr<const wchar_t> wch_fileend = PtrToStringChars(fileend);

    wchar_t* filename = NULL;
    
    //parts->CopyTo(parts_2, 3);
    int count = 0;
    for each (auto var in parts)
    {
        ++count;
    }
    array<System::String^>^ parts_2 = gcnew array<System::String^>(count - 2);
    for (int i = 0; i < count - 2; i++)
    {
        parts_2[i] = parts[i + 2];
    }
    //filename = StrDogW({ const_cast<wchar_t*>(wch_libname), L"-", const_cast<wchar_t*>(wch_version) });
    for each (auto var in parts_2)
    {
        pin_ptr<const wchar_t> wch_var = PtrToStringChars(var);
        filename = StrDogW(const_cast<wchar_t*>(wch_libname), StrDogW(L"-", const_cast<wchar_t*>(wch_var)));
    }
    filename = StrDogW(filename, StrDogW(L".", const_cast<wchar_t*>(wch_fileend)));

    libpath = JoinW({ libpath, const_cast<wchar_t*>(wch_libname), const_cast<wchar_t*>(wch_version), filename });
    return libpath;
}

wchar_t* MCCL::get_natives(Json::JsonValue^ data)
{
    /*
    Returns the native part from the json data
    */
    wchar_t* arch_type;
    if (System::String(ARCH) == System::String(L"x86"))
    {
        arch_type = L"32";
    }
    else
    {
        arch_type = L"64";
    }

    if (data->is_exist("natives"))
    {
        if (System::String(OS) == System::String(L"Windows"))
        {
            if (data["natives"]->is_exist("windows"))
            {
                pin_ptr<const wchar_t> wch_data = PtrToStringChars(data["natives"]["windows"]->to_string()->Replace(System::String(L"${arch}").ToString(), System::String(arch_type).ToString()));
                return const_cast<wchar_t*>(wch_data);
            }
            else
            {
                return L"";
            }
        }
        else if (System::String(OS) == System::String(L"Darwin"))
        {
            if (data["natives"]->is_exist("osx"))
            {
                pin_ptr<const wchar_t> wch_data = PtrToStringChars(data["natives"]["osx"]->to_string()->Replace(System::String(L"${arch}").ToString(), System::String(arch_type).ToString()));
                return const_cast<wchar_t*>(wch_data);
            }
            else
            {
                return L"";
            }
        }
        else
        {
            if (data["natives"]->is_exist("linux"))
            {
                pin_ptr<const wchar_t> wch_data = PtrToStringChars(data["natives"]["linux"]->to_string()->Replace(System::String(L"${arch}").ToString(), System::String(arch_type).ToString()));
                return const_cast<wchar_t*>(wch_data);
            }
            else
            {
                return L"";
            }
        }
    }
    else
    {
        return L"";
    }   
}

wchar_t* MCCL::_get_jvm_platform_string()
{
    /*
    Get the name that is used the identify the platform
    */
    if (System::String(OS) == System::String(L"Windows"))
    {
        if (System::String(ARCH) == System::String(L"x86"))
        {
            return L"windows-x86";
        }
        else
        {
            return L"windows-x64";
        }
    }
    else if (System::String(OS) == System::String(L"Linux"))
    {
        if (System::String(ARCH) == System::String(L"x86"))
        {
            return L"linux-i386";
        }
        else
        {
            return L"linux";
        }
    }
    else if (System::String(OS) == System::String(L"Darwin"))
    {
        return L"mac-os";
    }
    return L"";
}

wchar_t* MCCL::replace_arguments(System::String^ argstr, Json::JsonValue^ versionData, wchar_t* path, MCCL::Option::MinecraftOptions options)
{
    /*
    Replace all 20 placeholder in arguments with the needed value
    */
    argstr = argstr->Replace("${natives_directory}", System::String(options.nativesDirectory).ToString());
    argstr = argstr->Replace("${launcher_name}", System::String(options.get(L"launcherName", L"null")).ToString());
    argstr = argstr->Replace("${launcher_version}", System::String(options.get(L"launcherVersion", L"null")).ToString());
    argstr = argstr->Replace("${classpath}", System::String(options.classpath).ToString());
    argstr = argstr->Replace("${auth_player_name}", System::String(options.get(L"username", L"{username}")).ToString());
    argstr = argstr->Replace("${version_name}", versionData["id"]->to_string());
    argstr = argstr->Replace("${game_directory}", System::String(options.get(L"gameDirectory", path)).ToString());
    argstr = argstr->Replace("${assets_root}", System::String(JoinW({ path, L"assets" })).ToString());
    argstr = argstr->Replace("${assets_index_name}", versionData["assets"] != nullptr ? versionData["assets"]->to_string() : versionData["id"]->to_string());
    argstr = argstr->Replace("${auth_uuid}", System::String(options.get(L"uuid", L"{uuid}")).ToString());
    argstr = argstr->Replace("${auth_access_token}", System::String(options.get(L"token", L"{token}")).ToString());
    argstr = argstr->Replace("${user_type}", "mojang");
    argstr = argstr->Replace("${version_type}", versionData["type"]->to_string());
    argstr = argstr->Replace("${user_properties}", "{}");
    argstr = argstr->Replace("${resolution_width}", System::String(options.get(L"resolutionWidth", L"854")).ToString());
    argstr = argstr->Replace("${resolution_height}", System::String(options.get(L"resolutionHeight", L"480")).ToString());
    argstr = argstr->Replace("${game_assets}", System::String(JoinW({ path, L"assets", L"virtual", L"legacy" })).ToString());
    argstr = argstr->Replace("${auth_session}", System::String(options.get(L"token", L"{token}")).ToString());
    argstr = argstr->Replace("${library_directory}", System::String(JoinW({ path, L"libraries" })).ToString());
    argstr = argstr->Replace("${classpath_separator}", System::String(MCCL::get_classpath_separator()).ToString());

    pin_ptr<const wchar_t> wch_argstr = PtrToStringChars(argstr);
    return const_cast<wchar_t*>(wch_argstr);
}

wchar_t* MCCL::get_executable_path(wchar_t* jvm_version, wchar_t* minecraft_directory)
{
    /*
    Returns the path to the executable. Returns None if none is found.
    */
    wchar_t* java_path = JoinW({ minecraft_directory, L"runtime", jvm_version, _get_jvm_platform_string(), jvm_version, L"bin", L"java" });
    if (System::IO::File::Exists(System::String(java_path).ToString()))
    {
        if (System::IO::File::GetAttributes(System::String(java_path).ToString()) != System::IO::FileAttributes::Directory)
        {
            return java_path;
        }
        else if (System::IO::File::GetAttributes(System::String(java_path).ToString() + ".exe") != System::IO::FileAttributes::Directory)
        {
            return StrDogW(java_path, L".exe");
        }
    }
    

    System::String^ java_path_string = System::String(java_path).ToString()->Replace(System::String(JoinW({ L"bin", L"java" })).ToString(), System::String(JoinW({ L"jre.bundle", L"Contents", L"Home", L"bin", L"java" })).ToString());
    if (System::IO::File::Exists(java_path_string))
    {
        if (System::IO::File::GetAttributes(java_path_string) != System::IO::FileAttributes::Directory)
        {
            pin_ptr<const wchar_t> wch_java_path = PtrToStringChars(java_path_string);
                return const_cast<wchar_t*>(wch_java_path);
        }
        else
        {
            return nullptr;
        }
    }
    return nullptr;
}

bool MCCL::install_libraries(Json::JsonValue^ data, wchar_t* path, CallbackNull callback)
{
    /*
    Install all libraries
    */
    // TODO вызов callback для управление вывода
    
    for each (auto var in data->get_value("libraries")->get_value_list())
    {
        MCCL::Option::MinecraftOptions empty;
        // Check, if the rules allow this lib for the current system
        if (!MCCL::parse_rule_list(var, L"rules", empty))
        {
            continue;
        }
        // Turn the name into a path
        wchar_t* currentPath = JoinW({ path, L"libraries" });
        wchar_t* downloadUrl = NULL;
        if (var->is_exist("url"))
        {
            if (var->get_value("url")->to_string()->EndsWith("/"))
            {
                pin_ptr<const wchar_t> wch_var = PtrToStringChars(var->get_value("url")->to_string()->TrimEnd('/'));
                downloadUrl = const_cast<wchar_t*>(wch_var);
            }
            else
            {
                downloadUrl = var->get_value("url")->to_stringW();
            }
        }
        else
        {
            downloadUrl = L"https://libraries.minecraft.net";
        }

        System::String^ libPath = var->get_value("name")->to_string()->Split(':')[0];
        System::String^ name = var->get_value("name")->to_string()->Split(':')[1];
        System::String^ version = var->get_value("name")->to_string()->Split(':')[2];
        for each (auto var2 in libPath->Split('.'))
        {
            pin_ptr<const wchar_t> wch_var2 = PtrToStringChars(var2);
            currentPath = JoinW({ currentPath, const_cast<wchar_t*>(wch_var2) });
            downloadUrl = StrDogW({ downloadUrl, L"/", const_cast<wchar_t*>(wch_var2) });
        }

        System::String^ fileend;
        if (version->Split('@')[0] != version)
        {
            array<System::String^>^ splt = version->Split('@');
            version = splt[0];
            fileend = splt[1];
        }
        else
        {
            fileend = "jar";
        }

        System::String^ jarFilename = name + "-" + version + "." + fileend;
        pin_ptr<const wchar_t> wch_name = PtrToStringChars(name);
        pin_ptr<const wchar_t> wch_version = PtrToStringChars(version);
        downloadUrl = StrDogW({ downloadUrl, L"/", const_cast<wchar_t*>(wch_name), L"/", const_cast<wchar_t*>(wch_version) });
        currentPath = JoinW({ currentPath, const_cast<wchar_t*>(wch_name), const_cast<wchar_t*>(wch_version) });
        wchar_t* native = get_natives(var);

        //Check if there is a native file
        wchar_t* jarFilenameNative = NULL;
        if (System::String(native) != System::String(L""))
        {
            jarFilenameNative = StrDogW({ const_cast<wchar_t*>(wch_name), L"-", const_cast<wchar_t*>(wch_version), L"-", native, L".jar" });
        }
        jarFilename = name + "-" + version + "." + fileend;
        pin_ptr<const wchar_t> wch_jarFilename = PtrToStringChars(jarFilename);
        downloadUrl = StrDogW({ downloadUrl, L"/", const_cast<wchar_t*>(wch_jarFilename) });

        //Try to download the lib
        DownloadFile(downloadUrl, JoinW({ currentPath, const_cast<wchar_t*>(wch_jarFilename) }), callback);

        if (!var->is_exist("downloads"))
        {
            if (var->is_exist("extract"))
            {
                extract_natives_file(JoinW({ currentPath, jarFilenameNative }), JoinW({ path, L"versions", data->get_value("id")->to_stringW(), L"natives"}), var->get_value("extract"));
            }
            continue;
        }
        if (var->get_value("downloads")->is_exist("artifact"))
        {
            DownloadFile(var->get_value("downloads")->get_value("artifact")->get_value("url")->to_stringW(), JoinW({ path, L"libraries", var->get_value("downloads")->get_value("artifact")->get_value("path")->to_stringW() }), callback);
        }
        if (System::String(native) != System::String(L""))
        {
            DownloadFile(var->get_value("downloads")->get_value("classifiers")->get_value(System::String(native).ToString())->get_value("url")->to_stringW(), JoinW({ currentPath, jarFilenameNative }), callback);
            if (var->get_value("extract"))
            {
                extract_natives_file(JoinW({ currentPath, jarFilenameNative }), JoinW({ path, L"versions", data->get_value("id")->to_stringW(), L"natives" }), var->get_value("extract"));
            }
        }
    }
    return true;
}

bool MCCL::extract_natives_file(wchar_t* filename, wchar_t* extract_path, Json::JsonValue^ extract_data)
{
    /*
    Unpack natives
    */
    int ret = _wmkdir(extract_path);
    System::IO::Compression::ZipArchive^ zArchive;

    if (System::IO::File::Exists(System::String(filename).ToString()))
    {
        zArchive = System::IO::Compression::ZipFile::OpenRead(System::String(filename).ToString());
    }
    else
    {
        return false;
    }
    for each (auto var in zArchive->Entries)
    {
        for each (auto var2 in extract_data->get_value("exclude")->get_value_list())
        {
            if (var->Name->StartsWith(var2->to_string()))
            {
                continue;
            }
        }
        int count = 0;
        for each (auto var in var->FullName->Split('.'))
        {
            ++count;
        }
        if (count == 1)
        {
            continue;
        }
        if (!System::IO::File::Exists(System::String(extract_path).ToString() + "\\" + var->FullName))
        {
            
            System::IO::Compression::ZipFileExtensions::ExtractToFile(var, System::String(extract_path).ToString() + "\\" + var->FullName);
        }
    }
    return true;
}

bool MCCL::install_assets(Json::JsonValue^ data, wchar_t* path, CallbackNull callback)
{
    /*
    Install all assets
    */
    // Old versions dosen't have this
    if (data->is_exist("assetIndex"))
    {
        return false;
    }
    //TODO callback.get("setStatus", empty)("Download Assets")

    // Download all assets
    Json::JsonParcer jsonParcer;
    DownloadFile(data->get_value("assetIndex")->get_value("url")->to_stringW(), JoinW({ path, L"assets", L"indexes", StrDogW(data->get_value("assets")->to_stringW(), L".json") }), callback);
    auto assets_data = jsonParcer.ParseFile(System::String(JoinW({ path, L"assets", L"indexes", StrDogW(data["assets"]->to_stringW(), L".json")})).ToString());
    
    // The assets has a hash. e.g. c4dbabc820f04ba685694c63359429b22e3a62b5
    // With this hash, it can be download from https://resources.download.minecraft.net/c4/c4dbabc820f04ba685694c63359429b22e3a62b5
    // And saved at assets/objects/c4/c4dbabc820f04ba685694c63359429b22e3a62b5
    //callback.get("setMax", empty)(len(assets_data["objects"]) - 1)
    int count = 0;
    for each (auto var in assets_data->get_value("objects")->get_value())
    {
        DownloadFile(StrDogW({ L"https://resources.download.minecraft.net/", var->second->get_value("hash")[0]->to_stringW(), var->second->get_value("hash")[1]->to_stringW(), L"/", var->second->get_value("hash")->to_stringW(), JoinW({path, L"assets", L"objects", var->second->get_value("hash")[0]->to_stringW(), var->second->get_value("hash")[1]->to_stringW(), var->second->get_value("hash")->to_stringW()}) }), NULL, callback);
        ++count;
        //callback.get("setProgress", empty)(count)
    }
    return true;
}

bool MCCL::install_jvm_runtime(wchar_t* jvm_version, wchar_t* minecraft_directory, CallbackNull callback)
{
    /*
    Installs the given jvm runtime. callback is the same dict as in the install module.
    */
    wchar_t* _JVM_MANIFEST_URL = L"https://launchermeta.mojang.com/v1/products/java-runtime/2ec0cc96c44e5a76b9c8b7c39df7210883d12871/all.json";

    Json::JsonParcer jsonParcer;
    wchar_t* platform_string = _get_jvm_platform_string();
    auto manifest_data = jsonParcer.ParseFile(System::String(DownloadFile(_JVM_MANIFEST_URL)).ToString());

    // Check if the jvm version exists
    if (!manifest_data->get_value(System::String(platform_string).ToString())->is_exist(System::String(jvm_version).ToString()))
    {
        System::Console::Write("Version Not Found");
        System::Console::WriteLine(System::String(jvm_version).ToString());
        return false;
    }

    // Check if there is a platform manifest
    if (manifest_data[platform_string][jvm_version]->to_int() == 0)
    {
        return nullptr;
    }

    auto platform_manifest = jsonParcer.ParseFile(System::String(DownloadFile(manifest_data[platform_string][jvm_version][0]["manifest"]["url"]->to_stringW())).ToString());
    wchar_t* base_path = JoinW({ minecraft_directory, L"runtime", jvm_version, platform_string, jvm_version });

    // Download all files of the runtime
    //callback.get("setMax", empty)(len(platform_manifest["files"]) - 1)
    int count = 0;
    for each (auto var in platform_manifest["files"]->get_value())
    {
        pin_ptr<const wchar_t> wch_firs = PtrToStringChars(var->first);
        wchar_t* current_path = JoinW({ base_path, const_cast<wchar_t*>(wch_firs)});
        if (var->second["type"]->to_string() == System::String("file").ToString())
        {
            // Prefer downloading the compresses file
            if (var->second["downloads"]->is_exist("lzma"))
            {
                DownloadFile(var->second["downloads"]["lzma"]["url"]->to_stringW(), current_path, callback, true);
            }
            else
            {
                DownloadFile(var->second["downloads"]["lzma"]["url"]->to_stringW(), current_path, callback);
            }

            // Make files executable on unix systems
            if (var->second["executable"])
            {   
                if (System::IO::File::Exists(System::String(current_path).ToString()))
                {
                    //TODO subprocess.run(["chmod", "+x", current_path])
                }
            }
        }
        else if (var->second["type"]->to_string() == System::String("directory").ToString())
        {
            int outp = _wmkdir(current_path);
        }
        else if (var->second["type"]->to_string() == System::String("link").ToString())
        {
            //TODO os.symlink(value["target"], current_path)
        }
        // callback.get("setProgress", empty)(count)
        ++count;
    }
    // Create the.version file
    System::IO::StreamWriter^ file = gcnew System::IO::StreamWriter(System::String(JoinW({ minecraft_directory, L"runtime", jvm_version, platform_string, L".version" })).ToString());
    file->Write(manifest_data[platform_string][jvm_version][0]["version"]["name"]->to_string());
    file->Close();
    return true;
}

wchar_t* MCCL::get_arguments(Json::JsonValue^ data, Json::JsonValue^ versionData, wchar_t* path, MCCL::Option::MinecraftOptions options)
{
    /*
    Returns all arguments from the version.json
    */

    wchar_t* arglist = NULL;
    if (data->get_type() == Json::JsonTypes::ARRAY)
    {
        for each (auto var in data->get_value_list())
        {
            // Rules might has 2 different names in different versions.json
            if (!parse_rule_list(var, L"compatibilityRules", options))
            {
                continue;
            }
            if (!parse_rule_list(var, L"rules", options))
            {
                continue;
            }
            // var could be the argument
            if (var->get_type() == Json::JsonTypes::STRING)
            {
                arglist = StrDogW(arglist, MCCL::replace_arguments(var->to_string(), versionData, path, options));
                arglist = StrDogW(arglist, L" ");
            }
            else
            {
                // Sometimes  var["value"] is the argument
                if (var["value"]->get_type() == Json::JsonTypes::STRING)
                {
                    arglist = StrDogW(arglist, MCCL::replace_arguments(var["value"]->to_string(), versionData, path, options));
                    arglist = StrDogW(arglist, L" ");
                }
                // Sometimes var["value"] is a list of arguments
                else
                {
                    for each (auto v in var["value"]->get_value())
                    {
                        wchar_t* val = v->second->to_stringW();
                        val = replace_arguments(v->second->to_string(), versionData, path, options);
                        arglist = StrDogW(arglist, val);
                        arglist = StrDogW(arglist, L" ");
                    }
                }
            }
        }
    }
    else
    {
        for each (auto var in data->get_value())
        {
            // Rules might has 2 different names in different versions.json
            if (!parse_rule_list(var->second, L"compatibilityRules", options))
            {
                continue;
            }
            if (!parse_rule_list(var->second, L"rules", options))
            {
                continue;
            }
            // var could be the argument
            if (var->second->get_type() == Json::JsonTypes::STRING)
            {
                arglist = StrDogW(arglist, MCCL::replace_arguments(var->second->to_string(), versionData, path, options));
                arglist = StrDogW(arglist, L" ");
            }
            else
            {
                // Sometimes  var["value"] is the argument
                if (var->second["value"]->get_type() == Json::JsonTypes::STRING)
                {
                    arglist = StrDogW(arglist, MCCL::replace_arguments(var->second["value"]->to_string(), versionData, path, options));
                    arglist = StrDogW(arglist, L" ");
                }
                // Sometimes var["value"] is a list of arguments
                else
                {
                    for each (auto v in var->second["value"]->get_value())
                    {
                        wchar_t* val = v->second->to_stringW();
                        val = replace_arguments(v->second->to_string(), versionData, path, options);
                        arglist = StrDogW(arglist, val);
                        arglist = StrDogW(arglist, L" ");
                    }
                }
            }
        }
    }
    return arglist;
}

wchar_t* MCCL::get_arguments_string(Json::JsonValue^ versionData, wchar_t* path, MCCL::Option::MinecraftOptions options)
{
    /*
    Turns the argument string from the version.json into a list
    */
    wchar_t* arglist = NULL;
    for each (auto var in versionData["minecraftArguments"]->to_string()->Split(' '))
    {
        pin_ptr<const wchar_t> wch_var = PtrToStringChars(var);
        wchar_t* v = const_cast<wchar_t*>(wch_var);
        v = replace_arguments(var, versionData, path, options);
        arglist = StrDogW(arglist, v);
        arglist = StrDogW(arglist, L" ");
    }
    // Custom resolution is not in the list
    if (options.get(L"customResolution", false))
    {
        arglist = StrDogW(arglist, L"--width");
        arglist = StrDogW(arglist, L" ");
        arglist = StrDogW(arglist, options.get(L"resolutionWidth", L"854"));
        arglist = StrDogW(arglist, L" ");
        arglist = StrDogW(arglist, L"--height");
        arglist = StrDogW(arglist, L" ");
        arglist = StrDogW(arglist, options.get(L"resolutionHeight", L"480"));
        arglist = StrDogW(arglist, L" ");
    }
    if (options.get(L"demo", false)) 
    {
        arglist = StrDogW(arglist, L"--demo");
        arglist = StrDogW(arglist, L" ");
    }

    return arglist;
}

bool MCCL::Forge::install_forge_version(wchar_t* versionid, wchar_t* path, CallbackNull callback, wchar_t* java)
{
    /*
    Installs a forge version. Fore more information look at the documentation.
    */

    System::String^ rand = System::Random().Next(1, 100000).ToString();
    pin_ptr<const wchar_t> wch_rand = PtrToStringChars(rand);

    wchar_t* FORGE_DOWNLOAD_URL = StrDogW({ L"https://files.minecraftforge.net/maven/net/minecraftforge/forge/", versionid, L"/forge-", versionid, L"-installer.jar" });
    wchar_t* temp_file_path = StrDogW({ Additionals::TempFile::get_tempdir_SYSTEM(), StrDogW({L"forge-installer-", const_cast<wchar_t*>(wch_rand), L".tmp"}) });
    if (DownloadFile(FORGE_DOWNLOAD_URL, temp_file_path, callback) == nullptr)
    {
        System::Console::Write("Version Not Found");
        System::Console::WriteLine(System::String(versionid).ToString());
        return false;
    }
    System::IO::Compression::ZipArchive^ zArchive = System::IO::Compression::ZipFile::OpenRead(System::String(temp_file_path).ToString());

    // Read the install_profile.json
    Json::JsonParcer json_parcer;
    Json::JsonValue^ version_data;
    for each (auto var in zArchive->Entries)
    {
        if (var->FullName == "install_profile.json")
        {
            array<unsigned char>^ f;
            f->Resize(f, 50000);

            var->Open()->Read(f, 0, 50000); //FIXME 50000 символов передлать в динамическиое вычисление кол-во символов

            System::Text::Encoding^ enc = System::Text::Encoding::UTF8;
            System::String^ json_str = enc->GetString(f);

            version_data = json_parcer.ParseJson(json_str);

            break;
        }
    }
    wchar_t* forge_version_id = version_data["version"]->to_stringW();
    System::String^ forge_version_id2 = System::String(forge_version_id).ToString();

    // Make sure, the base version is installed
    install_minecraft_version(version_data["minecraft"]->to_stringW(), path, callback);

    // Install all needed libs from install_profile.json
    install_libraries(version_data, path, callback);

    // Extract the version.json
    pin_ptr<const wchar_t> wch_forge_version_id = PtrToStringChars(forge_version_id2);
    wchar_t* version_json_path = JoinW({ path, L"versions", const_cast<wchar_t*>(wch_forge_version_id), StrDogW(const_cast<wchar_t*>(wch_forge_version_id), L".json") });
    extract_file(zArchive, L"version.json", version_json_path);

    // Extract forge libs from the installer
    wchar_t* forge_lib_path = JoinW({ path, L"libraries", L"net", L"minecraftforge", L"forge", versionid });
    extract_file(zArchive, StrDogW({ L"maven/net/minecraftforge/forge/", versionid, L"/forge-", versionid, L".jar" }), JoinW({ forge_lib_path, StrDogW({L"forge-", versionid, L".jar"}) }));
    extract_file(zArchive, StrDogW({ L"maven/net/minecraftforge/forge/", versionid, L"/forge-", versionid, L"-universal.jar" }), JoinW({ forge_lib_path, StrDogW({L"forge-", versionid, L"-universal.jar"}) }));

    // Extract the client.lzma
    wchar_t* lzma_path = StrDogW({ Additionals::TempFile::get_tempdir_SYSTEM(), StrDogW({ L"lzma-", const_cast<wchar_t*>(wch_rand), L".tmp" }) });

    extract_file(zArchive, L"data/client.lzma", lzma_path);
    
    // Install the rest with the vanilla function
    install_minecraft_version(forge_version_id, path, callback);

    // Run the processors
    forge_processors(version_data, path, lzma_path, temp_file_path, callback, java);

    delete(zArchive);

    // Delete the temporary files
    System::IO::File::Delete(System::String(temp_file_path).ToString());
    if (System::IO::File::Exists(System::String(lzma_path).ToString()) && System::IO::File::GetAttributes(System::String(lzma_path).ToString()) != System::IO::FileAttributes::Directory)
    {
        System::IO::File::Delete(System::String(lzma_path).ToString());
    }


    return true;
}

bool MCCL::Forge::extract_file(System::IO::Compression::ZipArchive^ handler, wchar_t* zip_path, wchar_t* extract_path)
{
    /*
    Extract a file from a zip handler into the given path
    */
    pin_ptr<const wchar_t> wch = PtrToStringChars(System::IO::Path::GetDirectoryName(System::String(extract_path).ToString()));
    DWORD attrib = GetFileAttributesW(wch);
    if (attrib == INVALID_FILE_ATTRIBUTES || !(attrib & FILE_ATTRIBUTE_DIRECTORY))
    {
        if (!CreateDirectoryW(wch, NULL))
        {
            // Обработка ошибки создания директории
            int error = GetLastError();
            //System::Console::WriteLine(error);
        }
    }
    for each (auto var in handler->Entries)
    {
        if (var->FullName == System::String(zip_path).ToString())
        {
            System::IO::Compression::ZipFileExtensions::ExtractToFile(var, System::String(extract_path).ToString(), true);
            break;
        }
    }

    return true;
}

System::String^ MCCL::Forge::get_data_library_path(wchar_t* libname, wchar_t* path)
{
    /*
    Turns the libname into a path
    */
    for (int i = 0; libname[i] != '\0'; i++)
    {
        if (i == 0)
        {
            continue;
        }
        if (libname[i + 1] == '\0')
        {
            continue;
        }
        libname[i - 1] = libname[i];
    }
    wchar_t* libpath = JoinW({ path, L"libraries" });
    System::String^ base_path = System::String(libname).ToString()->Split(':')[0];
    System::String^ libname_str = System::String(libname).ToString()->Split(':')[1];
    System::String^ version = System::String(libname).ToString()->Split(':')[2];
    System::String^ extra = System::String(libname).ToString()->Split(':')[3];
    System::String^ fileend;

    for each (auto var in base_path->Split('.'))
    {
        pin_ptr<const wchar_t> wch_var = PtrToStringChars(var);
        libpath = JoinW({ libpath, const_cast<wchar_t*>(wch_var) });

        if (extra->Split('@')[0] == extra)
        {
            fileend = "jar";
        }
        else
        {
            extra = extra->Split('@')[0];
            fileend = extra->Split('@')[1];
        }
    }

    pin_ptr<const wchar_t> wch_1 = PtrToStringChars(version);
    pin_ptr<const wchar_t> wch_2 = PtrToStringChars(extra);
    pin_ptr<const wchar_t> wch_3 = PtrToStringChars(fileend);

    libpath = JoinW({ libpath, libname, const_cast<wchar_t*>(wch_1), StrDogW({libname, L"-", const_cast<wchar_t*>(wch_1), L"-", const_cast<wchar_t*>(wch_2), L".", const_cast<wchar_t*>(wch_3)}) });
    return System::String(libpath).ToString();
}

wchar_t* MCCL::Forge::get_jar_mainclass(wchar_t* path)
{
    /*
    Returns the mainclass of a given jar
    */
    System::IO::Compression::ZipArchive^ zArchive = System::IO::Compression::ZipFile::OpenRead(System::String(path).ToString());

    // Parse the MANIFEST.MF
    for each (auto var in zArchive->Entries)
    {

    }
    System::Console::WriteLine("get_jar_mainclass is not done blyat");

    return nullptr;
}

bool MCCL::Forge::forge_processors(Json::JsonValue^ data, wchar_t* minecraft_directory, wchar_t* lzma_path, wchar_t* installer_path, CallbackNull callback, wchar_t* java)
{
    /*
    Run the processors of the install_profile.json
    */
    System::String^ rand = System::Random().Next(1, 100000).ToString();
    pin_ptr<const wchar_t> wch_rand = PtrToStringChars(rand);
    wchar_t* path = minecraft_directory;

    Json::JsonValue^ argument_vars = gcnew Json::JsonObject();
    Json::JsonValue^ value_ = gcnew Json::JsonString(System::String(JoinW({ path, L"versions", data["minecraft"]->to_stringW(), StrDogW(data["minecraft"]->to_stringW(), L".jar") })).ToString());
    argument_vars->add_value("{MINECRAFT_JAR}", value_);

    for each (auto var in data["data"]->get_value())
    {
        if (var->second["client"]->to_string()->StartsWith("[") && var->second["client"]->to_string()->EndsWith("]"))
        {
            argument_vars["{" + var->first + "}"]->operator=(get_data_library_path(var->second["client"]->to_stringW(), path));
        }
        else
        {
            argument_vars["{" + var->first + "}"]->operator=(var->second["client"]);
        }
    }
    wchar_t* root_path = JoinW({ Additionals::TempFile::get_tempdir_SYSTEM(), StrDogW(L"forge-root-", const_cast<wchar_t*>(wch_rand)) });

    argument_vars["{INSTALLER}"]->operator=(System::String(installer_path).ToString());
    argument_vars["{BINPATCH}"]->operator=(System::String(lzma_path).ToString());
    argument_vars["{ROOT}"]->operator=(System::String(root_path).ToString());
    argument_vars["{SIDE}"]->operator=("client");

    wchar_t* classpath_seperator = NULL;
    if (System::String(OS) == System::String("Windows"))
    {
        classpath_seperator = L";";
    }
    else
    {
        classpath_seperator = L":";
    }

    //callback.get("setMax", empty)(len(data["processors"]))
    callback.OnProgress(NULL, data["processors"]->to_int(), NULL, NULL);

    int count = -1;
    for each (auto var in data["processors"]->get_value_list())
    {
        ++count;

        if (!(var["sides"]->is_exist("client")) || !(var["sides"] == var ? true : false))
        {
            // Skip server side only processors
            continue;
        }
        callback.OnProgress(NULL, NULL, NULL, StrDogW(L"Running processor ", var["jar"]->to_stringW()));

        // Get the classpath
        wchar_t* classpath = L"";
        for each (auto var2 in var["classpath"]->get_value_list())
        {
            classpath = StrDogW({ classpath, get_library_path(var2->to_stringW(), path), classpath_seperator });
        }

        classpath = StrDogW(classpath, get_library_path(var["jar"]->to_stringW(), path));
        wchar_t* mainclass = get_jar_mainclass(get_library_path(var["jar"]->to_stringW(), path));
        System::Collections::Generic::List<System::String^> command;
        command[0] = java == NULL || System::String(java) == System::String(L"") ? System::String(L"java").ToString() : System::String(java).ToString() + L"-cp", classpath, mainclass;

        wchar_t* variable = NULL;
        for each (auto var2 in var["args"]->get_value_list())
        {
            variable = argument_vars[var2->to_string()] == nullptr ? var2->to_stringW() : argument_vars[var2->to_string()]->to_stringW();
            if (System::String(variable).ToString()->StartsWith("[") && System::String(variable).ToString()->EndsWith("]"))
            {
                command.Add(System::String(get_library_path(variable, path)).ToString());
            }
            else
            {
                command.Add(System::String(variable).ToString());
            }
        }

        for each (auto var2 in argument_vars->get_value())
        {
            for (int i = 0; i < command.Count; i++)
            {
                command[i] = command[i]->Replace(var2->first, var2->second->to_string());
            }
        }

        wchar_t* commant_strw = NULL;
        for (int i = 0; i < command.Count; i++)
        {
            pin_ptr<const wchar_t> wch_comm = PtrToStringChars(command[i]);
            commant_strw = StrDogW(commant_strw, const_cast<wchar_t*>(wch_comm));
        }

        int out = _wsystem(commant_strw);

        callback.OnProgress(count, NULL, NULL, NULL);
    }
    if (System::IO::Directory::Exists(System::String(root_path).ToString()))
    {
        System::IO::Directory::Delete(System::String(root_path).ToString());
    }

    return true;
}

bool MCCL::ModPacks::install_mod_pack(wchar_t* versionid, wchar_t* path, CallbackNull callback)
{

    return false;
}
