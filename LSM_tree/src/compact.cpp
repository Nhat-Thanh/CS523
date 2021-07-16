/* 
@ This progream take 1 argument
@ argv[1] -> path of place that save database file
*/

#include <wiredtiger.h>

int main(int args, char **argv) {
    WT_CONNECTION *connection;
    WT_CURSOR *cursor;
    WT_SESSION *session;
    const char *conn_config = "cache_size=4G,eviction=(threads_min=4,threads_max=4)";

    /* Open a connection to the database. */
    wiredtiger_open(argv[1], nullptr, conn_config, &connection);
    
    /* Open a session handle for the database. */
    connection->open_session(connection, nullptr, nullptr, &session);
    
    /* connect to table LSM */
    session->open_cursor(session, "table:LSM", nullptr, nullptr, &cursor);
    
    /* merge segment if possible */
    session->compact(session, "table:LSM", nullptr);

    /* Close all handles. */
    connection->close(connection, nullptr);
    return 0;
}