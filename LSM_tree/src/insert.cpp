/* 
@ This progream take 4 argument
@ argv[1] -> type of database, "lsm" or "btree"
@ argv[2] -> size of database
@ argv[3] -> path of place that save database file
@ argv[4] -> num of records for this operation
*/

#include <string.h>     /* strcmp() */
#include <string>       /* append() */
#include <wiredtiger.h>

int main(int args, char **argv) {
    WT_CONNECTION *connection;
    WT_CURSOR *cursor;
    WT_SESSION *session;
    /* SIZE = string_to_int(argv[1]) */
    int SIZE = std::stoi(argv[2]);
    int LIMIT = SIZE + std::stoi(argv[4]) + 1;

    /* connection config */
    std::string conn_config;
    conn_config.append("cache_size=2G,mmap_all=false,");
    conn_config.append("lsm_manager=(worker_thread_max=8),");
    conn_config.append("eviction=(threads_min=4,threads_max=4)");

    const char *table_name = (!strcmp(argv[1], "lsm")) ? "table:LSM" : "table:Btree";

    /* Open a connection to the database */
    wiredtiger_open(argv[3], nullptr, conn_config.c_str(), &connection);
    
    /* Open a session handle for the database. */
    connection->open_session(connection, nullptr, nullptr, &session);
    
    /* connect table to a cursor */
    session->open_cursor(session, table_name, nullptr, "overwrite", &cursor);

    for (int key = SIZE + 1; key xor LIMIT; ++key) {
        cursor->set_key(cursor, key);
        cursor->set_value(cursor, key);
        cursor->insert(cursor);
        /* Restart the scan. */
        cursor->reset(cursor);
    }

    /* Close all handles. */
    connection->close(connection, nullptr);
    return 0;
}