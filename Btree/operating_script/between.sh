N=$1
DATA_FILE_PATH="./data/$N/between_data.txt"
DATABASE_FILE_PATH="./database.db"
#N=(`wc -l < $DATA_FILE_PATH`)

LINE=(`cat $DATA_FILE_PATH`)
I=0

while [ $I -lt "$N" ]
do
	sqlite3 $DATABASE_FILE_PATH "SELECT COUNT(*) FROM Btree WHERE NUMBER BETWEEN ${LINE[$I]} AND ${LINE[$I + 1]};";
	I=$(($I+2))
done

echo "finish between operation"
