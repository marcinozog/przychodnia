#include "connectorDB.h"

/*
ConnectorDB()
*/
ConnectorDB::ConnectorDB() {
    cout << "Podaj nazwę bazy danych: ";
    cin >> servername;
    cout << "Podaj nazwę użytkownika: ";
    cin >> user;
    cout << "Podaj hasło: ";
    cin >> password;
}

/*
~ConnectorDB()
*/
ConnectorDB::~ConnectorDB() {

}

int ConnectorDB::connect() {
    if (FILE *file = fopen(servername.c_str(), "r")) {
        fclose(file);
        return sqlite3_open(servername.c_str(), &db);
        
    } 
    return -1;
}

int ConnectorDB::disconnect() {
    return sqlite3_close(db);
}

/*
send_recvQuery(string query, Response *response)
zwraca ilość wierszy
*/
int ConnectorDB::send_recvQuery(string query, Response *response) {
    this->response = response;
    sqlite3_stmt *stmt;
    int i, rc, num_rows;

    if(sqlite3_prepare_v2(db, query.c_str(), -1, &stmt, NULL) != SQLITE_OK) {
        cout << "\nERROR send_recvQuery-sqlite3_prepare_v2: " << sqlite3_errmsg(db) << endl;
        cout << "Query: " << query << "\n\n";
        return -1;
    }

    // cout << "send_recvQuery()" <<endl;

    int num_cols = sqlite3_column_count(stmt);

    while ((rc = sqlite3_step(stmt)) == SQLITE_ROW) { // SQLITE_DONE SQLITE_ROW
        // cout << "sqlite3_data_count: " << sqlite3_data_count(stmt) << endl;
        response->addRow();
		for (i = 0; i < num_cols; i++)
		{
            // if sqlite3_column_text(stmt, i) == null
            string col = reinterpret_cast<const char*>(sqlite3_column_text(stmt, i)) ? reinterpret_cast<const char*>(sqlite3_column_text(stmt, i)) : "NULL";
            response->appendToLastRow(col);
		}
	}
    if (rc != SQLITE_DONE) {
        cout << "\nERROR send_recvQuery-sqlite3_step: " << sqlite3_errmsg(db) << endl;
        cout << "Query: " << query << "\n\n";
    }

    num_rows = response->getRowNum();
    if(num_rows) {
        for(i = 0; i < num_cols; i++) {
            response->appendToHeader(sqlite3_column_name(stmt, i));
        }
    }

    sqlite3_finalize(stmt);

    return num_rows;
}

/*
sendQuery(string query)
zapytanie bez 'odpowiedzi'
*/
int ConnectorDB::sendQuery(string query) {
    this->response = response;
    sqlite3_stmt *stmt;
    int i, rc, num_rows;

    if(sqlite3_prepare_v2(db, query.c_str(), -1, &stmt, NULL) != SQLITE_OK) {
        cout << "\nERROR sendQuery-sqlite3_prepare_v2: " << sqlite3_errmsg(db) << endl;
        cout << "Query: " << query << "\n\n";
        return -1;
    }

    if (sqlite3_step(stmt) != SQLITE_DONE) {
        cout << "\nERROR sendQuery-sqlite3_step: " << sqlite3_errmsg(db) << endl;
        cout << "Query: " << query << "\n\n";
        return -1;
    }

    query = "select changes();";
    sqlite3_prepare_v2(db, query.c_str(), -1, &stmt, NULL);
    sqlite3_step(stmt);
    // cout << "Changes: " << sqlite3_column_text(stmt, 0) << endl;
    int ret  = sqlite3_column_int(stmt, 0);

    sqlite3_finalize(stmt);

    return ret;
}