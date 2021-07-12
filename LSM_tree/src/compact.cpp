/* 
@ This progream take 1 argument
@ argv[1] -> path of place that save database file
*/

// @ finished

#include <string.h>
#include <wiredtiger.h>

int main(int args, char **argv) {
    WT_CONNECTION *connection;
    WT_CURSOR *cursor;
    WT_SESSION *session;

    /* Open a connection to the database, creating it if necessary. */
    wiredtiger_open(argv[1], nullptr,
                    "cache_size=4G,session_max=1000,eviction=(threads_min=4,threads_max=8)",
                    &connection);
    /* Open a session handle for the database. */
    connection->open_session(connection, nullptr, nullptr, &session);

    session->open_cursor(session, "table:LSM", nullptr, nullptr, &cursor);
    session->compact(session, "table:LSM", nullptr);

    connection->close(connection, nullptr); /* Close all handles. */
    return 0;
}