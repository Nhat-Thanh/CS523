operation=$1

if [ $operation != "insert" -a \
	$operation != "delete" -a \
	$operation != "rank" -a \
	$operation != "between" -a \
	$operation != "update" ]
then
	echo "operation is invalid
	insert, delete, rank, between, update are acceptable"
	exit()
fi
# INSERT OPERATION
if [ $operation == "insert" ]
then
	time -v -o ./result/insert/insert_operation_time.txt ./operating_script/insert.sh | \
		./measure_ram.sh $operation

# DELETE OPERATION
elif [ $operation == "delete" ]
then
	time -v -o "./result/delete/delete_operation_time.txt" ./operating_script/delete.sh | \
		./measure_ram.sh $operation

# RANK OPERATION
elif [ $operation == "rank" ]
then
	time -v -o "./result/rank/rank_operation_time.txt" ./operating_script/rank.sh $rank_number | \
		./measure_ram.sh $operation

# BETWEEN OPERATION
elif [ $operation == "between" ]
then

	time -v -o "./result/between/between_operation_time.txt" ./operating_script/between.sh| \
		./measure_ram.sh $operation
		
# UPDATE OPERATION
elif [ $operation == "update" ]
then
	time -v -o "./update/update_operation_time.txt" ./operating_script/update.sh | \
		./measure_ram.sh $operation
fi
