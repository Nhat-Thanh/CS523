/* 
@ This progream take 2 argument
@ argv[1] -> type of database, "lsm" or "btree"
@ argv[2] -> path of place that save database file
*/

#include <cstring> /* strcmp */
#include <wiredtiger.h>

int main(int args, char **argv) {
    WT_CONNECTION *connection;
    WT_CURSOR *cursor;
    WT_SESSION *session;
    int *key, *value;
    int ret;
    /* connection config */
    const char *conn_config = "cache_size=2G,eviction=(threads_min=4,threads_max=4)";
    const char *table_name = (!strcmp(argv[1], "lsm")) ? "table:LSM" : "table:Btree";

    /* Open a connection to the database */
    wiredtiger_open(argv[2], nullptr, conn_config, &connection);

    /* Open a session handle for the database. */
    connection->open_session(connection, nullptr, nullptr, &session);

    /* connect table to a cursor */
    session->open_cursor(session, table_name, nullptr, nullptr, &cursor);

    /* Restart the scan. */
    cursor->reset(cursor);
    ret = cursor->next(cursor);

    while (!ret) {
        cursor->get_key(cursor, &key);
        cursor->get_value(cursor, &value);
        printf("%d : %d\n", key, value);
        ret = cursor->next(cursor);
    }

    /* Close all handles. */
    connection->close(connection, nullptr); /* Close all handles. */
    return 0;
}