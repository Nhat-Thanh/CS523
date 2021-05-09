data_file_path="./data/between_data.txt"
database_file_path="./database.db"

n=1000
echo "between with 1000 ranges"

line=(`cat $data_file_path`)
i=0

while [ $i -lt "$n" ]
do
	sqlite3 $database_file_path "SELECT COUNT(*) FROM Btree WHERE NUMBER BETWEEN ${line[$i]} AND ${line[$i + 1]}";
	i=$(($i+2))
done

echo "finish between operation"
