SIZE=$1
sqlite3 ./database_"$SIZE"_.db < ./sql/rank/$SIZE/rank.sql
echo "finish rank operation"
exit 0