INDEX=$1
CORE_NUMBER=$2
BUFFER=$3
TEST_CONTENT=$4

# complexity mode is default

INPUT_FILE_PATH="/media/thanh/DATA/External_sort/input/input_"$INDEX"_trieu.txt"

TIME_FILE_PATH="/media/thanh/DATA/External_sort/time_output/complexity/Test_"$INDEX"_trieu/time_output_"$INDEX"_trieu_"$CORE_NUMBER"_cores_"$BUFFER".txt"

OUTPUT_FILE_PATH="/media/thanh/DATA/External_sort/output/output_"$INDEX"_trieu.txt"

PATH_SENSOR="/media/thanh/DATA/External_sort/time_output/complexity/Test_"$INDEX"_trieu/sensors_"$INDEX"_trieu_"$CORE_NUMBER"_cores_"$BUFFER".txt"

# buffer mode
# if
if [ $TEST_CONTENT == "buffer" ]
then 
	PATH_SENSOR="/media/thanh/DATA/External_sort/time_output/buffer/sensors_"$INDEX"_trieu_"$CORE_NUMBER"_cores_"$BUFFER".txt"
	TIME_FILE_PATH="/media/thanh/DATA/External_sort/time_output/buffer/time_output_"$INDEX"_trieu_"$CORE_NUMBER"_cores_"$BUFFER".txt"
fi
# endif


# parallel mode
# if
if [ $TEST_CONTENT == "parallel" ]
then 
	PATH_SENSOR="/media/thanh/DATA/External_sort/time_output/parallel/sensors_"$INDEX"_trieu_"$CORE_NUMBER"_cores_"$BUFFER".txt"
	TIME_FILE_PATH="/media/thanh/DATA/External_sort/time_output/parallel/time_output_"$INDEX"_trieu_"$CORE_NUMBER"_cores_"$BUFFER".txt"
fi
# endif


# save sensors info to sensor file
sensors >> "$PATH_SENSOR"
echo "%CPU %MEM     ELAPSED" >> "$PATH_SENSOR"
# end save info


# meature time
/usr/bin/time -v -o "$TIME_FILE_PATH" \
sort -n "$INPUT_FILE_PATH" -o "$OUTPUT_FILE_PATH" --parallel="$CORE_NUMBER" --buffer-size="$BUFFER" |\
./measure_ram.sh "$INDEX" "$CORE_NUMBER" "$BUFFER" "$TEST_CONTENT"
# end meature


# print announce that meaturing was finished
echo "Finish File "$INDEX" trieu"
