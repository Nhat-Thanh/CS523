/* 
* This progream take 3 argument
* argv[1] -> type of database, "lsm" or "btree"
* argv[2] -> size of database
* argv[3] -> path of place that save database file
*/

#include <wiredtiger.h>

int main(int args, char **argv) {
    WT_CONNECTION *connection;
    // todo: Open a connection to the database
    wiredtiger_open(argv[3], nullptr, nullptr, &connection);
    // todo: Close all handles
    connection->close(connection, nullptr);
    return 0;
}