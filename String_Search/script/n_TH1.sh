NUM_FILE=$1
i=0
echo "testing param n - TH1"
while [ $i -lt "$NUM_FILE" ]; do
	j=0
	while [ "$j" -lt "$NUM_FILE" ]; do
		bash grep.sh test_$((2000 + 2000 * $j)) TH1 n $NUM_FILE
		j=$(($j + 1))
	done
	i=$(($i + 1))
done
echo "finish testing param n - TH1"
exit 0
