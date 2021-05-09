data_file_path="./data/rank_data.txt"
database_file_path="./database.db"

n=1000

echo "ranking 1000 elements"

line=(`cat $data_file_path`)
i=0

while [ $i -lt "$n" ]
do
	sqlite3 $database_file_path "SELECT COUNT(*) FROM Btree WHERE NUMBER > ${line[$i]};"
	i=$(($i+1))
done
echo "finish rank operation"
