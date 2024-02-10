#include <iostream>
#include <sqlite3.h>
#include "response.h"

using namespace std;

class ConnectorDB {
    private:
        string servername;
        string user;
        string password;
        sqlite3 *db;
        char *error = 0;
        Response *response;
    
    public:
        ConnectorDB();
        ConnectorDB(string servername, string user, string password):
            servername(servername), user(user), password(password){};
        ~ConnectorDB();
        int connect();
        int disconnect();
        int send_recvQuery(string query, Response *response);
        int sendQuery(string query);
};