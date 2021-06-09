NUM_FILE=$1

i=0
while [ "$i" -lt "$NUM_FILE" ]; do
	j=0
	TEST_NAME="test_$((2000 + 2000 * $i))"
	
	while [ $j -lt "$NUM_FILE" ]; do
		PARAM_SIZE=$((10000000 + 10000000 * $j))
		sensorpath="./result/TH2/n/$PARAM_SIZE/"$TEST_NAME"_sensors.txt"
	        
	        numline=$(wc -l < $sensorpath)
		numline=$(($num - 1))
		head -n $numline $sensorpath > ~/temp.txt && cat ~/temp.txt > $sensorpath
        	j=$(($j + 1))
	done
	
	j=0
	
	while [ $j -lt "$NUM_FILE" ]; do
		PARAM_SIZE=$((505000 + 5000 * $j))
		sensorpath="./result/TH1/n/$PARAM_SIZE/"$TEST_NAME"_sensors.txt"
	        
	        numline=$(wc -l < $sensorpath)
		numline=$(($num - 1))
		head -n $numline $sensorpath > ~/temp.txt && cat ~/temp.txt > $sensorpath
        	j=$(($j + 1))
	done
	
	j=0
	
	while [ $j -lt "$NUM_FILE" ]; do
		PARAM_SIZE=$((100 + 100 * $j))
		sensorpath="./result/TH1/k/$PARAM_SIZE/"$TEST_NAME"_sensors.txt"
	        
	        numline=$(wc -l < $sensorpath)
		numline=$(($num - 1))
		head -n $numline $sensorpath > ~/temp.txt && cat ~/temp.txt > $sensorpath
        	j=$(($j + 1))
	done
	i=$(($i + 1))
done
echo "finish"
exit 0
