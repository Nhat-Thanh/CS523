N=$1
OLD_DATA_FILE_PATH="./data/$N/old_data_for_update_operation.txt"
NEW_DATA_FILE_PATH="./data/$N/new_data_for_update_operation.txt"
DATABASE_FILE_PATH="./database.db"
#N=(`wc -l < $OLD_DATA_FILE_PATH`)

echo "$N elements are updating"

OLD=(`cat $OLD_DATA_FILE_PATH`)
NEW=(`cat $NEW_DATA_FILE_PATH`)
I=0
while [ $I -lt "$N" ]
do
	sqlite3 $DATABASE_FILE_PATH "UPDATE Btree SET NUMBER = ${NEW[$I]} WHERE NUMBER = ${OLD[$I]};"
	I=$(($I+1))	
done
echo "finish update operation"
