OPERATION=$1
SIZE=$2
if [ $OPERATION != "rank" -a $OPERATION != "between" ]; then
    echo "this count.sh file is just only used with between and rank operations"
    exit 0
fi

/usr/bin/time -v -o ./result/$SIZE/$OPERATION/count_time.txt sqlite3 ./database_"$SIZE".db <./sql/$OPERATION/$SIZE/test_count.sql
