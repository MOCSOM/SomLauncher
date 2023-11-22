#include "StartProcess.h"

int client::startProcess(const std::string& args)
{
	std::unique_ptr<wchar_t[]> buffer = Additionals::Convectors::ConvertStringToWcharUniqPtr(args);

	STARTUPINFO si;
	memset(&si, 0, sizeof(si));
	si.cb = sizeof(si);
	PROCESS_INFORMATION pi;
	memset(&pi, 0, sizeof(pi));
	qInfo() << "Programm args setting complete" << std::endl;
	if (CreateProcessW(NULL, buffer.get(), NULL, NULL, FALSE, 0, NULL, NULL, &si, &pi))
	{
		// программа запущена, ждем её завершения
		qInfo() << "Programm has been started" << std::endl;
		DWORD dwWait = WaitForSingleObject(pi.hProcess, INFINITE);
		if (dwWait == WAIT_OBJECT_0)
		{
			qInfo() << "Programm has been closed" << std::endl;
			return 0;
		}
		else if (dwWait == WAIT_ABANDONED)
		{
			qInfo() << "Programm has been adadonde" << std::endl;
			return 1;
		}
		//  else ну и может быть другие варианты ожидания

		CloseHandle(pi.hProcess);
		CloseHandle(pi.hThread);
	}
	else
	{
		qWarning() << "Programm isnt starting" << std::endl;
	}

	return -1;
}

int client::startProcess(const std::vector<std::string>& args)
{
	HANDLE g_hChildStd_IN_Rd = NULL;
	HANDLE g_hChildStd_IN_Wd = NULL;
	HANDLE g_hChildStd_OUT_Rd = NULL;
	HANDLE g_hChildStd_OUT_Wd = NULL;

	SECURITY_ATTRIBUTES atributes = {};
	memset(&atributes, 0, sizeof(SECURITY_ATTRIBUTES));
	atributes.nLength = sizeof(atributes);
	atributes.lpSecurityDescriptor = NULL; // Дескриптор безопасности по умолчанию.
	atributes.bInheritHandle = TRUE; // Наследовать данный хэндл.

	CreatePipe(&g_hChildStd_OUT_Rd, &g_hChildStd_OUT_Wd, &atributes, 0);
	SetHandleInformation(g_hChildStd_OUT_Rd, HANDLE_FLAG_INHERIT, 0);

	CreatePipe(&g_hChildStd_IN_Rd, &g_hChildStd_IN_Wd, &atributes, 0);
	SetHandleInformation(g_hChildStd_IN_Rd, HANDLE_FLAG_INHERIT, 0);

	g_hChildStd_OUT_Wd = GetStdHandle(STD_OUTPUT_HANDLE);
	g_hChildStd_IN_Rd = GetStdHandle(STD_INPUT_HANDLE);

	std::ostringstream imploded;
	std::copy(args.begin(), args.end(),
		std::ostream_iterator<std::string>(imploded, " "));

	std::unique_ptr<wchar_t[]> buffer = Additionals::Convectors::ConvertStringToWcharUniqPtr(imploded.str());

	STARTUPINFO si;
	memset(&si, 0, sizeof(si));
	si.cb = sizeof(si);
	si.hStdError = g_hChildStd_OUT_Wd;
	si.hStdOutput = g_hChildStd_OUT_Wd;
	si.hStdInput = g_hChildStd_IN_Rd;
	si.dwFlags |= STARTF_USESTDHANDLES;

	PROCESS_INFORMATION pi;
	memset(&pi, 0, sizeof(pi));

	qInfo() << "Programm args setting complete" << std::endl;
	if (CreateProcessW(NULL, buffer.get(), &atributes, NULL, TRUE, 0, NULL, NULL, &si, &pi))
	{
		// программа запущена, ждем её завершения
		qInfo() << "Programm has been started" << std::endl;
		DWORD dwWait = WaitForSingleObject(pi.hProcess, INFINITE);
		if (dwWait == WAIT_OBJECT_0)
		{
			qInfo() << "Programm has been closed" << std::endl;
			return 0;
		}
		else if (dwWait == WAIT_ABANDONED)
		{
			qInfo() << "Programm has been adadonde" << std::endl;
			return 1;
		}
		//  else ну и может быть другие варианты ожидания

		CloseHandle(pi.hProcess);
		CloseHandle(pi.hThread);
	}
	else
	{
		qWarning() << "Programm isnt starting" << std::endl;
	}

	return -1;
}