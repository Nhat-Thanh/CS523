START=$1 # The smallest SIZE
END=$2   # The biggest SIZE
STEP=$3  # The discrepancy between 2 adjacent database size

SIZE=$START
STEP=$(($SIZE + 1))

# while (SIZE < END)
while [ "$SIZE" -lt "$END" ]; do
    # Call compact in bin directory
    bin/compact lsm_db/$SIZE

    SIZE=$(($SIZE + $STEP))
done

exit 0
