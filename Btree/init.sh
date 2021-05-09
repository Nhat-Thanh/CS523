echo "Create essential directories"
mkdir data operation_script result
mkdir ./result/insert \
        ./result/delete \
        ./result/rank \
        ./result/update \
        ./result/between

echo "compile .cpp file and execute"
g++ create_data_file.cpp -o create_data_file && ./create_data_file

./CreateDatabase.sh
