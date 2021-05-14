SIZE=$1
sqlite3 ./database_"$SIZE"_.db < ./sql/between/$SIZE/between.sql
echo "finish between operation"
exit 0
