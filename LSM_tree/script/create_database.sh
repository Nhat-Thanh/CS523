TYPE=$1  # Tree type (lsm or btree)
START=$2 # The smallest database size
END=$3   # The biggest database size
STEP=$4  # The discrepacy between 2 adjacent database size

SIZE=$START
END=$(($END + 1))

while [ "$SIZE" -lt "$END" ]; do
    echo "$TYPE, size = $SIZE"
    
    # Call create_"TYPE"_table in bin directory and
    # run it with measure_swinfo.sh parallelly
    /usr/bin/time -v -o result/"$TYPE"/create_database/$SIZE/time.txt \
        bin/create_"$TYPE"_table $SIZE "$TYPE"_db/$SIZE |
        bash script/measure_swinfo.sh $TYPE create_database $SIZE
    
    SIZE=$(($SIZE + $STEP))
    
    echo "sleep 5s"
    sleep 5
done

exit 0
