/* 
@ This progream take 2 argument
@ argv[1] -> type of database, "lsm" or "btree"
@ argv[2] -> path of place that save database file
*/

// @ finished

#include <string.h>
#include <wiredtiger.h>

int main(int args, char **argv) {
    WT_CONNECTION *connection;
    WT_CURSOR *cursor;
    WT_SESSION *session;
    int *key, *value;
    int ret;
    const char *table_name = (!strcmp(argv[1], "lsm")) ? "table:LSM" : "table:Btree";
    /* Open a connection to the database */
    wiredtiger_open(argv[2], nullptr,
                    "cache_size=5G,eviction=(threads_min=4,threads_max=8)",
                    &connection);
    /* Open a session handle for the database. */
    connection->open_session(connection, nullptr, nullptr, &session);
    session->open_cursor(session, table_name, nullptr, nullptr, &cursor);
    cursor->reset(cursor); /* Restart the scan. */
    ret = cursor->next(cursor);
    while (!ret) {
        cursor->get_key(cursor, &key);
        cursor->get_value(cursor, &value);
        printf("%d : %d\n", key, value);
        ret = cursor->next(cursor);
    }

    connection->close(connection, nullptr); /* Close all handles. */
    return 0;
}