#include "StartProcess.h"

int client::startProcess(const std::string& args)
{
	std::unique_ptr<wchar_t[]> buffer = Additionals::Convectors::ConvertStringToWcharUniqPtr(args);

	return utils::doProcess(buffer);
}

int client::startProcess(const std::vector<std::string>& args)
{
	std::ostringstream imploded;
	std::copy(args.begin(), args.end(),
		std::ostream_iterator<std::string>(imploded, " "));

	std::unique_ptr<wchar_t[]> buffer = Additionals::Convectors::ConvertStringToWcharUniqPtr(imploded.str());

	return utils::doProcess(buffer);
}

int client::utils::doProcess(std::unique_ptr<wchar_t[]>& buffer)
{
	SECURITY_ATTRIBUTES sa{};
	sa.nLength = sizeof(sa);
	sa.lpSecurityDescriptor = NULL;
	sa.bInheritHandle = TRUE;

	HANDLE h = CreateFile(L"somlogs\\last_minecraft_out.log",
		FILE_APPEND_DATA,
		FILE_SHARE_WRITE | FILE_SHARE_READ,
		&sa,
		OPEN_ALWAYS,
		FILE_ATTRIBUTE_NORMAL,
		NULL);


	STARTUPINFO si;
	//memset(&si, 0, sizeof(si));
	ZeroMemory(&si, sizeof(STARTUPINFO));
	si.cb = sizeof(si);

	DWORD flags = CREATE_NO_WINDOW;

	si.dwFlags = STARTF_USESTDHANDLES;
	//si.hStdInput = h;
	si.hStdError = h;
	si.hStdOutput = h;

	PROCESS_INFORMATION pi;
	memset(&pi, 0, sizeof(pi));

	qInfo() << "Programm args setting complete" << std::endl;
	if (CreateProcessW(NULL, buffer.get(), NULL, NULL, TRUE, flags, NULL, NULL, &si, &pi))
	{
		// ��������� ��������, ���� � ����������
		qInfo() << "Programm has been started" << std::endl;
		DWORD dwWait = WaitForSingleObject(pi.hProcess, INFINITE);
		if (dwWait == WAIT_OBJECT_0)
		{
			qInfo() << "Programm has been closed" << std::endl;
			WaitForSingleObject(pi.hProcess, INFINITE);
			CloseHandle(pi.hProcess);
			CloseHandle(pi.hThread);
			CloseHandle(h);
			return 0;
		}
		else if (dwWait == WAIT_ABANDONED)
		{
			qInfo() << "Programm has been adadonde" << std::endl;
			WaitForSingleObject(pi.hProcess, INFINITE);
			CloseHandle(pi.hProcess);
			CloseHandle(pi.hThread);
			CloseHandle(h);
			return 1;
		}
		//  else �� � ����� ���� ������ �������� ��������

		WaitForSingleObject(pi.hProcess, INFINITE);
		CloseHandle(pi.hProcess);
		CloseHandle(pi.hThread);
	}
	else
	{
		qWarning() << "Programm isnt starting" << std::endl;
	}

	CloseHandle(h);
	return -1;
}
