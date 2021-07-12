START=$1
END=$2
STEP=$3

SIZE=$START

while [ "$SIZE" -lt "$END" ]; do
    bin/compact lsm_db/$SIZE
    SIZE=$(($SIZE + $STEP))
done
exit 0
