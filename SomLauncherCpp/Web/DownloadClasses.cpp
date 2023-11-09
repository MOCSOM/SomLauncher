#include "DownloadClasses.h"

//bool DDIC::Download::Files::_CreateDirectoryIfNotExists(const std::wstring& path)
//{
//    if (!std::filesystem::exists(path))
//    {
//        return std::filesystem::create_directory(path);
//    }
//    return true;
//}

inline std::string DDIC::Download::Files::download_file(const std::string& s_url,
	const std::string& d_file, CallbackNull* callback, const std::string& sha1, bool lzma_compressed)
{
	//callback = const_cast<CallbackNull>(callback);
	std::string destenation_file;

	if (d_file == "")
	{
		destenation_file = "";
	}
	else
	{
		destenation_file = d_file;
	}
	if (d_file == "")
	{
		std::string url = s_url;
		int count = -1;
		for (auto& var : Additionals::String::split(url, '/'))
		{
			++count;
		}
		url = Additionals::String::split(url, '/')[count];
		destenation_file = url;
	}

	std::filesystem::path d_file_path(destenation_file);
	d_file_path = d_file_path.parent_path();

	if (d_file_path != "")
	{
		if (!std::filesystem::create_directories(d_file_path))
		{
			// Обработка ошибки создания директории
			int error = GetLastError();
		}
	}

	if (d_file != "")
	{
		if (std::filesystem::exists(d_file) && std::filesystem::is_directory(d_file))
		{
			std::string url = s_url;
			int count = -1;
			for (auto& var : Additionals::String::split(url, '/'))
			{
				++count;
			}
			url = Additionals::String::split(url, '/')[count];

			std::string ff = d_file;
			destenation_file = ff + "\\" + url;
		}
	}

	if (std::filesystem::is_regular_file(destenation_file))
	{
		if (sha1 == "")
		{
			return destenation_file;
		}
		callback->OnProgress(NULL, NULL, 6, Additionals::Convectors::ConvertStringToWString("Checking checksum " + destenation_file).c_str());
		if (SHA1::from_file(destenation_file) == sha1)
		{
			return destenation_file;
		}
	}

	HRESULT download_result = URLDownloadToFileA(NULL, s_url.c_str(), destenation_file.c_str(), NULL, callback);

	if (lzma_compressed)
	{
		/*System::IO::Compression::ZipArchive^ zArchive = System::IO::Compression::ZipFile::OpenRead(System::String(d_file).ToString());
		System::IO::Compression::ZipFileExtensions::ExtractToDirectory(zArchive, System::String(d_file).ToString());*/
	}

	if (sha1 != "")
	{
		std::string check_sum = SHA1::from_file(destenation_file);
		if (check_sum != sha1)
		{
			callback->OnProgress(NULL, NULL, NULL, Additionals::Convectors::ConvertStringToWString(
				"Invalid checksum " +
				s_url + " in " +
				destenation_file + " with " +
				sha1 + " checksum " + check_sum).c_str());

			/*throw std::runtime_error("Invalid checksum " +
				s_url + " in " +
				destenation_file + " with " +
				sha1 + " checksum " + check_sum);*/
		}
	}

	if (S_OK == download_result)
	{
		callback->OnProgress(NULL, NULL, NULL, Additionals::Convectors::ConvertStringToWString("The file is saved as: " + d_file).c_str());
		return destenation_file;
	}
	else
	{
		callback->OnProgress(NULL, NULL, NULL, Additionals::Convectors::ConvertStringToWString("Unable to Download the file: " + s_url).c_str());
		callback->OnProgress(NULL, NULL, NULL, Additionals::Convectors::ConvertStringToWString("to: " + d_file).c_str());
		return "";
	}
}

//wchar_t* DDIC::DownloadDeleteClass::download_file(wchar_t* s_url, CallbackDict callback)
//{
//    wchar_t* d_file = NULL;
//
//    if (S_OK == URLDownloadToFileW(NULL, s_url, d_file, NULL, &callback)) {
//        System::Console::Write("The file is saved as: ");
//        System::Console::WriteLine(System::String(d_file).ToString());
//        return d_file;
//    }
//    else {
//        System::Console::Write("Unable to Download the file: ");
//        System::Console::WriteLine(System::String(s_url).ToString());
//        return d_file;
//    }
//}

int DDIC::Download::Files::_get_java_exist_ver(const std::string& direct)
{
	std::vector<std::string> dirs = Additionals::Path::get_directories(direct);
	for (std::string var : dirs)
	{
		int count = -1;
		for (auto& var2 : Additionals::String::split(var, '\\'))
		{
			++count;
		}
		if (Additionals::String::split(var, '\\')[count]._Starts_with("jdk"))
		{
			if (Additionals::String::split(var, '\\')[count]._Starts_with("jdk8"))
			{
				return 8;
			}
			return 1;
		}
	}
	return 0;
}

std::vector<std::pair<std::string, std::string>> DDIC::Download::Files::_get_java_path(const std::string& dir)
{
	if (!std::filesystem::exists(dir))
	{
		return std::vector<std::pair<std::string, std::string>>();
	}
	std::vector<std::string> dirs = Additionals::Path::get_directories(dir);
	std::vector<std::pair<std::string, std::string>> return_vector;
	for (std::string var : dirs)
	{
		int count = -1;
		for (auto& var2 : Additionals::String::split(var, '\\'))
		{
			++count;
		}
		if (Additionals::String::split(var, '\\')[count].find("jdk") == 0)
		{
			if (Additionals::String::split(var, '\\')[count].find("jdk8") == 0)
			{
				return_vector.push_back(std::make_pair(var, "8"));
			}
			if (Additionals::String::split(var, '\\')[count].find("jdk-17") == 0)
			{
				return_vector.push_back(std::make_pair(var, "17"));
			}
		}
	}
	//return_vector.push_back(std::make_pair("", ""));
	return return_vector;
}

std::string DDIC::Download::Files::getInstalledJavaInDirectory(std::string directory_path, int version)
{
	if (directory_path == "" && version == 0)
	{
		char* program_files = nullptr;
		size_t program_files_sz = 0;
		_dupenv_s(&program_files, &program_files_sz, "ProgramFiles");

		std::vector<std::pair<std::string, std::string>> result_version = DDIC::Download::Files::_get_java_path(std::string(program_files == nullptr ? "" : program_files) + '\\' + "java");

		if (result_version.size() == 0)
		{
			return std::string();
		}

		return "\"" + result_version[0].first + "\\" + "bin" + "\\" + "java.exe" + "\"";
	}

	for (std::pair<std::string, std::string> path_version : _get_java_path(directory_path))
	{
		if (version == 0)
		{
			return path_version.first;
		}
		if (path_version.second == std::to_string(version))
		{
			return path_version.first;
		}
	}

	return std::string();
}

std::string DDIC::Download::Java::install(const std::string& version, const std::string& path, CallbackNull* callback, const std::string& operating_system, const std::string& arch, const std::string& impl, bool jre)
{
	std::string url = get_download_url(version, operating_system, arch, impl, jre);

	std::string path2 = path;
	if (path == "")
	{
		if (jre)
		{
			path2 = _JRE_DIR;
		}
		else
		{
			path2 = _JDK_DIR;
		}
	}

	std::string path_wch = path2 + "\\.zip";
	std::string path_wch_norm = path2;

	std::string jdk_file2 = "";

	jdk_file2 = DownloadFile(url, path_wch, callback);

	std::string jdk_file = jdk_file2;

	if (jdk_file == "")
	{
		//return _wcsdup(L"error 105: file not download");
		return "";
	}
	std::string jdk_ext = _get_normalized_compressed_file_ext(jdk_file);
	std::string jdk_dir = _decompress_archive(jdk_file, jdk_ext, path_wch_norm);

	if (jdk_file != "")
	{
		std::string fifa;
		for (size_t i = 0; jdk_file[i] != L'\0'; ++i)
		{
			fifa += jdk_file[i];
		}
		bool del = DeleteFileA(fifa.c_str());

		callback->OnProgress(NULL, NULL, NULL, (L"Deleted archive status: " + std::to_wstring(del)).c_str());
	}
	/*System::Console::WriteLine("Installation of java completed");*/

	callback->OnProgress(NULL, NULL, NULL, L"Installation of java completed");

	return jdk_dir;
}

std::string DDIC::Download::Java::get_download_url(/*wchar_t*& url,*/const std::string& version, const std::string& operating_system, const std::string& arch, const std::string& impl, bool jre)
{
	std::string _version = version;
	_version = normalize_version(version);
	if (jre) {
		//L"https://api.adoptopenjdk.net/v3/binary/latest/"

		/*wchar_t* url = L"https://api.adoptopenjdk.net/v3/binary/latest/";

		url = strdogW(url, version);
		url = strdogW(url, L"/ga/");
		url = strdogW(url, operating_system);
		url = strdogW(url, L"/");
		url = strdogW(url, arch);
		url = strdogW(url, L"/jre/");
		url = strdogW(url, impl);
		url = strdogW(url, L"/normal/adoptopenjdk");*/

		std::string url = Join({
			"https://api.adoptopenjdk.net/v3/binary/latest/",
			_version,
			"ga",
			operating_system,
			arch,
			"jre",
			impl,
			"normal/adoptopenjdk " });

		return url;
		//L"https://api.adoptopenjdk.net/v3/binary/latest/%s/ga/%s/%s/jre/%s/normal/adoptopenjdk", version, operating_system, arch, impl;
	}
	else {
		/*wchar_t* url = L"https://api.adoptopenjdk.net/v3/binary/latest/";

		url = strdogW(url, version);
		url = strdogW(url, L"/ga/");
		url = strdogW(url, operating_system);
		url = strdogW(url, L"/");
		url = strdogW(url, arch);
		url = strdogW(url, L"/jdk/");
		url = strdogW(url, impl);
		url = strdogW(url, L"/normal/adoptopenjdk");*/

		std::string url = Join({
			"https://api.adoptopenjdk.net/v3/binary/latest/",
			_version,
			"ga",
			operating_system,
			arch,
			"jdk",
			impl,
			"normal/adoptopenjdk " });

		return url;
	}
}

std::string DDIC::Download::Java::_decompress_archive(const std::string& repo_root, const std::string& file_ending, const std::string& destination_folder)
{
	//WIN32_FIND_DATA ffd;

	std::string destination_str;
	destination_str = destination_folder;
	std::string destination_str_cstr = destination_str;

	std::string repo_root_str;
	repo_root_str = repo_root;

	if (!std::filesystem::exists(destination_str)) {
		bool out_mkdir = std::filesystem::create_directories(destination_str_cstr);
		/*System::Console::Write("java dir is maked with status: ");
		System::Console::WriteLine(out_mkdir);*/

		std::cout << "java dir is maked with status: " << out_mkdir << std::endl;
	}

	std::string jdk_file = repo_root_str;

	if (std::filesystem::is_directory(jdk_file))
	{
		if (std::filesystem::exists(destination_str))
		{
			return destination_folder; //TODO переписывание архива
		}

		/*System::IO::Compression::ZipArchive^ zArchive = System::IO::Compression::ZipFile::OpenRead(repo_root_str);
		System::IO::Compression::ZipFileExtensions::ExtractToDirectory(zArchive, destination_str);*/

		/*jdk_directory = _extract_files(jdk_file, file_ending, destination_folder);
		jdk_bin = path.join(jdk_directory, "bin");
		_unpack_jars(jdk_directory, jdk_bin);*/

		return destination_folder;
	}
	else
	{
		if (std::filesystem::exists(destination_str))
		{
			QZipReader zip(jdk_file.c_str());
			return Additionals::archives::decompressArchive(zip, destination_str);
		}
	}
	return repo_root;
}

bool DDIC::Download::Java::check_system_verison_java(const std::string& java)
{
	char* program_files = nullptr;
	size_t program_files_sz = 0;
	_dupenv_s(&program_files, &program_files_sz, "ProgramFiles");

	return check_downloaded_version_java(std::string(program_files == nullptr ? "" : program_files) + '\\' + "java", java);
}

bool DDIC::Download::Java::check_downloaded_version_java(const std::string& path, const std::string& java)
{
	std::string java_path = "";
	for (auto& var : DDIC::Download::Files::_get_java_path(path))
	{
		if (var.second == java)
		{
			java_path = var.first + "\\" + "bin" + "\\" + "java.exe";
		}
	}

	if (std::filesystem::exists(java_path))
	{
		return true;
	}
	return false;
}

std::string DDIC::Download::Java::_get_normalized_compressed_file_ext(const std::string& file)
{
	std::string file_str;
	file_str = file;

	if (file_str.find(_TAR)) {
		return _TAR;
	}
	else if (file_str.find(_TAR_GZ)) {
		return _TAR_GZ;
	}
	else if (file_str.find(_ZIP)) {
		return _ZIP;
	}
	else {
		return _SEVEN_ZIP;
	}
}

std::string DDIC::Download::Java::normalize_version(const std::string& version)
{
	if (version == "1.8") {
		return "8";
	}
	return version;
}

std::string DDIC::Download::Java::expand_user(std::string path)
{
	if (!path.empty() && path[0] == '~')
	{
		//assert(path.size() == 1 || path[1] == '/');  // or other error handling
		//_dupenv_s(,"HOME")

		char* home = nullptr;
		size_t home_sz = 0;

		_dupenv_s(&home, &home_sz, "HOME");

		//home.compare(profile)
		if (home || (_dupenv_s(&home, &home_sz, "USERPROFILE")) && home != 0)
		{
			Additionals::String::replace(path, path, std::string(home));
		}
		else
		{
			size_t hdrive_sz = 0;
			size_t hpath_sz = 0;
			char* hdrive;
			char* hpath;

			_dupenv_s(&hdrive, &hdrive_sz, "HOMEDRIVE");
			_dupenv_s(&hpath, &hpath_sz, "HOMEPATH");

			//assert(hdrive);  // or other error handling
			//assert(hpath);

			Additionals::String::replace(path, path, (hdrive == 0 ? "" : std::string(hdrive)) + (hpath == 0 ? "" : std::string(hpath)));
		}
	}
	return path;
}

//std::string DDIC::JavaDownload::expand_user(std::string path) {
//    if (! path.empty() && path[0] == '~') {
//        //assert(path.size() == 1 || path[1] == '/');  // or other error handling
//        char const* home = getenv("HOME");
//        if (home || ((home = getenv("USERPROFILE")))) {
//            path.replace(0, 1, home);
//        }
//        else {
//            char const* hdrive = getenv("HOMEDRIVE"),
//                * hpath = getenv("HOMEPATH");
//            //assert(hdrive);  // or other error handling
//            //assert(hpath);
//            path.replace(0, 1, std::string(hdrive) + hpath);
//        }
//    }
//    return path;
//}