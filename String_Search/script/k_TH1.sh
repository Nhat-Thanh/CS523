NUM_FILE=$1
echo "testing param k - TH1"
i=0
while [ $i -lt "$NUM_FILE" ]; do
	bash grep.sh test_$((2000 + 2000 * $i)) TH1 k $NUM_FILE
	i=$(($i + 1))
done
echo "finish testing param k - TH1"
exit 0
