OPERATION=$1
SENSORS_PATH="./result/$OPERATION/"$OPERATION"_sensors.txt"

sensors >> "$SENSORS_PATH";

echo "%MEM   RSS  SIZE    VSZ CMD" >> "$SENSORS_PATH";

COMMAND="/usr/bin/time -v -o ./result/"$OPERATION"/"$OPERATION"_operation_time.txt ./operating_script/"$OPERATION".sh"

while [ `pgrep --full "$COMMAND"` ]
do
	# top -p$(pgrep --full "$command") >> $SENSORS_PATH
	ps --pid $(pgrep sqlite3) --format pmem,rss,size,vsize --no-headers >> "$SENSORS_PATH"
done

echo "finish measuring ram"

