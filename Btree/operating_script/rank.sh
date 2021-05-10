DATA_FILE_PATH="./data/rank_data.txt"
DATABASE_FILE_PATH="./database.db"
N=1000

echo "ranking $N elements"
LINE=(`cat $DATA_FILE_PATH`)
I=0

while [ $I -lt "$N" ]
do
	sqlite3 $DATABASE_FILE_PATH "SELECT COUNT(*) FROM Btree WHERE NUMBER > ${LINE[$I]};"
	I=$(($I+1))
done
echo "finish rank operation"
