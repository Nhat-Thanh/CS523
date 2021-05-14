SIZE=$1
sqlite3 ./database_"$SIZE".db < ./sql/rank/$SIZE/rank.sql
echo "finish rank operation"
exit 0