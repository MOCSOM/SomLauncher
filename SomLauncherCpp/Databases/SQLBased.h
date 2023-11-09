#include <stdio.h>
#include <tchar.h>
#include <Windows.h>
#include <sqlext.h>
#include <locale.h>

//#include <cppconn/driver.h>
#include <qsqldriver.h>
#include <qsqldatabase.h>
#include <qsqlquery.h>

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

	namespace mysql
	{
		QSqlDatabase& connect(const std::string& host_name, const std::string& database_name,
			const std::string& user_name, const std::string& password);

		QSqlQuery& getQuerry(const QSqlDatabase& database, const std::string& querry);
	}
}
