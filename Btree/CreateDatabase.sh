echo "creating a table"

# sqlite3 $DATABASE_FILE_PATH "DROP TABLE Btree;"

sqlite3 ./database.db "CREATE TABLE Btree (NUMBER INTEGER PRIMARY KEY);"
sqlite3 ./database.db < ./sql/CreateDatabase/CreateDatabase_1.sql
sqlite3 ./database.db < ./sql/CreateDatabase/CreateDatabase_2.sql

echo "finish creating database"
