SIZE=$1

if [ $SIZE != "all" ]; then
    sqlite3 ./database_250000000.db "DELETE FROM Btree WHERE NUMBER > 250000000"
    sqlite3 ./database_500000000.db "DELETE FROM Btree WHERE NUMBER > 500000000"
    sqlite3 ./database_750000000.db "DELETE FROM Btree WHERE NUMBER > 750000000"
    sqlite3 ./database_1000000000.db "DELETE FROM Btree WHERE NUMBER > 1000000000"
    sqlite3 ./database_1250000000.db "DELETE FROM Btree WHERE NUMBER > 1250000000"
    sqlite3 ./database_1500000000.db "DELETE FROM Btree WHERE NUMBER > 1500000000"
    sqlite3 ./database_1750000000.db "DELETE FROM Btree WHERE NUMBER > 1750000000"
    sqlite3 ./database_2000000000.db "DELETE FROM Btree WHERE NUMBER > 2000000000"
else
    sqlite3 ./database_$SIZE.db "DELETE FROM Btree WHERE NUMBER > $SIZE"
fi

echo "finish"
exit 0
