OPERATION=$1
SENSORS_PATH="./result/$OPERATION/"$OPERATION"_sensors.txt"

sensors > "$SENSORS_PATH"

echo "%MEM   RSS  SIZE    VSZ" >> $SENSORS_PATH

COMMAND="/usr/bin/time -v -o ./result/$OPERATION/"$OPERATION"_operation_time.txt bash ./operating_script/$OPERATION.sh"

while [ `pgrep --full "$COMMAND"` ]
do
	ps --pid $(pgrep sqlite3) --format pmem,rss,size,vsize --no-headers >> "$SENSORS_PATH"
done

echo "finish measuring ram for $OPERATION operation"
