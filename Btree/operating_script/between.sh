SIZE=$1
sqlite3 ./database_"$SIZE".db < ./sql/between/$SIZE/between.sql
echo "finish between operation"
exit 0
