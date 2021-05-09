old_data_file_path="../data/old_data_for_update_operation.txt"
new_data_file_path="../data/new_data_for_update_operation.txt"
database_file_path="../database.db"

n=1000
echo "$n elements are updating"

old=(`cat $old_data_file_path`)
new=(`cat $new_data_file_path`)
i=0
while [ $i -lt "$n" ]
do
	sqlite3 $database_file_path "UPDATE Btree SET NUMBER = ${new[$i]} WHERE NUMBER = ${old[$i]};"
	i=$(($i+1))	
done
echo "finish update operation"
