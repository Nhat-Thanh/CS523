echo "compile .cpp file and execute"
g++ create_data_file.cpp -o create_data_file && ./create_data_file

./CreateDatabase.sh
