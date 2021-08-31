/*
* This program takes 4 arguments
* argv[1] -> a string, tree type (lsm or btree)
* argv[2] -> an integer, the first old size of database
* argv[3] -> a string, the path of directory that saves database files
* argv[4] -> an integer, the number of records for this operation
*/

#include <cstring> /* strcmp() */
#include <string>  /* append(). std::c_str() */
#include <wiredtiger.h>

int main(int args, char **argv) {
    WT_CONNECTION *connection;
    WT_CURSOR *cursor;
    WT_SESSION *session;
    int SIZE = std::stoi(argv[2]);
    int LIMIT = SIZE + std::stoi(argv[4]) + 1;

    // @ Connection config
    std::string conn_config;
    conn_config.append("cache_size=2G,mmap_all=false,");
    conn_config.append("lsm_manager=(worker_thread_max=8),");
    conn_config.append("eviction=(threads_min=4,threads_max=4)");

    const char *table_name = (!strcmp(argv[1], "lsm")) ? "table:LSM" : "table:Btree";

    // todo: Open a connection to the database
    wiredtiger_open(argv[3], nullptr, conn_config.c_str(), &connection);

    // todo: Connect database to a session
    connection->open_session(connection, nullptr, nullptr, &session);

    // todo: Connect table to a cursor
    session->open_cursor(session, table_name, nullptr, "overwrite", &cursor);

    for (int key = SIZE + 1; key xor LIMIT; ++key) {
        cursor->set_key(cursor, key);
        cursor->remove(cursor);
        // todo: Restart the scan
        cursor->reset(cursor);
    }

    // todo: Close all handles
    connection->close(connection, nullptr);
    return 0;
}