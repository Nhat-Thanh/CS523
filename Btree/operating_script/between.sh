DATA_FILE_PATH="./data/between_data.txt"
DATABASE_FILE_PATH="./database.db"

n=1000
echo "between with 1000 ranges"

LINE=(`cat $DATA_FILE_PATH`)
i=0

while [ $i -lt "$n" ]
do
	sqlite3 $DATABASE_FILE_PATH "SELECT COUNT(*) FROM Btree WHERE NUMBER BETWEEN ${LINE[$i]} AND ${LINE[$i + 1]}";
	i=$(($i+2))
done

echo "finish between operation"
