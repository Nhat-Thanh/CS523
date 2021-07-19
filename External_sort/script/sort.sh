SIZE=$1
CORE_NUMBER=$2
BUFFER=$3
TEST_MODE=$4

# complexity mode is default

INPUT_FILE="input/"$SIZE"_trieu.txt"

TIME_FILE_PATH="result/complexity/"$SIZE"_trieu/time_"$SIZE"_trieu_"$CORE_NUMBER"_cores_"$BUFFER".txt"

# buffer mode
if [ $TEST_MODE == "buffer" ]; then
	PATH_SENSOR="result/buffer/"$BUFFER"/sensors_"$SIZE"_trieu_"$CORE_NUMBER"_cores_"$BUFFER".txt"
	TIME_FILE_PATH="result/buffer/"$BUFFER"/time_"$SIZE"_trieu_"$CORE_NUMBER"_cores_"$BUFFER".txt"
fi

# parallel mode
if [ $TEST_MODE == "parallel" ]; then
	PATH_SENSOR="result/parallel/"$CORE_NUMBER"/sensors_"$SIZE"_trieu_"$CORE_NUMBER"_cores_"$BUFFER".txt"
	TIME_FILE_PATH="result/parallel/"$CORE_NUMBER"/time_"$SIZE"_trieu_"$CORE_NUMBER"_cores_"$BUFFER".txt"
fi

# meature time
/usr/bin/time -v -o "$TIME_FILE_PATH" \
	sort -n "$INPUT_FILE" -o output/output.txt --parallel=$CORE_NUMBER --buffer-size=$BUFFER |
	script/measure_ram.sh "$SIZE" "$CORE_NUMBER" "$BUFFER" "$TEST_MODE"

# print announce that meaturing was finished
echo "Finish File $SIZE trieu, paralle=$CORE_NUMBER, buffer=$BUFFER"
