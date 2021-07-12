TYPE=$1
START=$2
END=$3
AMOUNT=$4
STEP=$5

SIZE=$START
END=$(($END + 1))

while [ "$SIZE" -lt "$END" ]; do
    /usr/bin/time -v -o result/"$TYPE"/open/$SIZE/time.txt \
        bin/open $TYPE $SIZE "$TYPE"_db/$SIZE $AMOUNT | 
        bash script/measure_swinfo.sh $TYPE open $SIZE $AMOUNT
    SIZE=$(($SIZE + $STEP))
done
