TYPE=$1   # tree type
START=$2  # the smallest database size
END=$3    # the biggest database size
AMOUNT=$4 # the amount of record that you want to interact with
STEP=$5   # discrepacy between 2 adjacent database size

SIZE=$START
END=$(($END + 1))

while [ "$SIZE" -lt "$END" ]; do
    # run search file in directory and measure_swinfo.sh parallelly
    /usr/bin/time -v -o result/"$TYPE"/search/$SIZE/time.txt \
        bin/search $TYPE $SIZE "$TYPE"_db/$SIZE $AMOUNT |
        bash script/measure_swinfo.sh $TYPE search $SIZE $AMOUNT
    SIZE=$(($SIZE + $STEP))
done
exit 0
