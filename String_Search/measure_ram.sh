TEST_NAME=$1
TH=$2
PARAM=$3
PARAM_SIZE=$4

SENSORS_PATH="./result/$TH/$PARAM/$PARAM_SIZE/"$TEST_NAME"_sensors.txt"
DISK_PATH="./result/$TH/$PARAM/$PARAM_SIZE/"$TEST_NAME"_disk.txt"

sensors >$SENSORS_PATH
echo "" >$DISK_PATH
echo "%MEM   RSS  SIZE    VSZ" >>$SENSORS_PATH

#COMMAND="/usr/bin/time -v -o ./result/$TH/$PARAM/$PARAM_SIZE/$TEST_NAME.txt bash ./script/$PARAM.sh $TEST_NAME $TH $PARAM_SIZE"

PARENT_COMMAND="bash ./script/$PARAM.sh $TEST_NAME $TH $PARAM_SIZE"

GREP_PID=$(ps --ppid $(pgrep -x -f "$PARENT_COMMAND") --format pid --no-headers)

while [ $(pgrep -x -f "$PARENT_COMMAND") ]; do
	ps --pid $GREP_PID --format pmem,rss,size,vsize --no-headers >>"$SENSORS_PATH" |
		du --summarize /tmp >>$DISK_PATH
done

echo "finish measuring ram and disk for $TEST_NAME.txt - $TH - $PARAM - $PARAM_SIZE"
exit 0
