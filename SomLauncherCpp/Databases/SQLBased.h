//#include <stdio.h>
//#include <tchar.h>
//#include <Windows.h>
//#include <sqlext.h>
//#include <locale.h>
#include <memory>
#include <sstream>
#include <map>

#include "mysql_connection.h"
#include <cppconn/driver.h>
#include <cppconn/connection.h>
#include <cppconn/resultset.h>
#include <cppconn/prepared_statement.h>
#include <cppconn/exception.h>

#include <qsqldriver.h>
#include <qsqldatabase.h>
#include <qsqlquery.h>
#include <qsqlerror.h>

namespace sqlbase
{
	namespace sqlexpress
	{
		//void displayError(SQLSMALLINT t, SQLHSTMT h);

		/*
		WCHAR szDSN[] = L"Driver={SQL Server};DSN='';SERVER=.\\sqlexpress;DATABASE=mydatabase;";
		WCHAR query[] = L"SELECT * FROM Table";
		*/
		//int connect(WCHAR szDSN[], WCHAR query[]);
	}

	namespace postgresql
	{
		int connect();
	}

	namespace mysql
	{
		namespace qt
		{
			QSqlDatabase& connect(const std::string& server_adress, const std::string& database_name,
				const std::string& user_name, const std::string& password);

			QSqlQuery& getQuerry(const QSqlDatabase& database, const std::string& querry);
		}
		namespace sqlconnector
		{
			sql::Connection* connect(const std::string& server_adress, const std::string& database_name,
				const std::string& username, const std::string& password);

			sql::ResultSet* sendQuerry(sql::Connection* database, const std::string& querry);

			std::string sqlResultToStringJson(sql::ResultSet* result);
		}
	}
}
