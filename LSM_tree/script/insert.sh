TYPE=$1   # tree type (lsm or btree)
START=$2  # the smallest database size
END=$3    # the biggest database size
AMOUNT=$4 # the number of records that you want to interact with
STEP=$5   # discrepacy between 2 adjacent database size

SIZE=$START
END=$(($END + 1))

# while (SIZE < END)
while [ "$SIZE" -lt "$END" ]; do
    # run insert in bin directory and measure_swinfo.sh parallelly
    /usr/bin/time -v -o result/"$TYPE"/insert/$SIZE/time.txt \
        bin/insert $TYPE $SIZE "$TYPE"_db/$SIZE $AMOUNT |
        bash script/measure_swinfo.sh $TYPE insert $SIZE $AMOUNT
    SIZE=$(($SIZE + $STEP))
done
exit 0
