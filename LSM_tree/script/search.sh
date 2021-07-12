TYPE=$1
START=$2
END=$3
AMOUNT=$4
STEP=$5

SIZE=$START
END=$(($END + 1))

while [ "$SIZE" -lt "$END" ]; do
    /usr/bin/time -v -o result/"$TYPE"/search/$SIZE/time.txt \
        bin/search $TYPE $SIZE "$TYPE"_db/$SIZE $AMOUNT |
        bash script/measure_swinfo.sh $TYPE search $SIZE $AMOUNT
    SIZE=$(($SIZE + $STEP))
done
