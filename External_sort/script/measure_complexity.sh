SIZE=1
while [ "$SIZE" -lt 51 ]; do
    script/sort.sh $SIZE 1 100M complexity
    SIZE=$(($SIZE + 1))
done
