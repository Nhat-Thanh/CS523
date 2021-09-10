/* 
* This program takes 2 arguments
* argv[1] A string, tree type (lsm or btree)
* argv[2] A string, the path of directory that saves database files
*/

#include <cstring> /* strcmp */
#include <wiredtiger.h>

int main(int args, char **argv) {
    WT_CONNECTION *connection;
    WT_CURSOR *cursor;
    WT_SESSION *session;
    int *key, *value;
    int ret;
    
    // todo: Connection config
    const char *conn_config = "cache_size=2G,eviction=(threads_min=4,threads_max=4)";
    const char *table_name = (!strcmp(argv[1], "lsm")) ? "table:LSM" : "table:Btree";

    // todo: Open a connection to the database
    wiredtiger_open(argv[2], nullptr, conn_config, &connection);

    // todo: Open a session handle for the database
    connection->open_session(connection, nullptr, nullptr, &session);

    // todo: Connect table to a cursor
    session->open_cursor(session, table_name, nullptr, nullptr, &cursor);

    // todo: Restart the scan
    cursor->reset(cursor);
    ret = cursor->next(cursor);

    while (!ret) {
        cursor->get_key(cursor, &key);
        cursor->get_value(cursor, &value);
        printf("%d : %d\n", key, value);
        ret = cursor->next(cursor);
    }

    // todo: Close all handles
    connection->close(connection, nullptr);
    
    return 0;
}