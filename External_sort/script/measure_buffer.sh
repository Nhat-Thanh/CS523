BUFFER=50
while [ "$BUFFER" -lt 1001 ]; do
    script/sort.sh 50 4 "$BUFFER"M buffer
    BUFFER=$(($BUFFER + 50))
done
