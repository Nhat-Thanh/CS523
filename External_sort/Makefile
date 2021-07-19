auto:
	g++ src/make_input_files.cpp -pthread -o bin/make_input_files
	bin/make_input_files
	bash script/measure_complexity.sh
	bash script/measure_parallel.sh
	bash script/measure_buffer.sh
	g++ src/make_csv.cpp  -o bin/make_csv
	bin/make_csv
