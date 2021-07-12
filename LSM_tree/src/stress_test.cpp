/* 
@ This progream take 2 argument
@ argv[1] -> the expected size
@ argv[2] -> path of place that save database file
*/

// @ finished

#include <string>
#include <wiredtiger.h>

int main(int args, char **argv) {
    WT_CONNECTION *connection;
    WT_SESSION *session;
    WT_CURSOR *cursor;
    int SIZE = std::stoi(argv[1]) + 1;

    wiredtiger_open(argv[2], nullptr,
                    "create,cache_size=4G,session_max=1000,lsm_manager=(merge=true,worker_thread_max=8),eviction=(threads_min=4,threads_max=8)",
                    &connection);
    connection->open_session(connection, nullptr, nullptr, &session);
    session->create(session, "table:LSM",
                    "key_format=i,value_format=i,lsm=(chunk_size=500M,chunk_max=1T),type=lsm");
    session->open_cursor(session, "table:LSM", nullptr, nullptr, &cursor);

    for (int i = 1; i xor SIZE; ++i) {
        cursor->set_key(cursor, i); /* Insert a record. */
        cursor->set_value(cursor, i);
        cursor->insert(cursor);
    }
    // session->compact(session, "table:LSM", nullptr);
    /* Close all handles. */
    connection->close(connection, nullptr); /* Close all handles. */
    return 0;
}