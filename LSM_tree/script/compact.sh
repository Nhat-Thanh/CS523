SIZE=100000

while [ "$SIZE" -lt 10000001 ]; do
    bin/compact lsm_db/$SIZE
    SIZE=$(($SIZE + 100000))
done