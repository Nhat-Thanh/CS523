data_file_path="../data/delete_data.txt"
database_file_path="../database.db"                                               
                                                                                                           
n=1000;                                                                                   
echo "deleting $n elements from Btree"                                                                    
                                                                                                                  
line=(`cat $data_file_path`);
i=0                                                                                                    
while [ $i -lt "$n" ]                                                                                           
do                                                                                                         
        sqlite3 $database_file_path "DELETE FROM Btree WHERE NUMBER = ${line[$i]};"
        i=$(($i+1))                                                                                               
done                                                                                                            
                                                                                                            
echo "finish delete operation"
