OPERATION=$1

if [ $OPERATION != "insert" -a \
	$OPERATION != "delete" -a \
	$OPERATION != "rank" -a \
	$OPERATION != "between" -a \
	$OPERATION != "update" -a \
	$OPERATION != "all" ]
then
	echo "operation is invalid
	all, insert, delete, rank, between, update are acceptable"
	exit 0
fi

# INSERT OPERATION
if [ $OPERATION == "all" ]
then
	/usr/bin/time -v -o ./result/insert/insert_operation_time.txt bash ./operating_script/insert.sh | bash ./measure_ram.sh insert
	echo "finish insert"
	
	/usr/bin/time -v -o ./result/update/update_operation_time.txt bash ./operating_script/update.sh | bash ./measure_ram.sh update
	echo "finish update"
	
	# /usr/bin/time -v -o ./result/between/between_operation_time.txt bash ./operating_script/between.sh | bash ./measure_ram.sh between
	# echo "finish between"
	
	# /usr/bin/time -v -o ./result/rank/rank_operation_time.txt bash ./operating_script/rank.sh | bash ./measure_ram.sh rank
	# echo "finish rank"
	
	# /usr/bin/time -v -o ./result/delete/delete_operation_time.txt bash ./operating_script/delete.sh | bash ./measure_ram.sh delete
	# echo "finish delete"

elif [ $OPERATION == "insert" ]
then
	/usr/bin/time -v -o ./result/insert/insert_operation_time.txt bash ./operating_script/insert.sh | bash ./measure_ram.sh insert
	echo "finish insert"

# DELETE OPERATION
elif [ $OPERATION == "delete" ]
then
	/usr/bin/time -v -o ./result/delete/delete_operation_time.txt bash ./operating_script/delete.sh | bash ./measure_ram.sh delete
	echo "finish delete"

# RANK OPERATION
elif [ $OPERATION == "rank" ]
then
	/usr/bin/time -v -o ./result/rank/rank_operation_time.txt bash ./operating_script/rank.sh | bash ./measure_ram.sh rank
	echo "finish rank"

# BETWEEN OPERATION
elif [ $OPERATION == "between" ]
then
	/usr/bin/time -v -o ./result/between/between_operation_time.txt bash ./operating_script/between.sh | bash ./measure_ram.sh between
	echo "finish between"
		
# UPDATE OPERATION
elif [ $OPERATION == "update" ]
then
	/usr/bin/time -v -o ./result/update/update_operation_time.txt bash ./operating_script/update.sh | bash ./measure_ram.sh update
	echo "finish update"
fi
