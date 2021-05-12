N=$1
DATA_FILE_PATH="./data/$N/delete_data.txt"
DATABASE_FILE_PATH="./database.db"                                                                                  

echo "deleting $N elements from Btree"

LINE=(`cat $DATA_FILE_PATH`)
I=0

while [ $I -lt "$N" ]
do                                                                                                         
        sqlite3 $DATABASE_FILE_PATH "DELETE FROM Btree WHERE NUMBER = ${LINE[$I]};"
        I=$(($I+1))
done

echo "finish delete operation"
