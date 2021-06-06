NUM_FILE=$1
echo "testing param k - TH1"
i=0
while [ $i -lt "$NUM_FILE" ]; do
	j=0
	while [ "$j" -lt "$NUM_FILE" ]; do
		bash grep.sh test_$((2000 + 2000 * $j)) TH1 k $NUM_FILE
		j=$(($j + 1))
	done
	i=$(($i + 1))
done
echo "finish testing param k - TH1"
exit 0
