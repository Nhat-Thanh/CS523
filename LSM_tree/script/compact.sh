START=$1 # the smallest SIZE
END=$2   # the biggest SIZE
STEP=$3  # discrepancy between 2 adjacent database size

SIZE=$START
STEP=$(($SIZE + 1))

# while (SIZE < END)
while [ "$SIZE" -lt "$END" ]; do
    # run compact file in bin directory
    bin/compact lsm_db/$SIZE
    SIZE=$(($SIZE + $STEP))
done
exit 0
