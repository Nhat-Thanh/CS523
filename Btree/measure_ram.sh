OPERATION=$1
SIZE=$2
SENSORS_PATH="./result/$SIZE/$OPERATION/"$OPERATION"_sensors.txt"
DISK_PATH="./result/$SIZE/$OPERATION/"$OPERATION"_disk.txt";

sensors > $SENSORS_PATH
echo "" >"$DISK_PATH"

echo "%MEM   RSS  SIZE    VSZ" >>$SENSORS_PATH

COMMAND="/usr/bin/time -v -o ./result/$SIZE/$OPERATION/"$OPERATION"_operation_time.txt bash ./operating_script/$OPERATION.sh $SIZE"

while [ $(pgrep --full "$COMMAND") ]; do
	ps --pid $(pgrep sqlite3) --format pmem,rss,size,vsize --no-headers >>"$SENSORS_PATH" |
		du --summarize --separate-dirs --threshold=9K * >>$DISK_PATH && du --summarize >>$DISK_PATH
	sleep 3
done

echo "finish measuring ram and disk for $OPERATION operation"
exit 0