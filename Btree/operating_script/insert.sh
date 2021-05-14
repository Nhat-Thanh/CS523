SIZE=$1
sqlite3 ./database_"$SIZE".db < ./sql/insert/$SIZE/insert.sql
echo "finish insert operation"
exit 0