NUM_FILE ?= 100

auto:
	bash ./init.sh $(NUM_FILE)
	g++ make_test.cpp -pthread -std=c++2a -o make_test && ./make_test $(NUM_FILE)
	@echo "testing param n - TH1"
	@i=0; \
	while [ $${i} -lt "$(NUM_FILE)" ]; do \
		j=0; \
		while [ $${j} -lt "$(NUM_FILE)" ]; do \
			bash grep.sh test_$$(( 2000 + 2000 * $${j} )) TH1 n $(expr 505000 + 5000 * $i); \
			j=$(expr $j + 1); \
		done; \
		i=$(expr $i + 1); \
	done; \
	true;
	@echo "finish testing param n - TH1"
	
	@echo "testing param k - TH1"
	@i=0; \
	while [ $${i} -lt "$(NUM_FILE)" ]; do \
		j=0; \
		while [ $${j} -lt "$(NUM_FILE)" ]; do \
			bash grep.sh test_$$(( 2000 + 2000 * $${j} )) TH1 k $(expr 100 + 100 * $i); \
			j=$(expr $j + 1; \
		done; \
		i=$(expr $i + 1); \
	done; \
	true;
	@echo "finish testing param k - TH1"
	
	@echo "testing param n - TH2"
	@i=0; \
	while [ $${i} -lt "$(NUM_FILE)" ]; do \
		j=0; \
		while [ $${j} -lt "$(NUM_FILE)" ]; do \
			bash grep.sh test_$$(( 2000 + 2000 * $${j} )) TH1 n $(expr 10000000 + 10000000 * $i); \
			j=(expr $j + 1); \
		done; \
		i=$(expr $i + 1); \
	done; \
	true;
	@echo "finish testing param n - TH2"
	rm ./output.txt

test_file:
	g++ make_test.cpp -pthread -std=c++2a -o make_test && ./make_test $(NUM_FILE)
	
init:
	bash ./init.sh $(NUM_FILE)
