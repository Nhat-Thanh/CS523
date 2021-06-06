TEST_NAME=$1
TH=$2
PARAM=$3
NUM_FILE=$4
i=0

if [ "$PARAM" == "n" -a "$TH" == "TH1" ]; then
    while [ $i -lt "$NUM_FILE" ]; do
        SIZE=$((505000 + 5000 * $i))

        /usr/bin/time -v -o ./result/TH1/n/$SIZE/$TEST_NAME.txt bash ./script/n.sh $TEST_NAME TH1 $SIZE |
            bash measure_ram.sh $TEST_NAME TH1 n $SIZE

        i=$(($i + 1))
    done

elif [ "$PARAM" == "n" -a "$TH" == "TH2" ]; then
    while [ $i -lt "$NUM_FILE" ]; do
        SIZE=$((10000000 + 10000000 * $i))

        /usr/bin/time -v -o ./result/TH2/n/$SIZE/$TEST_NAME.txt bash ./script/n.sh $TEST_NAME TH2 $SIZE |
            bash ./measure_ram.sh $TEST_NAME TH2 n $SIZE

        i=$(($i + 1))
    done

elif [ "$PARAM" == "k" -a "$TH" == "TH1" ]; then
    while [ $i -lt "$NUM_FILE" ]; do
        SIZE=$((100 + 100 * $i))

        /usr/bin/time -v -o ./result/TH1/k/$SIZE/$TEST_NAME.txt bash ./script/k.sh $TEST_NAME TH1 $SIZE |
            bash ./measure_ram.sh $TEST_NAME TH1 k $SIZE

        i=$(($i + 1))
    done
fi

exit 0
