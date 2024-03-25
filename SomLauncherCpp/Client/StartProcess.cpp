#include "StartProcess.h"

int client::startProcess(const std::string& args)
{
	std::unique_ptr<wchar_t[]> buffer = Additionals::Convectors::ConvertStringToWcharUniqPtr(args);

	return utils::doProcess(buffer, std::filesystem::path("somlogs") / "last_minecraft_log.txt", ".");
}

int client::startProcess(const std::vector<std::string>& args)
{
	std::ostringstream imploded;
	std::copy(args.begin(), args.end(),
		std::ostream_iterator<std::string>(imploded, " "));

	std::unique_ptr<wchar_t[]> buffer = Additionals::Convectors::ConvertStringToWcharUniqPtr(imploded.str());

	return utils::doProcess(buffer, std::filesystem::path("somlogs") / "last_minecraft_log.txt", ".");
}

int client::startProcess(const std::vector<std::wstring>& args)
{
	std::wstring imploded;
	for (std::vector<std::wstring>::const_iterator ii = args.begin(); ii != args.end(); ++ii)
	{
		imploded += (*ii);
		if (ii + 1 != args.end())
		{
			imploded += L" ";
		}
	}
	std::unique_ptr<wchar_t[]> ch_array = std::make_unique<wchar_t[]>(imploded.size() + 1);
	wcsncpy(ch_array.get(), imploded.c_str(), imploded.size());

	return utils::doProcess(ch_array, std::filesystem::path("somlogs") / "last_minecraft_log.txt", ".");
}

int client::startProcess(const std::vector<std::wstring>& args, const std::filesystem::path& output_file)
{
	std::wstring imploded;
	for (std::vector<std::wstring>::const_iterator ii = args.begin(); ii != args.end(); ++ii)
	{
		imploded += (*ii);
		if (ii + 1 != args.end())
		{
			imploded += L" ";
		}
	}
	std::unique_ptr<wchar_t[]> ch_array = std::make_unique<wchar_t[]>(imploded.size() + 1);
	wcsncpy(ch_array.get(), imploded.c_str(), imploded.size());

	return utils::doProcess(ch_array, output_file, ".");
}

int client::startProcess(std::vector<std::variant<std::string, std::filesystem::path, std::wstring>>& args, std::filesystem::path instance_path)
{
	std::variant<std::string> a;

	std::wstring imploded;
	for (auto& ii : args)
	{
		try
		{
			imploded += std::get<std::wstring>(ii);
		}
		catch (const std::bad_variant_access& ex)
		{
			try
			{
				imploded += L"\"" + std::get<std::filesystem::path>(ii).wstring() + L"\"";
			}
			catch (const std::bad_variant_access& ex)
			{
				try
				{
					imploded += Additionals::Convectors::ConvertStringToWString(std::get<std::string>(ii));
				}
				catch (const std::bad_variant_access& ex)
				{
					qWarning() << ex.what() << '\n';
				}
			}
		}

		imploded += L" ";
	}
	std::unique_ptr<wchar_t[]> ch_array = std::make_unique<wchar_t[]>(imploded.size() + 1);
	wcsncpy(ch_array.get(), imploded.c_str(), imploded.size());

	qInfo() << "Command:" << imploded << std::endl;

	return utils::doProcess(ch_array, std::filesystem::path("somlogs") / "last_minecraft_log.txt", instance_path);
}

int client::utils::doProcess(std::unique_ptr<wchar_t[]>& buffer, const std::filesystem::path& output_file, std::filesystem::path workdir_path)
{
	SECURITY_ATTRIBUTES sa{};
	sa.nLength = sizeof(sa);
	sa.lpSecurityDescriptor = NULL;
	sa.bInheritHandle = TRUE;

	HANDLE h = CreateFileW(output_file.wstring().c_str(),
		GENERIC_WRITE, 0, &sa, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);

	if (h == INVALID_HANDLE_VALUE)
	{
		qWarning() << "error create log file:" << output_file.wstring() << std::endl;
	}

	PROCESS_INFORMATION pi;
	STARTUPINFOW si;

	ZeroMemory(&si, sizeof(STARTUPINFO));
	memset(&pi, 0, sizeof(pi));

	si.cb = sizeof(STARTUPINFOW);
	si.hStdError = h; // Перенаправляем стандартный поток ошибок в файл
	si.hStdOutput = h; // Перенаправляем стандартный поток вывода в файл
	si.hStdInput = h;
	si.dwFlags |= STARTF_USESTDHANDLES; // Устанавливаем флаг, чтобы использовать перенаправление потоко

	//STARTUPINFO si;
	////memset(&si, 0, sizeof(si));
	//ZeroMemory(&si, sizeof(STARTUPINFO));
	//si.cb = sizeof(si);

	//DWORD flags = CREATE_NO_WINDOW;

	//si.dwFlags = STARTF_USESTDHANDLES;
	////si.hStdInput = h;
	//si.hStdError = h;
	//si.hStdOutput = h;

	//PROCESS_INFORMATION pi;
	//memset(&pi, 0, sizeof(pi));

	auto work_dir = std::filesystem::current_path();
	std::filesystem::current_path(workdir_path);

	qInfo() << "Programm args setting complete" << std::endl;
	if (CreateProcessW(NULL, buffer.get(), NULL, NULL, TRUE, NULL, NULL, NULL, &si, &pi))
	{
		// программа запущена, ждем её завершения
		qInfo() << "Programm has been started" << std::endl;
		DWORD dwWait = WaitForSingleObject(pi.hProcess, INFINITE);
		if (dwWait == WAIT_OBJECT_0)
		{
			qInfo() << "Programm has been closed" << std::endl;
			std::filesystem::current_path(work_dir);

			WaitForSingleObject(pi.hProcess, INFINITE);
			CloseHandle(pi.hProcess);
			CloseHandle(pi.hThread);
			CloseHandle(h);
			return 0;
		}
		else if (dwWait == WAIT_ABANDONED)
		{
			qInfo() << "Programm has been adadonde" << std::endl;
			std::filesystem::current_path(work_dir);

			WaitForSingleObject(pi.hProcess, INFINITE);
			CloseHandle(pi.hProcess);
			CloseHandle(pi.hThread);
			CloseHandle(h);
			return 1;
		}
		//  else ну и может быть другие варианты ожидания

		std::filesystem::current_path(work_dir);

		WaitForSingleObject(pi.hProcess, INFINITE);
		CloseHandle(pi.hProcess);
		CloseHandle(pi.hThread);
	}
	else
	{
		qWarning() << "Programm isnt starting" << std::endl;
	}
	std::filesystem::current_path(work_dir);
	CloseHandle(h);
	return -1;
}
