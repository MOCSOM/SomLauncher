#include <stdio.h>
#include <tchar.h>
#include <Windows.h>
#include <sqlext.h>
#include <locale.h>

namespace sqlbase
{
	namespace sqlexpress
	{
		void displayError(SQLSMALLINT t, SQLHSTMT h);

		/*
		WCHAR szDSN[] = L"Driver={SQL Server};DSN='';SERVER=.\\sqlexpress;DATABASE=mydatabase;";
		WCHAR query[] = L"SELECT * FROM Table";
		*/
		int connect(WCHAR szDSN[], WCHAR query[]);
	}

	namespace postgresql
	{
		int connect();
	}
}
