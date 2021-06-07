NUM_FILE=$1
echo "testing param n - TH1"
i=0
while [ $i -lt "$NUM_FILE" ]; do
	bash grep.sh test_$((2000 + 2000 * $i)) TH1 n $NUM_FILE
	i=$(($i + 1))
done
echo "finish testing param n - TH1"
exit 0
