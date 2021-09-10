TYPE=$1   # Tree type (lsm or btree)
START=$2  # The smallest database size
END=$3    # The biggest database size
AMOUNT=$4 # The number of records that you want to interact with
STEP=$5   # The discrepacy between 2 adjacent database size

SIZE=$START
END=$(($END + 1))

while [ "$SIZE" -lt "$END" ]; do
    # Call open in bin directory and
    # run it with measure_swinfo.sh parallelly
    /usr/bin/time -v -o result/"$TYPE"/open/$SIZE/time.txt \
        bin/open $TYPE $SIZE "$TYPE"_db/$SIZE $AMOUNT |
        bash script/measure_swinfo.sh $TYPE open $SIZE $AMOUNT

    SIZE=$(($SIZE + $STEP))
done

exit 0
