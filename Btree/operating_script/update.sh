SIZE=$1
sqlite3 ./database_"$SIZE"_.db < ./sql/update/$SIZE/update.sql
echo "finish update operation"
exit 0