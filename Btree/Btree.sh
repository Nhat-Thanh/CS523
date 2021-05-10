OPERATION=$1

if [ $OPERATION != "insert" -a \
	$OPERATION != "delete" -a \
	$OPERATION != "rank" -a \
	$OPERATION != "between" -a \
	$OPERATION != "update" ]
then
	echo "operation is invalid
	insert, delete, rank, between, update are acceptable"
	exit 0
fi
# INSERT OPERATION
if [ $OPERATION == "insert" ]
then
	/usr/bin/time -v -o ./result/insert/insert_operation_time.txt ./operating_script/insert.sh | \
		./measure_ram.sh $OPERATION

# DELETE OPERATION
elif [ $OPERATION == "delete" ]
then
	/usr/bin/time -v -o "./result/delete/delete_operation_time.txt" ./operating_script/delete.sh | \
		./measure_ram.sh $OPERATION

# RANK OPERATION
elif [ $OPERATION == "rank" ]
then
	/usr/bin/time -v -o "./result/rank/rank_operation_time.txt" ./operating_script/rank.sh | \
		./measure_ram.sh $OPERATION

# BETWEEN OPERATION
elif [ $OPERATION == "between" ]
then

	/usr/bin/time -v -o "./result/between/between_operation_time.txt" ./operating_script/between.sh| \
		./measure_ram.sh $OPERATION
		
# UPDATE OPERATION
elif [ $OPERATION == "update" ]
then
	/usr/bin/time -v -o "./result/update/update_operation_time.txt" ./operating_script/update.sh | \
		./measure_ram.sh $OPERATION
fi
