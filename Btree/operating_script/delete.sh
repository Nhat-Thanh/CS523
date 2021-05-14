SIZE=$1
sqlite3 ./database_"$SIZE".db < ./sql/delete/$SIZE/delete.sql
echo "finish delete operation"
exit 0
