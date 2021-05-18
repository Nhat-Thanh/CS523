SIZE=$1

if [ $SIZE -eq 250000000 ]; then
    echo "250 trieu"
    sqlite3 ./database_250000000.db "CREATE TABLE Btree (NUMBER INTEGER PRIMARY KEY);"
    sqlite3 ./database_250000000.db <./sql/CreateDatabase/250000000/CreateDatabase_1.sql

elif [ $SIZE -eq 500000000 ]; then

    echo "500 trieu"
    sqlite3 ./database_500000000.db "CREATE TABLE Btree (NUMBER INTEGER PRIMARY KEY);"
    sqlite3 ./database_500000000.db <./sql/CreateDatabase/500000000/CreateDatabase_1.sql

elif [ $SIZE -eq 750000000 ]; then
    echo "750 trieu"
    sqlite3 ./database_750000000.db "CREATE TABLE Btree (NUMBER INTEGER PRIMARY KEY);"
    sqlite3 ./database_750000000.db <./sql/CreateDatabase/750000000/CreateDatabase_1.sql

elif [ $SIZE -eq 1000000000 ]; then
    echo "1000 trieu"
    sqlite3 ./database_1000000000.db "CREATE TABLE Btree (NUMBER INTEGER PRIMARY KEY);"
    sqlite3 ./database_1000000000.db <./sql/CreateDatabase/1000000000/CreateDatabase_1.sql

elif [ $SIZE -eq 1250000000 ]; then
    echo "1250 trieu"
    sqlite3 ./database_1250000000.db "CREATE TABLE Btree (NUMBER INTEGER PRIMARY KEY);"
    sqlite3 ./database_1250000000.db <./sql/CreateDatabase/1250000000/CreateDatabase_1.sql

elif [ $SIZE -eq 1500000000 ]; then
    echo "1500 trieu"
    sqlite3 ./database_1500000000.db "CREATE TABLE Btree (NUMBER INTEGER PRIMARY KEY);"
    sqlite3 ./database_1500000000.db <./sql/CreateDatabase/1500000000/CreateDatabase_1.sql

elif [ $SIZE -eq 1750000000 ]; then
    echo "1750 trieu"
    sqlite3 ./database_1750000000.db "CREATE TABLE Btree (NUMBER INTEGER PRIMARY KEY);"
    sqlite3 ./database_1750000000.db <./sql/CreateDatabase/1750000000/CreateDatabase_1.sql

elif [ $SIZE -eq 2000000000 ]; then
    echo "2000 trieu"
    sqlite3 ./database_2000000000.db "CREATE TABLE Btree (NUMBER INTEGER PRIMARY KEY);"
    sqlite3 ./database_2000000000.db <./sql/CreateDatabase/2000000000/CreateDatabase_1.sql
fi

echo "finish creating databases"
exit 0
