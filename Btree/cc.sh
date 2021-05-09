line=(`sed -n '1000001,1009106 p' ./data/data.txt`)
i=0

while [ $i -lt 9106 ]
do
	sqlite3 ./database.db "DELETE FROM Btree WHERE NUMBER = ${line[$i]}"
	i=$(($i+1))
done

echo "finish"
