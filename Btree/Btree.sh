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
	I=1000
	while [ $I -lt 9001 ]
	do
		/usr/bin/time -v -o ./result/insert/$I/insert_operation_time.txt bash ./operating_script/insert.sh $I | ./measure_ram.sh $OPERATION $I
		I=$(($I+1000))
	done

# DELETE OPERATION
elif [ $OPERATION == "delete" ]
then

	I=1000
	while [ $I -lt 9001 ]
	do
		/usr/bin/time -v -o ./result/delete/$I/delete_operation_time.txt bash ./operating_script/delete.sh | ./measure_ram.sh $OPERATION $I
		I=$(($I+1000))
	done
	

# RANK OPERATION
elif [ $OPERATION == "rank" ]
then
	I=1000
	while [ $I -lt 9001 ]
	do
		/usr/bin/time -v -o ./result/rank/$I/rank_operation_time.txt bash ./operating_script/rank.sh $I | ./measure_ram.sh $OPERATION $I
		I=$(($I+1000))
	done
	
# BETWEEN OPERATION
elif [ $OPERATION == "between" ]
then
	I=1000
	while [ $I -lt 9001 ]
	do
		/usr/bin/time -v -o ./result/between/$I/between_operation_time.txt bash ./operating_script/between.sh $I | ./measure_ram.sh $OPERATION $I
		I=$(($I+1000))
	done
		
# UPDATE OPERATION
elif [ $OPERATION == "update" ]
then
	I=1000
	while [ $I -lt 9001 ]
	do
		/usr/bin/time -v -o ./result/update/$I/update_operation_time.txt bash ./operating_script/update.sh $I | ./measure_ram.sh $OPERATION $I
		I=$(($I+1000))
	done
fi
