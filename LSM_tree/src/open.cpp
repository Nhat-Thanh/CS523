/* 
* This program takes 3 arguments
* argv[1] -> a string, tree type (lsm or btree)
* argv[2] -> an integer, size of database
* argv[3] -> a string, the path of directory that saves database files
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