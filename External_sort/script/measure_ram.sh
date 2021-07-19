SIZE=$1
CORE_NUMBER=$2
BUFFER=$3
TEST_MODE=$4

PATH_SENSOR="result/complexity/"$SIZE"_trieu/sensors_"$SIZE"_trieu_"$CORE_NUMBER"_cores_"$BUFFER".txt"

# buffer mode
if [ $TEST_MODE == "buffer" ]; then
	PATH_SENSOR="result/buffer/"$BUFFER"/sensors_"$SIZE"_trieu_"$CORE_NUMBER"_cores_"$BUFFER".txt"
fi

# parallel mode
if [ $TEST_MODE == "parallel" ]; then
	PATH_SENSOR="result/parallel/"$CORE_NUMBER"/sensors_"$SIZE"_trieu_"$CORE_NUMBER"_cores_"$BUFFER".txt"
fi

# # sleep 0.05 second to prevent meature_ram.sh from running before sort.sh
# sleep 0.05

# save sensors info to sensor file
sensors >"$PATH_SENSOR"
echo "%CPU %MEM     ELAPSED" >>"$PATH_SENSOR"

COMMAND="sort -n input/"$SIZE"_trieu.txt -o output/output.txt --parallel=$CORE_NUMBER --buffer-size=$BUFFER"

PID=$(pgrep -x --full "$COMMAND")

# save ram usage info to file while sorting
while [ $(pgrep sort) ]; do
	ps --pid $PID --format pmem,rss,size,vsize --no-headers >>"$PATH_SENSOR"
done

# print an announce that meaturing was finished
echo "Finish RAM meature, $SIZE trieu, paralle=$CORE_NUMBER, buffer=$BUFFER"
