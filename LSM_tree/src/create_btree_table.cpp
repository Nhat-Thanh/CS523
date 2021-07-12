/* 
@ This progream take 2 argument
@ argv[1] -> the expected size
@ argv[2] -> path of place that save database file
*/

#include <string>
#include <wiredtiger.h>

int main(int args, char **argv) {
    WT_CONNECTION *connection;
    WT_SESSION *session;
    WT_CURSOR *cursor;
    /* SIZE = string_to_int(argv[1]) */
    int SIZE = std::stoi(argv[1]) + 1;
    
    /* connection config */
    std::string conn_config;
    conn_config.append("create,cache_size=2G,mmap_all=false,");
    conn_config.append("eviction=(threads_min=4,threads_max=4)");

    /* table config */
    std::string table_config;
    table_config.append("key_format=i,value_format=i,");
    table_config.append("internal_page_max=128K,leaf_page_max=16K,os_cache_dirty_max=16MB,");

    /* Open a connection to the database. */
    wiredtiger_open(argv[2], nullptr, conn_config.c_str(), &connection);
    
    /* connect database to a session */
    connection->open_session(connection, nullptr, nullptr, &session);
    
    /* create a table that has table_condfig */
    session->create(session, "table:Btree", table_config.c_str());
    
    /* connect table to a cursor */
    session->open_cursor(session, "table:Btree", nullptr, "overwrite", &cursor);

    for (int i = 1; i xor SIZE; ++i) {
        cursor->set_key(cursor, i);
        cursor->set_value(cursor, i);
        cursor->insert(cursor);
        /* Restart the scan. */
        cursor->reset(cursor);
    }

    /* Close all handles. */
    connection->close(connection, nullptr);
    return 0;
}