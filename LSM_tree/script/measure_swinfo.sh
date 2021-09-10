TYPE=$1   # Tree type (lsm or btree)
OP=$2     # Operation's name
SIZE=$3   # Size of database
AMOUNT=$4 # The number of records that you want to interact with

# Assign the command of running process to command variable
if [ "$OP" == "create_database" ]; then
	COMMAND="bin/create_"$TYPE"_table $SIZE "$TYPE"_db/$SIZE"
else
	COMMAND="bin/$OP $TYPE $SIZE "$TYPE"_db/$SIZE $AMOUNT"
fi

# Path of sensor.txt file
SENSORS_PATH="result/$TYPE/$OP/$SIZE/sensor.txt"

# Path of disk.txt file
DISK_PATH="result/$TYPE/$OP/$SIZE/disk.txt"

# Push sensor info to sensor.txt
sensors >$SENSORS_PATH
echo "" >$DISK_PATH
echo "%MEM   RSS  SIZE    VSZ" >>$SENSORS_PATH

# Find the process id of COMMAND
PID=$(pgrep -x --full "$COMMAND")

# While process id of COMMAND is existing
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
