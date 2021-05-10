DATA_FILE_PATH="./data/insert_data.txt"
DATABASE_FILE_PATH="./database.db"
N=1000
echo "inserting $N elements into Btree"                                                                                                                  
LINE=(`cat $DATA_FILE_PATH`)
I=0
while [ $I -lt "$N" ]
do
        sqlite3 "$DATABASE_FILE_PATH" "INSERT INTO Btree VALUES (${LINE[$I]});"
        I=$(($I+1))
done
echo "finish insert operation"
