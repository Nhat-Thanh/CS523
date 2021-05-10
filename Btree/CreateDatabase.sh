DATA_FILE_PATH="./data/data.txt"
DATABASE_FILE_PATH="./database.db"

N=1000000;
echo "creating a table which has $n records"

LINE=(`sed -n '1,1000000 p' $DATA_FILE_PATH`);
I=0

# sqlite3 $DATABASE_FILE_PATH "DROP TABLE Btree;"

sqlite3 $DATABASE_FILE_PATH "CREATE TABLE Btree (NUMBER INTEGER PRIMARY KEY);"

while [ $I -lt "$N" ]
do
	sqlite3 $DATABASE_FILE_PATH "INSERT INTO Btree VALUES (${LINE[$I]});";
	I=$(($I+1))
done

echo "finish creating database"
