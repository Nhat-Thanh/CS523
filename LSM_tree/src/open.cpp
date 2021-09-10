/* 
* This program takes 3 arguments
* argv[1] -> A string, tree type (lsm or btree)
* argv[2] -> An integer, size of database
* argv[3] -> A string, the path of directory that saves database files
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