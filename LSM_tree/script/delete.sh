TYPE=$1   # Tree type (lsm or btree)
START=$2  # The smallest database size
END=$3    # The biggest database size
AMOUNT=$4 # The number of records that you want to interact with
STEP=$5   # The discrepacy between 2 adjacent database size

SIZE=$START
END=$(($END + 1))

# while (SIZE < END)
while [ "$SIZE" -lt "$END" ]; do
    # Call delete in bin directory and
    # run it with measure_swinfo.sh parallelly
    /usr/bin/time -v -o result/"$TYPE"/delete/$SIZE/time.txt \
        bin/delete $TYPE $SIZE "$TYPE"_db/$SIZE $AMOUNT |
        bash script/measure_swinfo.sh $TYPE delete $SIZE $AMOUNT

    SIZE=$(($SIZE + $STEP))
done

exit 0
