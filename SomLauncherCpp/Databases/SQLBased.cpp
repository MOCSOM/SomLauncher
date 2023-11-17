#include "SQLBased.h"

//int sqlbase::sqlexpress::connect(WCHAR szDSN[], WCHAR query[])
//{
//	//HENV    hEnv = NULL;
//	//HDBC    hDbc = NULL;
//	//HSTMT hStmt = NULL;
//	//int iConnStrLength2Ptr;
//	//WCHAR szConnStrOut[256];
//	//SQLINTEGER rowCount = 0;
//	//SQLSMALLINT fieldCount = 0, currentField = 0;
//	//SQLWCHAR buf[128], colName[128];
//	////SQLINTEGER ret;
//	//SQLLEN ret;
//
//	///* ODBC API return status */
//	//RETCODE rc;
//
//	////setlocale(LC_ALL, "Russian");
//
//	///* Allocate an environment handle */
//	//rc = SQLAllocEnv(&hEnv);
//	///* Allocate a connection handle */
//	//rc = SQLAllocConnect(hEnv, &hDbc);
//
//	///* Connect to the database */
//	//rc = SQLDriverConnect(hDbc, NULL, (WCHAR*)szDSN,
//	//	SQL_NTS, (WCHAR*)szConnStrOut,
//	//	255, (SQLSMALLINT*)&iConnStrLength2Ptr, SQL_DRIVER_NOPROMPT);
//
//	//if (SQL_SUCCEEDED(rc))
//	//{
//	//	wprintf(L"Successfully connected to database. Data source name: \n  %s\n",
//	//		szConnStrOut);
//
//	//	/* Prepare SQL query */
//	//	wprintf(L"SQL query:\n  %s\n", query);
//
//	//	rc = SQLAllocStmt(hDbc, &hStmt);
//	//	rc = SQLPrepare(hStmt, (SQLWCHAR*)query, SQL_NTS);
//
//	//	/* Excecute the query */
//	//	rc = SQLExecute(hStmt);
//	//	if (SQL_SUCCEEDED(rc))
//	//	{
//	//		wprintf(L"\n- Columns -\n");
//
//	//		SQLNumResultCols(hStmt, &fieldCount);
//	//		if (fieldCount > 0)
//	//		{
//	//			for (currentField = 1; currentField <= fieldCount; currentField++)
//	//			{
//	//				SQLDescribeCol(hStmt, currentField,
//	//					colName, sizeof(colName), 0, 0, 0, 0, 0);
//	//				wprintf(L"%d: %s\n", (int)currentField, colName);
//	//			}
//	//			wprintf(L"\n");
//
//	//			/* Loop through the rows in the result set */
//
//	//			rc = SQLFetch(hStmt);
//	//			while (SQL_SUCCEEDED(rc))
//	//			{
//	//				wprintf(L"- Record #%d -\n", (int)rowCount);
//
//	//				for (currentField = 1; currentField <= fieldCount; currentField++)
//	//				{
//	//					rc = SQLGetData(hStmt, currentField, SQL_C_WCHAR, buf, sizeof(buf), &ret);
//
//	//					if (SQL_SUCCEEDED(rc) == FALSE)
//	//					{
//	//						wprintf(L"%d: SQLGetData failed\n", (int)currentField);
//	//						continue;
//	//					}
//
//	//					if (ret <= 0)
//	//					{
//	//						wprintf(L"%d: (no data)\n", (int)currentField);
//	//						continue;
//	//					}
//
//	//					wprintf(L"%d: %s\n", (int)currentField, buf);
//	//				}
//
//	//				wprintf(L"\n");
//	//				rc = SQLFetch(hStmt);
//	//				rowCount++;
//	//			};
//
//	//			rc = SQLFreeStmt(hStmt, SQL_DROP);
//	//		}
//	//		else
//	//		{
//	//			wprintf(L"Error: Number of fields in the result set is 0.\n");
//	//		}
//	//	}
//	//	else
//	//	{
//	//		wprintf(L"SQL Failed\n");
//	//		displayError(SQL_HANDLE_STMT, hStmt);
//
//	//		/* Disconnect and free up allocated handles */
//	//		SQLDisconnect(hDbc);
//	//		SQLFreeHandle(SQL_HANDLE_DBC, hDbc);
//	//		SQLFreeHandle(SQL_HANDLE_ENV, hEnv);
//	//		return -1;
//	//	}
//	//}
//	//else
//	//{
//	//	wprintf(L"Couldn't connect to %s\n", szDSN);
//	//	displayError(SQL_HANDLE_DBC, hDbc);
//
//	//	/* Disconnect and free up allocated handles */
//	//	SQLDisconnect(hDbc);
//	//	SQLFreeHandle(SQL_HANDLE_DBC, hDbc);
//	//	SQLFreeHandle(SQL_HANDLE_ENV, hEnv);
//	//	return -1;
//	//}
//
//	///* Disconnect and free up allocated handles */
//	//SQLDisconnect(hDbc);
//	//SQLFreeHandle(SQL_HANDLE_DBC, hDbc);
//	//SQLFreeHandle(SQL_HANDLE_ENV, hEnv);
//	return 0;
//}

//void sqlbase::sqlexpress::displayError(SQLSMALLINT t, SQLHSTMT h)
//{
//	//SQLWCHAR        SqlState[6], Msg[SQL_MAX_MESSAGE_LENGTH];
//	//SQLINTEGER      NativeError;
//	//SQLSMALLINT     i, MsgLen;
//	//SQLRETURN       rc;
//
//	//SQLLEN numRecs = 0;
//	//SQLGetDiagField(t, h, 0, SQL_DIAG_NUMBER, &numRecs, 0, 0);
//
//	//// Get the status records.
//	//i = 1;
//	//while (i <= numRecs && (rc = SQLGetDiagRec(t, h, i, SqlState, &NativeError,
//	//	Msg, sizeof(Msg), &MsgLen)) != SQL_NO_DATA)
//	//{
//	//	wprintf(L"Error %d: %s\n", NativeError, Msg);
//	//	i++;
//	//}
//}

int sqlbase::postgresql::connect()
{
	/*PGconn* conn = PQsetdbLogin(
		"tcp://79.174.93.203",
		"3306",
		NULL,
		NULL,
		"sombd",
		"debug",
		"admindebug1"
	);

	switch (PQstatus(conn))
	{
	case CONNECTION_STARTED:
		qInfo() << "Connecting...";
		break;

	case CONNECTION_MADE:
		qInfo() << "Connected to server...";
		break;
	default:
		qInfo() << "Connecting...";
	}*/
	return 0;
	//try
	//{
	//	// Connect to the database.  In practice we may have to pass some
	//	// arguments to say where the database server is, and so on.
	//	// The constructor parses options exactly like libpq's
	//	// PQconnectdb/PQconnect, see:
	//	// https://www.postgresql.org/docs/10/static/libpq-connect.html
	//	//"postgresql://username:password@adress/dbname:port"
	//	pqxx::connection c("postgresql://debug:admindebug1@79.174.93.203/sombd:3306");

	//	// Start a transaction.  In libpqxx, you always work in one.
	//	pqxx::work w(c);

	//	// work::exec1() executes a query returning a single row of data.
	//	// We'll just ask the database to return the number 1 to us.
	//	pqxx::row r = w.exec1("SELECT 1");

	//	// Commit your transaction.  If an exception occurred before this
	//	// point, execution will have left the block, and the transaction will
	//	// have been destroyed along the way.  In that case, the failed
	//	// transaction would implicitly abort instead of getting to this point.
	//	w.commit();

	//	// Look at the first and only field in the row, parse it as an integer,
	//	// and print it.
	//	std::cout << r[0].as<int>() << std::endl;
	//}
	//catch (const std::exception& e)
	//{
	//	std::cerr << e.what() << std::endl;
	//	return 1;
	//}

	//QSqlDatabase db = QSqlDatabase::addDatabase("QPSQL", "conn1");
	////db.setConnectOptions("SSL_KEY=client-key.pem;SSL_CERT=client-cert.pem;SSL_CA=ca-cert.pem;CLIENT_IGNORE_SPACE=1");
	//db.setHostName("tcp://79.174.93.203");
	//db.setDatabaseName("sombd");
	//db.setUserName("debug");
	//db.setPassword("admindebug1");
	//db.setPort(3306);

	//bool ok = db.open();
	//if (ok)
	//{
	//	qDebug() << "conn establish";
	//	//return db;
	//}
	//else
	//{
	//	//TODO: error handler
	//	qWarning() << db.lastError() << " - " << db.lastError().type();
	//	//return db;
	//}
	//return 1;
}

QSqlDatabase& sqlbase::mysql::qt::connect(
	const std::string& server_adress,
	const std::string& database_name,
	const std::string& user_name,
	const std::string& password)
{
	QSqlDatabase db = QSqlDatabase::addDatabase("QMYSQL", "conn1");
	//db.setConnectOptions("SSL_KEY=client-key.pem;SSL_CERT=client-cert.pem;SSL_CA=ca-cert.pem;CLIENT_IGNORE_SPACE=1");
	db.setHostName("tcp://37.140.192.89");
	db.setDatabaseName("u2306233_SomSite");
	db.setUserName("u2306233_debug");
	db.setPassword("debugadminmoc1");
	db.setPort(3306);

	bool ok = db.open();
	if (ok)
	{
		qDebug() << "conn establish";
		return db;
	}
	else
	{
		//TODO: error handler
		qWarning() << db.lastError() << " - " << db.lastError().type();
		return db;
	}
}

QSqlQuery& sqlbase::mysql::qt::getQuerry(const QSqlDatabase& database, const std::string& querry)
{
	QSqlQuery querry_from_db = QSqlQuery(database);
	querry_from_db.prepare(querry.c_str());

	bool ok = querry_from_db.exec();
	if (ok)
	{
		return querry_from_db;
	}
	else
	{
		//TODO: error handler
		return querry_from_db;
	}
}

sql::Connection* sqlbase::mysql::sqlconnector::connect(const std::string& server_adress, const std::string& database_name, const std::string& username, const std::string& password)
{
	sql::Driver* driver = nullptr;
	sql::Connection* con = nullptr;

	driver = get_driver_instance();
	con = driver->connect("tcp://" + server_adress + ":3306", username, password);
	con->setSchema(database_name);

	return con;
}

sql::ResultSet* sqlbase::mysql::sqlconnector::sendQuerry(sql::Connection* database, const std::string& querry)
{
	sql::Statement* stmt = nullptr;
	sql::ResultSet* res = nullptr;

	stmt = database->createStatement();
	res = stmt->executeQuery(querry);

	return res;
}

std::string sqlbase::mysql::sqlconnector::sqlResultToStringJson(sql::ResultSet* result)
{
	std::stringstream builder;

	while (result->next())
	{
		sql::SQLString str;
		size_t iter = 0;
		bool is_continue = true;
		while (is_continue)
		{
			++iter;
			try
			{
				str = result->getString(iter);
				builder << '\"' << str << '\"' << ',';
			}
			catch (const sql::SQLException& exc_sql)
			{
				is_continue = false;
			}
		}

		builder << std::endl;
	}

	return builder.str();
}