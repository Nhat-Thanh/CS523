CORE=1
while [ "$CORE" -lt 9 ]; do
    script/sort.sh 50 $CORE 100M parallel
    CORE=$(($CORE + 1))
done
