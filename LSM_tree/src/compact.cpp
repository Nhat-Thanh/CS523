/* 
* This program takes 1 argument
* argv[1] -> A string, the path of directory that saves database files
*/

#include <wiredtiger.h>

int main(int args, char **argv) {
    WT_CONNECTION *connection;
    WT_CURSOR *cursor;
    WT_SESSION *session;
    const char *conn_config = "cache_size=4G,eviction=(threads_min=4,threads_max=4)";

    // todo: Open a connection to the database
    wiredtiger_open(argv[1], nullptr, conn_config, &connection);
    
    // todo: Open a session handle for the database
    connection->open_session(connection, nullptr, nullptr, &session);
    
    // todo: Connect to table LSM
    session->open_cursor(session, "table:LSM", nullptr, nullptr, &cursor);
    
    // todo: Merge segment if possible
    session->compact(session, "table:LSM", nullptr);

    // todo: Close all handles
    connection->close(connection, nullptr);
    
    return 0;
}