/* 
* This program takes 2 arguments
* argv[1] -> An integer, the expected size
* argv[2] -> A string, the path of directory that saves database files
*/

#include <string> /* std::append, std::c_str() */
#include <wiredtiger.h>

int main(int args, char **argv) {
    WT_CONNECTION *connection;
    WT_SESSION *session;
    WT_CURSOR *cursor;
    int SIZE = std::stoi(argv[1]) + 1;

    /* 
    @ connection config 
    */
    std::string conn_config;
    conn_config.append("create,cache_size=2G,mmap_all=false,");
    conn_config.append("lsm_manager=(worker_thread_max=8),");
    conn_config.append("eviction=(threads_min=4,threads_max=4)");

    /* 
    @ table config 
    */
    std::string table_config;
    table_config.append("key_format=i,value_format=i,type=lsm,");
    table_config.append("internal_page_max=128K,leaf_page_max=16K,");
    table_config.append("os_cache_dirty_max=16MB,");
    table_config.append("lsm=(auto_throttle=true,chunk_size=500MB,");
    table_config.append("chunk_max = 5G,bloom=true,bloom_bit_count=30,");
    table_config.append("bloom_hash_count=20,bloom_oldest=true)");

    // todo: Open a connection to the database
    wiredtiger_open(argv[2], nullptr, conn_config.c_str(), &connection);

    // todo: Connect database to a session
    connection->open_session(connection, nullptr, nullptr, &session);

    // todo: Create a table that has table_condfig
    session->create(session, "table:LSM", table_config.c_str());

    // todo: Connect table to a cursor
    session->open_cursor(session, "table:LSM", nullptr, "overwrite", &cursor);

    for (int i = 1; i xor SIZE; ++i) {
        cursor->set_key(cursor, i);
        cursor->set_value(cursor, i);
        cursor->insert(cursor);

        // todo: Restart the scan
        cursor->reset(cursor);
    }

    // todo: Close all handles
    connection->close(connection, nullptr);
    
    return 0;
}