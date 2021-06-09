NUM_FILE ?= 50

auto:
	bash ./init.sh $(NUM_FILE)
	g++ make_test.cpp -pthread -std=c++2a -o make_test && ./make_test $(NUM_FILE)
	bash ./script/k_TH1.sh $(NUM_FILE); 
	bash ./script/n_TH1.sh $(NUM_FILE);
	bash ./script/n_TH2.sh $(NUM_FILE);
	rm -f ~/output.txt
	g++ make_csv.cpp -pthread -std=c++2a -o make_csv && ./make_csv $(NUM_FILE)
	bash ./remove_end.sh $(NUM_FILE)

test_file:
	g++ make_test.cpp -pthread -std=c++2a -o make_test && ./make_test $(NUM_FILE)
	
csv:
	g++ make_csv.cpp -pthread -std=c++2a -o make_csv && ./make_csv $(NUM_FILE)

remove_end:
	bash ./remove_end.sh $(NUM_FILE)
	
init:
	bash ./init.sh $(NUM_FILE)
