#include "Minecraftus.h"




wchar_t* MinecraftCpp::option::MinecraftOptions::get(const wchar_t* param, const wchar_t* writ)
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

    wchar_t* field = nullptr;

    if (std::wstring(param) == std::wstring(L"username"))
        field = this->username;
    else if (std::wstring(param) == std::wstring(L"uuid"))
        field = this->uuid;
    else if (std::wstring(param) == std::wstring(L"token"))
        field = this->token;
    else if (std::wstring(param) == std::wstring(L"executablePath"))
        field = this->executablePath;
    else if (std::wstring(param) == std::wstring(L"jvmArguments"))
        field = this->jvmArguments;
    else if (std::wstring(param) == std::wstring(L"launcherName"))
        field = this->launcherName;
    else if (std::wstring(param) == std::wstring(L"launcherVersion"))
        field = this->launcherVersion;
    else if (std::wstring(param) == std::wstring(L"gameDirectory"))
        field = this->gameDirectory;
    else if (std::wstring(param) == std::wstring(L"resolutionWidth"))
        field = this->resolutionWidth;
    else if (std::wstring(param) == std::wstring(L"resolutionHeight"))
        field = this->resolutionHeight;
    else if (std::wstring(param) == std::wstring(L"server"))
        field = this->server;
    else if (std::wstring(param) == std::wstring(L"port"))
        field = this->port;
    else if (std::wstring(param) == std::wstring(L"nativesDirectory"))
        field = this->nativesDirectory;
    else
        return this->NULLES;

    if (writ == nullptr)
    {
        return field;
    }
    else if (field == nullptr)
    {
        field = const_cast<wchar_t*>(writ);
        return field;
    }
    else
    {
        return field;
    }
}

bool MinecraftCpp::option::MinecraftOptions::get(const wchar_t* param, bool writ)
{
    bool field = false;

    if (std::wstring(param) == std::wstring(L"demo"))
        field = &this->demo;
    else if (std::wstring(param) == std::wstring(L"customResolution"))
        field = &this->customResolution;
    else if (std::wstring(param) == std::wstring(L"enableLoggingConfig"))
        field = &this->enableLoggingConfig;
    else
        return false;

    if (!writ)
        return field;

    if (field)
        return field;

    field = writ;
    return field;
}


bool MinecraftCpp::option::MinecraftOptions::is_exist(wchar_t* param)
{
    if (std::wstring(param) == L"username" ||
        std::wstring(param) == L"uuid" ||
        std::wstring(param) == L"token" ||
        std::wstring(param) == L"executablePath" ||
        std::wstring(param) == L"jvmArguments" ||
        std::wstring(param) == L"launcherName" ||
        std::wstring(param) == L"launcherVersion" ||
        std::wstring(param) == L"gameDirectory" ||
        std::wstring(param) == L"resolutionWidth" ||
        std::wstring(param) == L"resolutionHeight" ||
        std::wstring(param) == L"server" ||
        std::wstring(param) == L"port" ||
        std::wstring(param) == L"nativesDirectory" ||
        std::wstring(param) == L"demo" ||
        std::wstring(param) == L"customResolution" ||
        std::wstring(param) == L"enableLoggingConfig")
    {
        return true;
    }
    else
    {
        return false;
    }
}


bool MinecraftCpp::install_minecraft_version(wchar_t* versionid, wchar_t* minecraft_directory, CallbackNull callback)
{
    /*
    Install a Minecraft Version. Fore more Information take a look at the documentation"
    */
    Json::JsonParcer json_manifest;

    wchar_t* full_dir = JoinW({ minecraft_directory , L"versions" , versionid, StrDogW(versionid, L".json") });

    wchar_t* download_dir = JoinW({ minecraft_directory, L"downloads" });

    if (!std::filesystem::exists(download_dir)) {
        int out_mkdir = _wmkdir(download_dir);
        std::cout << "java dir is maked with status: " << out_mkdir << std::endl;
    }

    if (std::filesystem::exists(full_dir))
    {
        if (std::filesystem::is_directory(full_dir))
        {
            do_version_install(versionid, minecraft_directory, callback);
            return true;
        }
    }
    
    wchar_t* version_manifest_file = DownloadFile(L"https://launchermeta.mojang.com/mc/game/version_manifest.json",
        download_dir, callback);

    auto version_list = json_manifest.ParseFile(version_manifest_file);

    for (auto var : version_list->get_value("versions")->get_value_list())
    {
        if (std::wstring((*var)["id"]->to_stringW()) == std::wstring(versionid))
        {
            do_version_install(versionid, minecraft_directory, callback, var->get_value("url")->to_stringW());
            return true;
        }
    }
	return false;
}

bool MinecraftCpp::do_version_install(wchar_t* versionid, wchar_t* path, CallbackNull callback, wchar_t* url)
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
    auto versiondata = json_verid.ParseFile(path_ver_json);

    // For forge
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
    if (!std::filesystem::is_directory(JoinW({ path, L"versions", versiondata->get_value("id")->to_stringW(), StrDogW(versiondata->get_value("id")->to_stringW(), L".jar") })) && versiondata->is_exist("inheritsFrom"))
    {
        std::filesystem::copy
        (
            std::wstring
            (
                JoinW
                ({
                    path,
                    L"versions",
                    versiondata->get_value("id")->to_stringW(),
                    StrDogW
                    (
                        versiondata->get_value("id")->to_stringW(),
                        L".jar"
                    ) 
                })
            ),
            std::wstring
            (
                JoinW
                ({
                    path,
                    L"versions",
                    versiondata->get_value("inheritsFrom")->to_stringW(),
                    StrDogW
                    (
                        versiondata->get_value("inheritsFrom")->to_stringW(),
                        L".jar"
                    )
                })
            )
        );
    }

    //Install java runtime if needed
    if (versiondata->is_exist("javaVersion"))
    {
        install_jvm_runtime(versiondata->get_value("javaVersion")->get_value("component")->to_stringW(), path, callback);
    }

    return true;
}

Json::JsonValue* MinecraftCpp::inherit_json(Json::JsonValue* original_data, wchar_t* path)
{
    /*
    Implement the inheritsFrom function
    See https://github.com/tomsik68/mclauncher-api/wiki/Version-Inheritance-&-forge
    */
    auto inherit_version = original_data->get_value("inheritsFrom");

    wchar_t* path_inh_json = JoinW({ path, L"versions", inherit_version->to_stringW(), StrDogW(inherit_version->to_stringW(), L".json")});
    Json::JsonParcer json_inherit;
    auto new_data = json_inherit.ParseFile(path_inh_json);
    for (auto& var : original_data->get_value())
    {
        if (var.second->get_type() == Json::JsonTypes::Array && new_data->get_value(var.first)->get_type() == Json::JsonTypes::Array)
        {
            new_data->get_value(var.first)->operator=((*var.second) + (*new_data)[var.first]);
        }
        else if (var.second->get_type() == Json::JsonTypes::Object && new_data->get_value(var.first)->get_type() == Json::JsonTypes::Object)
        {
            for (auto& variable : var.second->get_value())
            {
                if (variable.second->get_type() == Json::JsonTypes::Array)
                {
                    new_data->get_value(var.first)->get_value(variable.first)->operator=
                        ((*new_data->get_value(var.first)->get_value(variable.first)) + variable.second);
                }
            }
        }
        else
        {
            if (new_data->is_exist(var.first))
            {
                new_data->get_value(var.first)->operator=(var.second);
            }
            else
            {
                new_data->add_value(var.first, var.second);
            }
        }
    }
    return new_data;
}

wchar_t* MinecraftCpp::get_minecraft_command__(wchar_t* version, wchar_t* minecraft_directory, MinecraftCpp::option::MinecraftOptions options)
{
    /*
    Returns a command for launching Minecraft.For more information take a look at the documentation.
    */
    if (!std::filesystem::exists(JoinW({ minecraft_directory, L"versions", version, StrDogW(version, L".json") })) || 
        std::filesystem::is_directory(JoinW({minecraft_directory, L"versions", version})))
    {
        std::cout << "Version Not Found" << version << std::endl;
        return nullptr;
    }

    Json::JsonParcer json_parcer;
    auto data = json_parcer.ParseFile(JoinW({ minecraft_directory, L"versions", version, StrDogW(version, L".json") }));

    if (data->is_exist("inheritsFrom"))
    {
        data = MinecraftCpp::inherit_json(data, minecraft_directory);
    }
    options.nativesDirectory = options.get(L"nativesDirectory", JoinW({ minecraft_directory, L"versions", (*data)["id"]->to_stringW(), L"natives" }));
    //options.nativesDirectory = JoinW({ minecraft_directory, L"versions", data["id"]->to_stringW(), L"natives" });
    options.classpath = MinecraftCpp::get_libraries(data, minecraft_directory);

    wchar_t* command = NULL;

    // Add Java executable
    if (options.executablePath != NULL)
    {
        command = StrDogW(command, options.executablePath);
        command = StrDogW(command, L" ");
    }
    else if (data->is_exist("javaVersion"))
    {
        wchar_t* java_path = MinecraftCpp::get_executable_path((*(*data)["javaVersion"])["component"]->to_stringW(), minecraft_directory);
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
    if (data->get_value("arguments")->get_type() == Json::JsonTypes::Object)
    {
        if (data->get_value("arguments")->is_exist("jvm"))
        {
            command = StrDogW(command, MinecraftCpp::get_arguments((*(*data)["arguments"])["jvm"], data, minecraft_directory, options));
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

    command = StrDogW(command, (*data)["mainClass"]->to_stringW());
    command = StrDogW(command, L" ");
    if (data->is_exist("minecraftArguments"))
    {
        // For older versions
        command = StrDogW(command, MinecraftCpp::get_arguments_string(data, minecraft_directory, options));
        command = StrDogW(command, L" ");
    }
    else
    {
        command = StrDogW(command, MinecraftCpp::get_arguments(data->get_value("arguments")->get_value("game"), data, minecraft_directory, options));
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

wchar_t* MinecraftCpp::get_libraries(Json::JsonValue* data, wchar_t* path)
{
    /*
    Returns the argument with all libs that come after -cp
    */
    wchar_t* classpath_seperator = MinecraftCpp::get_classpath_separator();
    wchar_t* libstr;
    wchar_t* native;
    MinecraftCpp::option::MinecraftOptions empty;
    int debug = 0;
    if ((*data)["libraries"]->get_count() == 1)
    {
        for (auto var : (*(*data)["libraries"])[0]->get_value_list())
        {
            if (!(MinecraftCpp::parse_rule_list(var, L"rules", empty)))
            {
                continue;
            }
            libstr = StrDogW(libstr, StrDogW(MinecraftCpp::get_library_path(var->get_value("name")->to_stringW(), path), classpath_seperator));
            native = MinecraftCpp::get_natives(var);
            if (std::wstring(native) != std::wstring(L""))
            {
                if (var->is_exist("downloads"))
                {
                    libstr = StrDogW(libstr, StrDogW(JoinW({ path, L"libraries", (*var->get_value("downloads")->get_value("classifiers"))[native]->get_value("path")->to_stringW() }), classpath_seperator));
                }
                else
                {
                    libstr = StrDogW(libstr, StrDogW(MinecraftCpp::get_library_path(StrDogW(var->get_value("name")->to_stringW(), StrDogW(L"-", native)), path), classpath_seperator));
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
        for (auto var : data->get_value("libraries")->get_value_list())
        {
            if (!(MinecraftCpp::parse_rule_list(var, L"rules", empty)))
            {
                continue;
            }
            libstr = StrDogW(libstr, StrDogW(MinecraftCpp::get_library_path(var->get_value("name")->to_stringW(), path), classpath_seperator));
            native = MinecraftCpp::get_natives(var);
            if (std::wstring(native) != std::wstring(L""))
            {
                if (var->is_exist("downloads"))
                {
                    libstr = StrDogW(libstr, StrDogW(JoinW({ path, L"libraries", (*var->get_value("downloads")->get_value("classifiers"))[native]->get_value("path")->to_stringW() }), classpath_seperator));
                }
                else
                {
                    libstr = StrDogW(libstr, StrDogW(MinecraftCpp::get_library_path(StrDogW(var->get_value("name")->to_stringW(), StrDogW(L"-", native)), path), classpath_seperator));
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

bool MinecraftCpp::start_minecraft(wchar_t* java_path, wchar_t* args)
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

wchar_t* MinecraftCpp::get_classpath_separator()
{
    /*
    Returns the classpath seperator for the current os
    */
    if (std::wstring(OS) == std::wstring(L"Windows"))
    {
        return const_cast<wchar_t*>(std::wstring(L";").c_str());
    }
    else
    {
        return const_cast<wchar_t*>(std::wstring(L":").c_str());
    }
}

bool MinecraftCpp::parse_rule_list(Json::JsonValue* data, const wchar_t* rule_string, MinecraftCpp::option::MinecraftOptions options)
{
    /*
    Parse a list of rules
    */
    if (!data->is_exist(Additionals::Convectors::ConvertWcharPtrToString(rule_string)))
    {
        return true;
    }
    for (auto var : (*data)[rule_string]->get_value_list())
    {
        if (!MinecraftCpp::parse_single_rule(var, options))
        {
            return false;
        }
    }
    return true;
}

bool MinecraftCpp::parse_single_rule(Json::JsonValue* rule, MinecraftCpp::option::MinecraftOptions options)
{
    /*
    Parse a single rule from the versions.json
    */
    bool returnvalue = false;
    if ((*rule)["action"]->to_string() == "allow")
    {
        returnvalue = false;
    }
    else if ((*rule)["action"]->to_string() == "disallow")
    {
        returnvalue = true;
    }
    if (rule->is_exist("os"))
    {
        for (auto& var : (*rule)["os"]->get_value())
        {
            if (var.first == "name")
            {
                if (var.second->to_string() == "windows" && std::wstring(OS) != std::wstring(L"Windows"))
                {
                    return returnvalue;
                }
                else if (var.second->to_string() == "osx" && std::wstring(OS) != std::wstring(L"Darwin"))
                {
                    return returnvalue;
                }
                else if (var.second->to_string() == "linux" && std::wstring(OS) != std::wstring(L"Linux"))
                {
                    return returnvalue;
                }
            }
            else if (var.first == "arch")
            {
                if (var.second->to_string() == "x86" && std::wstring(ARCH) != std::wstring(L"x86"))
                {
                    return returnvalue;
                }
            }
            else if (var.first == "version")
            {
                if (std::wstring(var.second->to_stringW()) != std::wstring(OS))
                {
                    return returnvalue;
                }
            }
        }
    }
    if (rule->is_exist("features"))
    {
        for (auto& var : (*rule)["features"]->get_value())
        {
            if (var.first == "has_custom_resolution" && !options.get(L"customResolution", false))
            {
                return returnvalue;
            }
            else if (var.first == "is_demo_user" && !options.get(L"demo", false))
            {
                return returnvalue;
            }
        }
    }
    return !returnvalue;
}

wchar_t* MinecraftCpp::get_library_path(wchar_t* name, wchar_t* path)
{
    /*
    Returns the path from a libname
    */

    wchar_t* libpath = JoinW({ path, L"libraries" });

    auto parts = Additionals::String::split(name, ':');
    std::wstring base_path = parts[0];
    std::wstring libname = parts[1];
    std::wstring version = parts[2];
    std::wstring fileend;

    for (auto& var : Additionals::String::split(base_path, '.'))
    {
        libpath = JoinW({ libpath, var.c_str()});
    }
    if (version.find('@'))
    {
        auto splt = Additionals::String::split(version, '@', 2);
        version = splt[0];
        fileend = splt[1];
    }
    else
    {
        fileend = L"jar";
    }
    // construct a filename with the remaining parts

    wchar_t* filename = NULL;
    
    //parts->CopyTo(parts_2, 3);
    int count = 0;
    for (auto& var : parts)
    {
        ++count;
    }
    /*array<System::String^>^ parts_2 = gcnew array<System::String^>(count - 2);
    for (int i = 0; i < count - 2; i++)
    {
        parts_2[i] = parts[i + 2];
    }*/
    //filename = StrDogW({ const_cast<wchar_t*>(wch_libname), L"-", const_cast<wchar_t*>(wch_version) });
    for (auto& var : parts)
    {
        filename = StrDogW(libname.c_str(), StrDogW(L"-", var.c_str()));
    }
    filename = StrDogW(filename, StrDogW(L".", fileend.c_str()));

    libpath = JoinW({ libpath, libname.c_str(), version.c_str(), filename});
    return libpath;
}

wchar_t* MinecraftCpp::get_natives(Json::JsonValue* data)
{
    /*
    Returns the native part from the json data
    */
    std::wstring arch_type;
    if (std::wstring(ARCH) == std::wstring(L"x86"))
    {
        arch_type = L"32";
    }
    else
    {
        arch_type = L"64";
    }

    if (data->is_exist("natives"))
    {
        if (std::wstring(OS) == std::wstring(L"Windows"))
        {
            if ((*data)["natives"]->is_exist("windows"))
            {
                std::string replace_string = data->operator[]("natives")->operator[]("windows")->to_string();
                Additionals::String::replace(replace_string, "${arch}", Additionals::Convectors::ConvertWcharPtrToString(arch_type.c_str()));
                return Additionals::Convectors::ConvertStringToWcharPtr(replace_string);
            }
            else
            {
                return const_cast<wchar_t*>(L"");
            }
        }
        else if (std::wstring(OS) == std::wstring(L"Darwin"))
        {
            if ((*data)["natives"]->is_exist("osx"))
            {
                std::string replace_string = (*(*data)["natives"])["osx"]->to_string();
                Additionals::String::replace(replace_string, "${arch}", Additionals::Convectors::ConvertWcharPtrToString(arch_type.c_str()));
                return Additionals::Convectors::ConvertStringToWcharPtr(replace_string);
            }
            else
            {
                return const_cast<wchar_t*>(L"");
            }
        }
        else
        {
            if ((*data)["natives"]->is_exist("linux"))
            {
                std::string replace_string = (*(*data)["natives"])["linux"]->to_string();
                Additionals::String::replace(replace_string, "${arch}", Additionals::Convectors::ConvertWcharPtrToString(arch_type.c_str()));
                return Additionals::Convectors::ConvertStringToWcharPtr(replace_string);
            }
            else
            {
                return const_cast<wchar_t*>(L"");
            }
        }
    }
    else
    {
        return const_cast<wchar_t*>(L"");
    }   
}

wchar_t* MinecraftCpp::_get_jvm_platform_string()
{
    /*
    Get the name that is used the identify the platform
    */
    if (std::wstring(OS) == std::wstring(L"Windows"))
    {
        if (std::wstring(ARCH) == std::wstring(L"x86"))
        {
            return const_cast<wchar_t*>(L"windows-x86");
        }
        else
        {
            return const_cast<wchar_t*>(L"windows-x64");
        }
    }
    else if (std::wstring(OS) == std::wstring(L"Linux"))
    {
        if (std::wstring(ARCH) == std::wstring(L"x86"))
        {
            return const_cast<wchar_t*>(L"linux-i386");
        }
        else
        {
            return const_cast<wchar_t*>(L"linux");
        }
    }
    else if (std::wstring(OS) == std::wstring(L"Darwin"))
    {
        return const_cast<wchar_t*>(L"mac-os");
    }
    return const_cast<wchar_t*>(L"");
}

std::string MinecraftCpp::replace_arguments(std::string argstr, Json::JsonValue* versionData, wchar_t* path, MinecraftCpp::option::MinecraftOptions options)
{
    /*
    Replace all 20 placeholder in arguments with the needed value
    */

    Additionals::String::replace(argstr, "${natives_directory}", Additionals::Convectors::ConvertWcharPtrToString(options.nativesDirectory));
    Additionals::String::replace(argstr, "${launcher_name}", Additionals::Convectors::ConvertWcharPtrToString(options.get(L"launcherName", L"null")));
    Additionals::String::replace(argstr, "${launcher_version}", Additionals::Convectors::ConvertWcharPtrToString(options.get(L"launcherVersion", L"null")));
    Additionals::String::replace(argstr, "${classpath}", Additionals::Convectors::ConvertWcharPtrToString(options.classpath));
    Additionals::String::replace(argstr, "${auth_player_name}", Additionals::Convectors::ConvertWcharPtrToString(options.get(L"username", L"{username}")));
    Additionals::String::replace(argstr, "${version_name}", (*versionData)["id"]->to_string());
    Additionals::String::replace(argstr, "${game_directory}", Additionals::Convectors::ConvertWcharPtrToString(options.get(L"gameDirectory", path)));
    Additionals::String::replace(argstr, "${assets_root}", Additionals::Convectors::ConvertWcharPtrToString(JoinW({ path, L"assets" })));
    Additionals::String::replace(argstr, "${assets_index_name}", (*versionData)["assets"] != nullptr ? (*versionData)["assets"]->to_string() : (*versionData)["id"]->to_string());
    Additionals::String::replace(argstr, "${auth_uuid}", Additionals::Convectors::ConvertWcharPtrToString(options.get(L"uuid", L"{uuid}")));
    Additionals::String::replace(argstr, "${auth_access_token}", Additionals::Convectors::ConvertWcharPtrToString(options.get(L"token", L"{token}")));
    Additionals::String::replace(argstr, "${user_type}", "mojang");
    Additionals::String::replace(argstr, "${version_type}", (*versionData)["type"]->to_string());
    Additionals::String::replace(argstr, "${user_properties}", "{}");
    Additionals::String::replace(argstr, "${resolution_width}", Additionals::Convectors::ConvertWcharPtrToString(options.get(L"resolutionWidth", L"854")));
    Additionals::String::replace(argstr, "${resolution_height}", Additionals::Convectors::ConvertWcharPtrToString(options.get(L"resolutionHeight", L"480")));
    Additionals::String::replace(argstr, "${game_assets}", Additionals::Convectors::ConvertWcharPtrToString(JoinW({ path, L"assets", L"virtual", L"legacy" })));
    Additionals::String::replace(argstr, "${auth_session}", Additionals::Convectors::ConvertWcharPtrToString(options.get(L"token", L"{token}")));
    Additionals::String::replace(argstr, "${library_directory}", Additionals::Convectors::ConvertWcharPtrToString(JoinW({ path, L"libraries" })));
    Additionals::String::replace(argstr, "${classpath_separator}", Additionals::Convectors::ConvertWcharPtrToString(MinecraftCpp::get_classpath_separator()));

    return argstr;
}

wchar_t* MinecraftCpp::get_executable_path(wchar_t* jvm_version, wchar_t* minecraft_directory)
{
    /*
    Returns the path to the executable. Returns None if none is found.
    */
    wchar_t* java_path = JoinW({ minecraft_directory, L"runtime", jvm_version, _get_jvm_platform_string(), jvm_version, L"bin", L"java" });
    if (std::filesystem::exists(java_path))
    {
        if (!std::filesystem::is_directory(java_path))
        {
            return java_path;
        }
        else if (!std::filesystem::is_directory(std::wstring(java_path) + L".exe"))
        {
            return StrDogW(java_path, L".exe");
        }
    }
    
    std::wstring java_w_path = java_path;
    Additionals::String::replace(java_w_path, JoinW({ L"bin", L"java" }), JoinW({ L"jre.bundle", L"Contents", L"Home", L"bin", L"java" }));

    if (std::filesystem::exists(java_w_path))
    {
        if (!std::filesystem::is_directory(java_w_path))
        {
            return const_cast<wchar_t*>(java_w_path.c_str());
        }
        else
        {
            return nullptr;
        }
    }
    return nullptr;
}

bool MinecraftCpp::install_libraries(Json::JsonValue* data, wchar_t* path, CallbackNull callback)
{
    /*
    Install all libraries
    */
    // TODO вызов callback для управление вывода
    
    for (auto var : data->get_value("libraries")->get_value_list())
    {
        MinecraftCpp::option::MinecraftOptions empty;
        // Check, if the rules allow this lib for the current system
        if (!MinecraftCpp::parse_rule_list(var, L"rules", empty))
        {
            continue;
        }
        // Turn the name into a path
        wchar_t* currentPath = JoinW({ path, L"libraries" });
        wchar_t* downloadUrl = NULL;
        if (var->is_exist("url"))
        {
            if (Additionals::String::EndsWith(var->get_value("url")->to_string(), "/"))
            {
                std::string download_string = Additionals::String::rtrim_copy(var->get_value("url")->to_string(), '/');
                downloadUrl = Additionals::Convectors::ConvertStringToWcharPtr(download_string);
            }
            else
            {
                downloadUrl = var->get_value("url")->to_stringW();
            }
        }
        else
        {
            downloadUrl = const_cast<wchar_t*>(L"https://libraries.minecraft.net");
        }

        std::string libPath = Additionals::String::split(var->get_value("name")->to_string(), ':')[0];
        std::string name = Additionals::String::split(var->get_value("name")->to_string(), ':')[1];
        std::string version = Additionals::String::split(var->get_value("name")->to_string(), ':')[2];
        for (auto& var2 : Additionals::String::split(libPath, '.'))
        {
            currentPath = JoinW({ currentPath, Additionals::Convectors::ConvertStringToWcharPtr(var2) });
            downloadUrl = StrDogW({ downloadUrl, L"/", Additionals::Convectors::ConvertStringToWcharPtr(var2) });
        }

        std::string fileend;
        if (Additionals::String::split(version, '@')[0] != version)
        {
            auto splt = Additionals::String::split(version, '@');
            version = splt[0];
            fileend = splt[1];
        }
        else
        {
            fileend = "jar";
        }

        std::string jarFilename = name + "-" + version + "." + fileend;
        downloadUrl = StrDogW({ downloadUrl, L"/", Additionals::Convectors::ConvertStringToWcharPtr(name), L"/", Additionals::Convectors::ConvertStringToWcharPtr(version) });
        currentPath = JoinW({ currentPath, Additionals::Convectors::ConvertStringToWcharPtr(name), Additionals::Convectors::ConvertStringToWcharPtr(version) });
        wchar_t* native = get_natives(var);

        //Check if there is a native file
        wchar_t* jarFilenameNative = NULL;
        if (std::wstring(native) != std::wstring(L""))
        {
            jarFilenameNative = StrDogW({ Additionals::Convectors::ConvertStringToWcharPtr(name), L"-", Additionals::Convectors::ConvertStringToWcharPtr(version), L"-", native, L".jar" });
        }
        jarFilename = name + "-" + version + "." + fileend;
        downloadUrl = StrDogW({ downloadUrl, L"/", Additionals::Convectors::ConvertStringToWcharPtr(jarFilename) });

        //Try to download the lib
        DownloadFile(downloadUrl, JoinW({ currentPath, Additionals::Convectors::ConvertStringToWcharPtr(jarFilename) }), callback);

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
        if (std::wstring(native) != std::wstring(L""))
        {
            DownloadFile(var->get_value("downloads")->get_value("classifiers")->get_value(Additionals::Convectors::ConvertWcharPtrToString(native))->get_value("url")->to_stringW(), JoinW({ currentPath, jarFilenameNative }), callback);
            if (var->get_value("extract"))
            {
                extract_natives_file(JoinW({ currentPath, jarFilenameNative }), JoinW({ path, L"versions", data->get_value("id")->to_stringW(), L"natives" }), var->get_value("extract"));
            }
        }
    }
    return true;
}

bool MinecraftCpp::extract_natives_file(wchar_t* filename, wchar_t* extract_path, Json::JsonValue* extract_data)
{
    /*
    Unpack natives
    */
    int ret = _wmkdir(extract_path);
    Additionals::ziparchives::ZipArchive zArchive;

    if (std::filesystem::exists(filename))
    {
        zArchive.Open(filename);
    }
    else
    {
        return false;
    }
    for (auto& var : zArchive.entries)
    {
        for (auto var2 : extract_data->get_value("exclude")->get_value_list())
        {
            if (var.fileName().startsWith(var2->to_string().c_str()))
            {
                continue;
            }
        }
        int count = 0;
        for (auto& var : Additionals::String::split(var.filesystemFileName(), '.'))
        {
            ++count;
        }
        if (count == 1)
        {
            continue;
        }
        if (!std::filesystem::exists(std::wstring(extract_path) + L"\\" + std::wstring(var.filesystemFileName())))
        {
            
            Additionals::ziparchives::ZipArchive::ExtractFile(var, Additionals::Convectors::ConvertWStringToString(std::wstring(extract_path) + L"\\" + var.filesystemFileName().wstring()));
        }
    }
    return true;
}

bool MinecraftCpp::install_assets(Json::JsonValue* data, wchar_t* path, CallbackNull callback)
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
    auto assets_data = jsonParcer.ParseFile(JoinW({ path, L"assets", L"indexes", StrDogW((*data)["assets"]->to_stringW(), L".json") }));
    
    // The assets has a hash. e.g. c4dbabc820f04ba685694c63359429b22e3a62b5
    // With this hash, it can be download from https://resources.download.minecraft.net/c4/c4dbabc820f04ba685694c63359429b22e3a62b5
    // And saved at assets/objects/c4/c4dbabc820f04ba685694c63359429b22e3a62b5
    //callback.get("setMax", empty)(len(assets_data["objects"]) - 1)
    int count = 0;
    for (auto& var : assets_data->get_value("objects")->get_value())
    {
        DownloadFile(
            StrDogW({ 
                L"https://resources.download.minecraft.net/",
                var.second->get_value("hash")[0].to_stringW(),
                var.second->get_value("hash")[1].to_stringW(),
                L"/",
                var.second->get_value("hash")->to_stringW(),
                JoinW
                ({
                    path, L"assets", L"objects",
                    var.second->get_value("hash")[0].to_stringW(),
                    var.second->get_value("hash")[1].to_stringW(),
                    var.second->get_value("hash")->to_stringW()})
                }),
            NULL,
            callback);

        ++count;
        //callback.get("setProgress", empty)(count)
    }
    return true;
}

bool MinecraftCpp::install_jvm_runtime(wchar_t* jvm_version, wchar_t* minecraft_directory, CallbackNull callback)
{
    /*
    Installs the given jvm runtime. callback is the same dict as in the install module.
    */
    const wchar_t* _JVM_MANIFEST_URL = L"https://launchermeta.mojang.com/v1/products/java-runtime/2ec0cc96c44e5a76b9c8b7c39df7210883d12871/all.json";

    Json::JsonParcer jsonParcer;
    wchar_t* platform_string = _get_jvm_platform_string();
    auto manifest_data = jsonParcer.ParseFile(DDIC::Download::Files::download_file(_JVM_MANIFEST_URL));

    // Check if the jvm version exists
    if (!manifest_data->get_value(Additionals::Convectors::ConvertWcharPtrToString(platform_string))->is_exist(Additionals::Convectors::ConvertWcharPtrToString(jvm_version)))
    {
        std::cout << "Version Not Found" << jvm_version << std::endl;

        return false;
    }

    // Check if there is a platform manifest
    if ((*(*manifest_data)[platform_string])[jvm_version]->to_int() == 0)
    {
        return false;
    }

    auto& platform_manifest = *jsonParcer.ParseFile(DownloadFile((*(*(*(*(*manifest_data)[platform_string])[jvm_version])[0])[L"manifest"])[L"url"]->to_stringW()));
    wchar_t* base_path = JoinW({ minecraft_directory, L"runtime", jvm_version, platform_string, jvm_version });

    // Download all files of the runtime
    //callback.get("setMax", empty)(len(platform_manifest["files"]) - 1)
    int count = 0;
    for (auto& var : platform_manifest["files"]->get_value())
    {
        wchar_t* current_path = JoinW({ base_path, Additionals::Convectors::ConvertStringToWcharPtr(var.first) });
        if (var.second->get_value("type")->to_string() == std::string("file"))
        {
            // Prefer downloading the compresses file
            if (var.second->get_value("downloads")->is_exist("lzma"))
            {
                DownloadFile((*(*var.second->get_value("downloads"))["lzma"])["url"]->to_stringW(), current_path, callback, true);
            }
            else
            {
                DownloadFile((*(*var.second->get_value("downloads"))["lzma"])["url"]->to_stringW(), current_path, callback);
            }

            // Make files executable on unix systems
            if (var.second->get_value("executable"))
            {   
                if (std::filesystem::exists(current_path))
                {
                    //TODO subprocess.run(["chmod", "+x", current_path])
                }
            }
        }
        else if (var.second->get_value("type")->to_string() == "directory")
        {
            int outp = _wmkdir(current_path);
        }
        else if (var.second->get_value("type")->to_string() == "link")
        {
            //TODO os.symlink(value["target"], current_path)
        }
        // callback.get("setProgress", empty)(count)
        ++count;
    }
    // Create the.version file
    std::wstring path = JoinW({ minecraft_directory, L"runtime", jvm_version, platform_string, L".version" });
    
    (*(*(*(*(*manifest_data)[platform_string])[jvm_version])[0])["version"])["name"]->SaveJsonToFile(path, 4);

    return true;
}

wchar_t* MinecraftCpp::get_arguments(
    Json::JsonValue* data,
    Json::JsonValue* versionData,
    wchar_t* path,
    MinecraftCpp::option::MinecraftOptions options)
{
    /*
    Returns all arguments from the version.json
    */

    wchar_t* arglist = NULL;
    if (data->get_type() == Json::JsonTypes::Array)
    {
        for (auto var : data->get_value_list())
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
            if (var->get_type() == Json::JsonTypes::String)
            {
                arglist = StrDogW(arglist, Additionals::Convectors::ConvertStringToWcharPtr(MinecraftCpp::replace_arguments(var->to_string(), versionData, path, options)));
                arglist = StrDogW(arglist, L" ");
            }
            else
            {
                // Sometimes  var["value"] is the argument
                if ((*var)["value"]->get_type() == Json::JsonTypes::String)
                {
                    arglist = StrDogW(arglist, Additionals::Convectors::ConvertStringToWcharPtr(MinecraftCpp::replace_arguments((*var)["value"]->to_string(), versionData, path, options)));
                    arglist = StrDogW(arglist, L" ");
                }
                // Sometimes var["value"] is a list of arguments
                else
                {
                    for (auto& v : (*var)["value"]->get_value())
                    {
                        wchar_t* val = v.second->to_stringW();
                        val = Additionals::Convectors::ConvertStringToWcharPtr(replace_arguments(v.second->to_string(), versionData, path, options));
                        arglist = StrDogW(arglist, val);
                        arglist = StrDogW(arglist, L" ");
                    }
                }
            }
        }
    }
    else
    {
        for (auto& var : data->get_value())
        {
            // Rules might has 2 different names in different versions.json
            if (!parse_rule_list(var.second, L"compatibilityRules", options))
            {
                continue;
            }
            if (!parse_rule_list(var.second, L"rules", options))
            {
                continue;
            }
            // var could be the argument
            if (var.second->get_type() == Json::JsonTypes::String)
            {
                arglist = StrDogW(arglist, Additionals::Convectors::ConvertStringToWcharPtr(MinecraftCpp::replace_arguments(var.second->to_string(), versionData, path, options)));
                arglist = StrDogW(arglist, L" ");
            }
            else
            {
                // Sometimes  var["value"] is the argument
                if (var.second->operator[]("value")->get_type() == Json::JsonTypes::String)
                {
                    arglist = StrDogW(arglist, Additionals::Convectors::ConvertStringToWcharPtr(MinecraftCpp::replace_arguments(var.second->operator[]("value")->to_string(), versionData, path, options)));
                    arglist = StrDogW(arglist, L" ");
                }
                // Sometimes var["value"] is a list of arguments
                else
                {
                    for (auto& v : var.second->operator[]("value")->get_value())
                    {
                        wchar_t* val = v.second->to_stringW();
                        val = Additionals::Convectors::ConvertStringToWcharPtr(replace_arguments(v.second->to_string(), versionData, path, options));
                        arglist = StrDogW(arglist, val);
                        arglist = StrDogW(arglist, L" ");
                    }
                }
            }
        }
    }
    return arglist;
}

wchar_t* MinecraftCpp::get_arguments_string(Json::JsonValue* versionData, wchar_t* path, MinecraftCpp::option::MinecraftOptions options)
{
    /*
    Turns the argument string from the version.json into a list
    */
    wchar_t* arglist = NULL;
    
    for (auto& var : Additionals::String::split((*versionData)["minecraftArguments"]->to_string(), ' '))
    {
        var = replace_arguments(var, versionData, path, options);
        arglist = StrDogWA(arglist, var.c_str());
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

bool MinecraftCpp::forge::install_forge_version(wchar_t* versionid, wchar_t* path, CallbackNull callback, wchar_t* java)
{
    /*
    Installs a forge version. Fore more information look at the documentation.
    */

    int random_num = 1 + (rand() % 100000);

    wchar_t* FORGE_DOWNLOAD_URL = StrDogW({ L"https://files.minecraftforge.net/maven/net/minecraftforge/forge/", versionid, L"/forge-", versionid, L"-installer.jar" });
    wchar_t* temp_file_path = StrDogW({ Additionals::TempFile::get_tempdir_SYSTEM(), StrDogW({L"forge-installer-", std::to_wstring(random_num).c_str(), L".tmp"})});
    if (DownloadFile(FORGE_DOWNLOAD_URL, temp_file_path, callback) == nullptr)
    {
        std::cout << "Version Not Found" << versionid << std::endl;
        return false;
    }
    Additionals::ziparchives::ZipArchive zArchive(temp_file_path);

    // Read the install_profile.json
    Json::JsonParcer json_parcer;
    Json::JsonValue* version_data;

    for (auto& var : zArchive.entries)
    {
        if (var.filesystemFileName() == "install_profile.json")
        {
            qint64 fileSize;
            QString fileName;

            var.Open();
            QDataStream data_stream;

            data_stream.setDevice(&var);
            data_stream.setVersion(QDataStream::Qt_6_5);

            // Читаем размер файла и его имя.
            data_stream >> fileSize;
            data_stream >> fileName;

            char* buffer = new char[fileSize];

            // Читаем содержимое файла.
            data_stream.readRawData(buffer, fileSize);

            std::string json_str = buffer;

            version_data = json_parcer.ParseJson(json_str);

            var.close();
            break;
        }
    }

    wchar_t* forge_version_id = (*version_data)["version"]->to_stringW();

    // Make sure, the base version is installed
    install_minecraft_version((*version_data)["minecraft"]->to_stringW(), path, callback);

    // Install all needed libs from install_profile.json
    install_libraries(version_data, path, callback);

    // Extract the version.json
    wchar_t* version_json_path = JoinW({ path, L"versions", forge_version_id, StrDogW(forge_version_id, L".json") });
    extract_file(zArchive, L"version.json", version_json_path);

    // Extract forge libs from the installer
    wchar_t* forge_lib_path = JoinW({ path, L"libraries", L"net", L"minecraftforge", L"forge", versionid });
    extract_file(zArchive, StrDogW({ L"maven/net/minecraftforge/forge/", versionid, L"/forge-", versionid, L".jar" }), JoinW({ forge_lib_path, StrDogW({L"forge-", versionid, L".jar"}) }));
    extract_file(zArchive, StrDogW({ L"maven/net/minecraftforge/forge/", versionid, L"/forge-", versionid, L"-universal.jar" }), JoinW({ forge_lib_path, StrDogW({L"forge-", versionid, L"-universal.jar"}) }));

    // Extract the client.lzma
    wchar_t* lzma_path = StrDogW({ Additionals::TempFile::get_tempdir_SYSTEM(), StrDogW({ L"lzma-", std::wstring(std::to_wstring(random_num)).c_str(), L".tmp" }) });

    extract_file(zArchive, L"data/client.lzma", lzma_path);
    
    // Install the rest with the vanilla function
    install_minecraft_version(forge_version_id, path, callback);

    // Run the processors
    forge_processors(version_data, path, lzma_path, temp_file_path, callback, java);

    zArchive.Close();

    // Delete the temporary files
    std::filesystem::remove(temp_file_path);
    if (std::filesystem::exists(lzma_path) && !std::filesystem::is_directory(lzma_path))
    {
        std::filesystem::remove(lzma_path);
    }


    return true;
}

bool MinecraftCpp::forge::extract_file(Additionals::ziparchives::ZipArchive handler, const wchar_t* zip_path, const wchar_t* extract_path)
{
    /*
    Extract a file from a zip handler into the given path
    */
    std::filesystem::path p = extract_path;
    std::filesystem::path dir = p.parent_path();
    DWORD attrib = GetFileAttributesW(dir.wstring().c_str());
    if (attrib == INVALID_FILE_ATTRIBUTES || !(attrib & FILE_ATTRIBUTE_DIRECTORY))
    {
        if (!CreateDirectoryW(dir.wstring().c_str(), NULL))
        {
            // Обработка ошибки создания директории
            int error = GetLastError();
            //System::Console::WriteLine(error);
        }
    }
    for (auto& var : handler.entries)
    {
        if (var.filesystemFileName() == zip_path)
        {
            Additionals::ziparchives::ZipArchive::ExtractFile(var, p.string());
            break;
        }
    }

    return true;
}

std::string MinecraftCpp::forge::get_data_library_path(wchar_t* libname, wchar_t* path)
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
    std::wstring base_path = Additionals::String::split(libname,':')[0];
    std::wstring libname_str = Additionals::String::split(libname, ':')[1];
    std::wstring version = Additionals::String::split(libname, ':')[2];
    std::wstring extra = Additionals::String::split(libname, ':')[3];
    std::wstring fileend;

    for (auto& var : Additionals::String::split(base_path, '.'))
    {
        libpath = JoinW({ libpath, var.c_str()});

        if (Additionals::String::split(extra, '@')[0] == extra)
        {
            fileend = L"jar";
        }
        else
        {
            extra = Additionals::String::split(extra, '@')[0];
            fileend = Additionals::String::split(extra, '@')[1];
        }
    }



    libpath = JoinW({ libpath, libname, version.c_str(), StrDogW({libname, L"-", version.c_str(), L"-", extra.c_str(), L".", fileend.c_str()})});
    return Additionals::Convectors::ConvertWcharPtrToString(libpath);
}

wchar_t* MinecraftCpp::forge::get_jar_mainclass(wchar_t* path)
{
    /*
    Returns the mainclass of a given jar
    */
    Additionals::ziparchives::ZipArchive zArchive(path);

    // Parse the MANIFEST.MF
    for (auto& var : zArchive.entries)
    {

    }
    std::cout << "get_jar_mainclass is not done blyat" << std::endl;

    return nullptr;
}

bool MinecraftCpp::forge::forge_processors(
    Json::JsonValue* data,
    wchar_t* minecraft_directory,
    wchar_t* lzma_path,
    wchar_t* installer_path,
    CallbackNull callback,
    wchar_t* java = nullptr)
{
    /*
    Run the processors of the install_profile.json
    */
    int random_num = 1 + (rand() % 100000);
    wchar_t* path = minecraft_directory;

    Json::JsonValue* argument_vars = new Json::JsonObject();
    Json::JsonValue* value_ = new Json::JsonString(std::wstring(JoinW({ path, L"versions", (*data)["minecraft"]->to_stringW(), StrDogW((*data)["minecraft"]->to_stringW(), L".jar") })));
    argument_vars->add_value("{MINECRAFT_JAR}", value_);

    for (auto& var : (*data)["data"]->get_value())
    {
        if (var.second->get_value("client")->to_string()._Starts_with("[") && Additionals::String::EndsWith(var.second->get_value("client")->to_string(), "]"))
        {
            (*argument_vars)["{" + var.first + "}"]->operator=(get_data_library_path(var.second->get_value("client")->to_stringW(), path));
        }
        else
        {
            (*argument_vars)["{" + var.first + "}"]->operator=(var.second->get_value("client"));
        }
    }
    wchar_t* root_path = JoinW({ Additionals::TempFile::get_tempdir_SYSTEM(), StrDogW(L"forge-root-", std::to_wstring(random_num).c_str()) });

    (*argument_vars)["{INSTALLER}"]->operator=(std::wstring(installer_path));
    (*argument_vars)["{BINPATCH}"]->operator=(std::wstring(lzma_path));
    (*argument_vars)["{ROOT}"]->operator=(std::wstring(root_path));
    (*argument_vars)["{SIDE}"]->operator=("client");

    std::wstring classpath_seperator = nullptr;
    if (std::wstring(OS) == std::wstring(L"Windows"))
    {
        classpath_seperator = L";";
    }
    else
    {
        classpath_seperator = L":";
    }

    //callback.get("setMax", empty)(len(data["processors"]))
    callback.OnProgress(NULL, (*data)["processors"]->to_int(), NULL, NULL);

    int count = -1;
    for (auto var : (*data)["processors"]->get_value_list())
    {
        ++count;

        if (!((*var)["sides"]->is_exist("client")) || !((*var)["sides"] == var ? true : false))
        {
            // Skip server side only processors
            continue;
        }
        callback.OnProgress(NULL, NULL, NULL, StrDogW(L"Running processor ", (*var)["jar"]->to_stringW()));

        // Get the classpath
        std::wstring classpath = L"";
        for (auto var2 : (*var)["classpath"]->get_value_list())
        {
            classpath = StrDogW({ classpath.c_str(), get_library_path(var2->to_stringW(), path), classpath_seperator.c_str()});
        }

        classpath = StrDogW(classpath.c_str(), get_library_path((*var)["jar"]->to_stringW(), path));
        wchar_t* mainclass = get_jar_mainclass(get_library_path((*var)["jar"]->to_stringW(), path));
        std::vector<std::wstring> command;
        command[0] = java == nullptr || std::wstring(java) == std::wstring(L"") ? std::wstring(L"java") : std::wstring(java) + L"-cp", classpath, mainclass;

        wchar_t* variable = NULL;
        for (auto var2 : (*var)["args"]->get_value_list())
        {
            variable = (*argument_vars)[var2->to_string()] == nullptr ? var2->to_stringW() : (*argument_vars)[var2->to_string()]->to_stringW();
            if (std::wstring(variable)._Starts_with(L"[") && Additionals::String::EndsWith(variable, L"]"))
            {
                command.push_back(get_library_path(variable, path));
            }
            else
            {
                command.push_back(variable);
            }
        }

        for (auto& var2 : argument_vars->get_value())
        {
            for (size_t i = 0; i < command.size(); i++)
            {
                std::replace(command.begin(), command.end(), Additionals::Convectors::ConvertStringToWcharPtr(var2.first), var2.second->to_stringW());
                //command[i] = command[i].insert(var2.first, var2.second->to_string());
            }
        }

        wchar_t* commant_strw = NULL;
        for (size_t i = 0; i < command.size(); i++)
        {
            commant_strw = StrDogW(commant_strw, command[i].c_str());
        }

        int out = _wsystem(commant_strw);

        callback.OnProgress(count, NULL, NULL, NULL);
    }
    if (std::filesystem::exists(root_path))
    {
        std::filesystem::remove(root_path);
    }

    return true;
}

bool MinecraftCpp::modpacks::install_mod_pack(wchar_t* versionid, wchar_t* path, CallbackNull callback)
{

    return false;
}
