data_file_path="./data/data.txt"
database_file_path="./database.db"

n=1000000;
echo "creating a table which has $n records"

line=(`sed -n '1,1000000 p' $data_file_path`);
i=0

# sqlite3 $database_file_path "DROP TABLE Btree;"

sqlite3 $database_file_path "CREATE TABLE Btree (NUMBER INTEGER PRIMARY KEY);"

while [ $i -lt "$n" ]
do
	sqlite3 $database_file_path "INSERT INTO Btree VALUES (${line[$i]});";
	i=$(($i+1))
done

echo "finish creating database"