INDEX=$1
CORE_NUMBER=$2
BUFFER=$3
TEST_CONTENT=$4

PATH_SENSOR="/media/thanh/DATA/External_sort/time_output/complexity/Test_"$INDEX"_trieu/sensors_"$INDEX"_trieu_"$CORE_NUMBER"_cores_"$BUFFER".txt"

# buffer mode
# if
if [ $TEST_CONTENT == "buffer" ]
then 
	PATH_SENSOR="/media/thanh/DATA/External_sort/time_output/buffer/sensors_"$INDEX"_trieu_"$CORE_NUMBER"_cores_"$BUFFER".txt"
fi
# end if


# parallel mode
# if
if [ $TEST_CONTENT == "parallel" ]
then 
	PATH_SENSOR="/media/thanh/DATA/External_sort/time_output/parallel/sensors_"$INDEX"_trieu_"$CORE_NUMBER"_cores_"$BUFFER".txt"
fi
# endif


# sleep 0.05 second to prevent meature_ram.sh from running before sort.sh
sleep 0.05

# save ram usage info to file while sorting
while [ $(pgrep sort) ]
do
	ps --pid $(pgrep sort) --format pcpu,pmem,etime --no-headers >> "$PATH_SENSOR"
	sleep 10s
done
# end saving


# print an announce that meaturing was finished
echo "Finish RAM meature "$BUFFER""
