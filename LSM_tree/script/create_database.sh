TYPE=$1
START=$2
END=$3
STEP=$4

# SIZE=100000
SIZE=$START
END=$(($END + 1))

while [ "$SIZE" -lt "$END" ]; do
    echo "$TYPE, size = $SIZE"
    /usr/bin/time -v -o result/"$TYPE"/create_database/$SIZE/time.txt \
        bin/create_"$TYPE"_table $SIZE "$TYPE"_db/$SIZE |
        bash script/measure_swinfo.sh $TYPE create_database $SIZE
    SIZE=$(($SIZE + $STEP))
    echo "sleep 5s"
    sleep 5
done