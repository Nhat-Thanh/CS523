/* 
@ This progream take 2 argument
@ argv[1] -> a string, tree type, (lsm, btree)
@ argv[2] -> an integer, the first size of database
@ argv[3] -> a string, path of directory that save database file
@ argv[4] -> an integer, num of records for this operation
*/

#include <cstring> /* strcmp() */
#include <string>  /* std::append(), std::c_str() */
#include <wiredtiger.h>

int main(int args, char **argv) {
    WT_CONNECTION *connection;
    WT_CURSOR *cursor;
    WT_SESSION *session;
    /* STEP = string_to_int(argv[1]) */
    int STEP = std::stoi(argv[4]);
    /* SIZE = string_to_int(argv[1]) */
    int SIZE = std::stoi(argv[2]);
    /* LIMIT = string_to_int(argv[1]) */
    int LIMIT = SIZE + STEP + 1;

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
        cursor->set_value(cursor, key + STEP);
        cursor->update(cursor);
        /* Restart the scan. */
        cursor->reset(cursor);
    }

    /* Close all handles. */
    connection->close(connection, nullptr);
    return 0;
}