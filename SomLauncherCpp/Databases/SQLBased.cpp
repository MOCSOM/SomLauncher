#include "SQLBased.h"

int sqlbase::sqlexpress::connect(WCHAR szDSN[], WCHAR query[])
{
	HENV    hEnv = NULL;
	HDBC    hDbc = NULL;
	HSTMT hStmt = NULL;
	int iConnStrLength2Ptr;
	WCHAR szConnStrOut[256];
	SQLINTEGER rowCount = 0;
	SQLSMALLINT fieldCount = 0, currentField = 0;
	SQLWCHAR buf[128], colName[128];
	//SQLINTEGER ret;
	SQLLEN ret;

	/* ODBC API return status */
	RETCODE rc;

	//setlocale(LC_ALL, "Russian");

	/* Allocate an environment handle */
	rc = SQLAllocEnv(&hEnv);
	/* Allocate a connection handle */
	rc = SQLAllocConnect(hEnv, &hDbc);

	/* Connect to the database */
	rc = SQLDriverConnect(hDbc, NULL, (WCHAR*)szDSN,
		SQL_NTS, (WCHAR*)szConnStrOut,
		255, (SQLSMALLINT*)&iConnStrLength2Ptr, SQL_DRIVER_NOPROMPT);

	if (SQL_SUCCEEDED(rc))
	{
		wprintf(L"Successfully connected to database. Data source name: \n  %s\n",
			szConnStrOut);

		/* Prepare SQL query */
		wprintf(L"SQL query:\n  %s\n", query);

		rc = SQLAllocStmt(hDbc, &hStmt);
		rc = SQLPrepare(hStmt, (SQLWCHAR*)query, SQL_NTS);

		/* Excecute the query */
		rc = SQLExecute(hStmt);
		if (SQL_SUCCEEDED(rc))
		{
			wprintf(L"\n- Columns -\n");

			SQLNumResultCols(hStmt, &fieldCount);
			if (fieldCount > 0)
			{
				for (currentField = 1; currentField <= fieldCount; currentField++)
				{
					SQLDescribeCol(hStmt, currentField,
						colName, sizeof(colName), 0, 0, 0, 0, 0);
					wprintf(L"%d: %s\n", (int)currentField, colName);
				}
				wprintf(L"\n");

				/* Loop through the rows in the result set */

				rc = SQLFetch(hStmt);
				while (SQL_SUCCEEDED(rc))
				{
					wprintf(L"- Record #%d -\n", (int)rowCount);

					for (currentField = 1; currentField <= fieldCount; currentField++)
					{
						rc = SQLGetData(hStmt, currentField, SQL_C_WCHAR, buf, sizeof(buf), &ret);

						if (SQL_SUCCEEDED(rc) == FALSE)
						{
							wprintf(L"%d: SQLGetData failed\n", (int)currentField);
							continue;
						}

						if (ret <= 0)
						{
							wprintf(L"%d: (no data)\n", (int)currentField);
							continue;
						}

						wprintf(L"%d: %s\n", (int)currentField, buf);
					}

					wprintf(L"\n");
					rc = SQLFetch(hStmt);
					rowCount++;
				};

				rc = SQLFreeStmt(hStmt, SQL_DROP);
			}
			else
			{
				wprintf(L"Error: Number of fields in the result set is 0.\n");
			}
		}
		else
		{
			wprintf(L"SQL Failed\n");
			displayError(SQL_HANDLE_STMT, hStmt);

			/* Disconnect and free up allocated handles */
			SQLDisconnect(hDbc);
			SQLFreeHandle(SQL_HANDLE_DBC, hDbc);
			SQLFreeHandle(SQL_HANDLE_ENV, hEnv);
			return -1;
		}
	}
	else
	{
		wprintf(L"Couldn't connect to %s\n", szDSN);
		displayError(SQL_HANDLE_DBC, hDbc);

		/* Disconnect and free up allocated handles */
		SQLDisconnect(hDbc);
		SQLFreeHandle(SQL_HANDLE_DBC, hDbc);
		SQLFreeHandle(SQL_HANDLE_ENV, hEnv);
		return -1;
	}

	/* Disconnect and free up allocated handles */
	SQLDisconnect(hDbc);
	SQLFreeHandle(SQL_HANDLE_DBC, hDbc);
	SQLFreeHandle(SQL_HANDLE_ENV, hEnv);
	return 0;
}

void sqlbase::sqlexpress::displayError(SQLSMALLINT t, SQLHSTMT h)
{
	SQLWCHAR        SqlState[6], Msg[SQL_MAX_MESSAGE_LENGTH];
	SQLINTEGER      NativeError;
	SQLSMALLINT     i, MsgLen;
	SQLRETURN       rc;

	SQLLEN numRecs = 0;
	SQLGetDiagField(t, h, 0, SQL_DIAG_NUMBER, &numRecs, 0, 0);

	// Get the status records.
	i = 1;
	while (i <= numRecs && (rc = SQLGetDiagRec(t, h, i, SqlState, &NativeError,
		Msg, sizeof(Msg), &MsgLen)) != SQL_NO_DATA)
	{
		wprintf(L"Error %d: %s\n", NativeError, Msg);
		i++;
	}
}

int sqlbase::postgresql::connect()
{
	//pqxx::connection con;
	return 0;
}