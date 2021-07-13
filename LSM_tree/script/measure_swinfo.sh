TYPE=$1   # tree type
OP=$2     # the name of operation
SIZE=$3   # the size of database
AMOUNT=$4 # the amount of record that you want to interact with

# assign the command of running process to command variable
if [ "$OP" == "create_database" ]; then
	COMMAND="bin/create_"$TYPE"_table $SIZE "$TYPE"_db/$SIZE"
else
	COMMAND="bin/$OP $TYPE $SIZE "$TYPE"_db/$SIZE $AMOUNT"
fi
# path of sensor.txt file
SENSORS_PATH="result/$TYPE/$OP/$SIZE/sensor.txt"
# path of disk.txt file
DISK_PATH="result/$TYPE/$OP/$SIZE/disk.txt"
# push sensor infoto sensor.txt
sensors >$SENSORS_PATH
echo "" >$DISK_PATH
echo "%MEM   RSS  SIZE    VSZ" >>$SENSORS_PATH

# find the process id of COMMAND
PID=$(pgrep -x --full "$COMMAND")

# while process id of COMMAND still existing
while [ $(pgrep -x --full "$COMMAND") ]; do
	# get pmen, rss, size and vsize info and push to sensor.txt
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
