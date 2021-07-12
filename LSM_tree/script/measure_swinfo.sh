TYPE=$1
OP=$2
SIZE=$3
AMOUNT=$4

if [ "$OP" == "create_database" ]; then
	COMMAND="bin/create_"$TYPE"_table $SIZE "$TYPE"_db/$SIZE"
else
	COMMAND="bin/$OP $TYPE $SIZE "$TYPE"_db/$SIZE $AMOUNT"
fi

SENSORS_PATH="result/$TYPE/$OP/$SIZE/sensor.txt"
DISK_PATH="result/$TYPE/$OP/$SIZE/disk.txt"
sensors >$SENSORS_PATH
echo "" >$DISK_PATH
echo "%MEM   RSS  SIZE    VSZ" >>$SENSORS_PATH

PID=$(pgrep -x --full "$COMMAND")

while [ $(pgrep -x --full "$COMMAND") ]; do
	ps --pid $PID --format pmem,rss,size,vsize --no-headers >>"$SENSORS_PATH" |
		du \
			--exclude='*.lsm' \
			--exclude='*.bf' \
			--exclude='*.wt' \
			--exclude='*.turtle' \
			--exclude='*.lock' \
			--exclude='*.basecfg' \
			--threshold=1K "$TYPE"_db/$SIZE >>$DISK_PATH 2>/dev/null
done
echo "finish measuring ram and disk, op=$OP, size=$SIZE, type=$TYPE"
exit 0