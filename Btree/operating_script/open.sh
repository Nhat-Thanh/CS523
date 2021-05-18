SIZE=$1
i=0
while [ $i -lt 1000 ]; do
    sqlite3 ./database_$SIZE.db ".quit"
    i=$(($i + 1))
done
exit 0
