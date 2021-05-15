OPERATION=$1
SIZE=$2

rm -f create_sql_files

if [ $OPERATION != "insert" -a \
	$OPERATION != "delete" -a \
	$OPERATION != "rank" -a \
	$OPERATION != "between" -a \
	$OPERATION != "update" -a \
	$OPERATION != "all" ]; then
	echo "operation is invalid
	all, insert, delete, rank, between, update are acceptable"
	exit 0
fi

# INSERT OPERATION
if [ $OPERATION == "all" ]; then
	/usr/bin/time -v -o ./result/$SIZE/insert/insert_operation_time.txt bash ./operating_script/insert.sh $SIZE | bash ./measure_ram.sh insert $SIZE
	echo "finish insert"

	/usr/bin/time -v -o ./result/$SIZE/update/update_operation_time.txt bash ./operating_script/update.sh $SIZE | bash ./measure_ram.sh update $SIZE
	echo "finish update"

	/usr/bin/time -v -o ./result/$SIZE/between/between_operation_time.txt bash ./operating_script/between.sh $SIZE | bash ./measure_ram.sh between $SIZE
	bash ./operating_script/count.sh between $SIZE
	echo "finish between"

	/usr/bin/time -v -o ./result/$SIZE/rank/rank_operation_time.txt bash ./operating_script/rank.sh $SIZE | bash ./measure_ram.sh rank $SIZE
	bash ./operating_script/count.sh rank $SIZE
	echo "finish rank"

	/usr/bin/time -v -o ./result/$SIZE/delete/delete_operation_time.txt bash ./operating_script/delete.sh $SIZE | bash ./measure_ram.sh delete $SIZE
	echo "finish delete"

elif [ $OPERATION == "insert" ]; then
	/usr/bin/time -v -o ./result/$SIZE/insert/insert_operation_time.txt bash ./operating_script/insert.sh $SIZE | bash ./measure_ram.sh insert $SIZE
	echo "finish insert"

# DELETE OPERATION
elif [ $OPERATION == "delete" ]; then
	/usr/bin/time -v -o ./result/$SIZE/sdelete/delete_operation_time.txt bash ./operating_script/delete.sh $SIZE | bash ./measure_ram.sh delete $SIZE
	echo "finish delete"

# RANK OPERATION
elif [ $OPERATION == "rank" ]; then
	/usr/bin/time -v -o ./result/$SIZE/rank/rank_operation_time.txt bash ./operating_script/rank.sh $SIZE | bash ./measure_ram.sh rank $SIZE
	bash ./operating_script/count.sh rank $SIZE
	echo "finish rank"

# BETWEEN OPERATION
elif [ $OPERATION == "between" ]; then
	/usr/bin/time -v -o ./result/$SIZE/between/between_operation_time.txt bash ./operating_script/between.sh $SIZE | bash ./measure_ram.sh between $SIZE
	/bash ./operating_script/count.sh between $SIZE
	echo "finish between"

# UPDATE OPERATION
elif [ $OPERATION == "update" ]; then
	/usr/bin/time -v -o ./result/$SIZE/update/update_operation_time.txt bash ./operating_script/update.sh $SIZE | bash ./measure_ram.sh update $SIZE
	echo "finish update"
fi
exit 0
