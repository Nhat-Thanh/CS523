data_file_path="./data/insert_data.txt"

database_file_path="./database.db"                                               
                                                                                                                                                                                                              n=1000;                                                                                   
echo "inserting $n elements into Btree"                                                                    
                                                                                                                  
line=(`cat $data_file_path`)                                                
i=0                                                                                                    
while [ $i -lt "$n" ]                                                                                           
do
        sqlite3 "$database_file_path" "INSERT INTO Btree VALUES (${line[$i]});"
        i=$(($i+1))                                                                                               
done                                                                                                                   
echo "finish insert operation"
