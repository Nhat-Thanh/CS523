operation=$1
SENSORS_PATH="./result/$operation/"$operation"_sensors.txt"

sleep 0.1

sensors >> "$SENSORS_PATH"

echo "%CPU %MEM     ELAPSED" >> "$SENSORS_PATH"

while [ pgrep time ]
do
	ps --pid $(pgrep sqlite3) --format pcpu,pmem,etime --no-headers >> "$SENSORS_PATH"
	sleep 1
done

echo "finish measuring ram"
