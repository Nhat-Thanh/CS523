TEST_NAME=$1
TH=$2
PARAM=$3
PARAM_SIZE=$4

/usr/bin/time -v -o ./result/$TH/$PARAM/$PARAM_SIZE/$TEST_NAME.txt bash ./script/$PARAM.sh $TEST_NAME $TH $PARAM_SIZE |
    bash ./measure_ram.sh $TEST_NAME $TH $PARAM $PARAM_SIZE
