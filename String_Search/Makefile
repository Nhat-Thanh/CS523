NUM_FILE ?= 100

auto:
	bash ./init.sh $(NUM_FILE)
	# g++ make_test.cpp -pthread -std=c++2a -o make_test && ./make_test $(NUM_FILE)
	bash ./script/k_TH1.sh $(NUM_FILE); 
	bash ./script/n_TH1.sh $(NUM_FILE);
	bash ./script/n_TH2.sh $(NUM_FILE);
	rm -f ~/output.txt

test_file:
	g++ make_test.cpp -pthread -std=c++2a -o make_test && ./make_test $(NUM_FILE)
	
init:
	bash ./init.sh $(NUM_FILE)
