TREE_TYPE ?= "lsm"
OP ?= "open"
START ?= 100000
END ?= 10000000
DB_SIZE ?= 10000000
AMOUNT_FOR_OP ?= 100000
STEP ?= 100000

# Run everything automatically
auto:
	#================================ Create folders ================================
	bash script/init.sh $(START) $(END) $(STEP)

	#=============================== Build cpp files ===============================
	g++ src/create_btree_table.cpp -lwiredtiger -o ./bin/create_btree_table -L/usr/local/lib -Wl,-R/usr/local/lib 
	g++ src/create_lsm_table.cpp -lwiredtiger -o ./bin/create_lsm_table -L/usr/local/lib -Wl,-R/usr/local/lib 
	g++ src/insert.cpp -lwiredtiger -o ./bin/insert -L/usr/local/lib -Wl,-R/usr/local/lib 
	g++ src/open.cpp -lwiredtiger -o ./bin/open -L/usr/local/lib -Wl,-R/usr/local/lib 
	g++ src/search.cpp -lwiredtiger -o ./bin/search -L/usr/local/lib -Wl,-R/usr/local/lib 
	g++ src/update.cpp -lwiredtiger -o ./bin/update -L/usr/local/lib -Wl,-R/usr/local/lib 
	g++ src/delete.cpp -lwiredtiger -o ./bin/delete -L/usr/local/lib -Wl,-R/usr/local/lib
	g++ src/print_db.cpp -lwiredtiger -o ./bin/print_db -L/usr/local/lib -Wl,-R/usr/local/lib 
	g++ src/compact.cpp -lwiredtiger -o ./bin/compact -L/usr/local/lib -Wl,-R/usr/local/lib 
	g++ src/check_and_fix.cpp -o ./bin/check_and_fix
	g++ src/make_csv.cpp -o ./bin/make_csv

	#=============================== Create Databases ===============================
	bash script/create_database.sh lsm $(START) $(END) $(STEP)
	bash script/create_database.sh btree $(START) $(END) $(STEP)

	#============================= Run LSM tree operations ===========================\
	bash script/open.sh lsm $(START) $(END) $(AMOUNT_FOR_OP) $(STEP)
	bash script/insert.sh lsm $(START) $(END) $(AMOUNT_FOR_OP) $(STEP)
	bash script/search.sh lsm $(START) $(END) $(AMOUNT_FOR_OP) $(STEP)
	bash script/update.sh lsm $(START) $(END) $(AMOUNT_FOR_OP) $(STEP)
	bash script/delete.sh lsm $(START) $(END) $(AMOUNT_FOR_OP) $(STEP)

	#============================ Run Btree operations ==========================
	bash script/open.sh btree $(START) $(END) $(AMOUNT_FOR_OP) $(STEP)
	bash script/insert.sh btree $(START) $(END) $(AMOUNT_FOR_OP) $(STEP)
	bash script/search.sh btree $(START) $(END) $(AMOUNT_FOR_OP) $(STEP)
	bash script/update.sh btree $(START) $(END) $(AMOUNT_FOR_OP) $(STEP)
	bash script/delete.sh btree $(START) $(END) $(AMOUNT_FOR_OP) $(STEP)

	#============================ Check and fix errors ==========================
	bin/check_and_fix $(START) $(END) $(STEP)

	#============================ Make all csv files ==========================
	bin/make_csv lsm create_database $(START) $(END) $(STEP)
	bin/make_csv lsm open $(START) $(END) $(STEP)
	bin/make_csv lsm insert $(START) $(END) $(STEP)
	bin/make_csv lsm search $(START) $(END) $(STEP)
	bin/make_csv lsm update $(START) $(END) $(STEP)
	bin/make_csv lsm delete $(START) $(END) $(STEP)

	bin/make_csv btree create_database $(START) $(END) $(STEP)
	bin/make_csv btree open $(START) $(END) $(STEP)
	bin/make_csv btree insert $(START) $(END) $(STEP)
	bin/make_csv btree search $(START) $(END) $(STEP)
	bin/make_csv btree update $(START) $(END) $(STEP)
	bin/make_csv btree delete $(START) $(END) $(STEP)

# Create result, btree_db, lsm_db, and bin directory
init:
	bash script/init.sh $(START) $(END) $(STEP)

# Build all cpp files in src directory
build_all_cpp:
	g++ src/create_btree_table.cpp -lwiredtiger -o ./bin/create_btree_table -L/usr/local/lib -Wl,-R/usr/local/lib 
	g++ src/create_lsm_table.cpp -lwiredtiger -o ./bin/create_lsm_table -L/usr/local/lib -Wl,-R/usr/local/lib 
	g++ src/insert.cpp -lwiredtiger -o ./bin/insert -L/usr/local/lib -Wl,-R/usr/local/lib 
	g++ src/open.cpp -lwiredtiger -o ./bin/open -L/usr/local/lib -Wl,-R/usr/local/lib 
	g++ src/search.cpp -lwiredtiger -o ./bin/search -L/usr/local/lib -Wl,-R/usr/local/lib 
	g++ src/update.cpp -lwiredtiger -o ./bin/update -L/usr/local/lib -Wl,-R/usr/local/lib 
	g++ src/delete.cpp -lwiredtiger -o ./bin/delete -L/usr/local/lib -Wl,-R/usr/local/lib
	g++ src/print_db.cpp -lwiredtiger -o ./bin/print_db -L/usr/local/lib -Wl,-R/usr/local/lib 
	g++ src/compact.cpp -lwiredtiger -o ./bin/compact -L/usr/local/lib -Wl,-R/usr/local/lib 
	g++ src/check_and_fix.cpp -o bin/check_and_fix
	g++ src/make_csv.cpp -o bin/make_csv

# Build a cpp file whose name is the same as $(OP)
build_cpp:
	g++ src/$(OP).cpp -lwiredtiger -o ./bin/$(OP) -L/usr/local/lib -Wl,-R/usr/local/lib

# Create a database whose tree type is $(TREE_TYPE) and has $(DB_SIZE) records
a_database:
	/usr/bin/time -v -o result/$(TREE_TYPE)/create_database/$(DB_SIZE)/time.txt \
        bin/create_$(TREE_TYPE)_table $(DB_SIZE) $(TREE_TYPE)_db/$(DB_SIZE) | \
		bash script/measure_swinfo.sh $(TREE_TYPE) create_database $(DB_SIZE)

# Create databases using $(TREE_TYPE)
databases:
	bash script/create_database.sh $(TREE_TYPE) $(START) $(END) $(STEP)

# Create all databases for testing
all_database:
	bash script/create_database.sh btree $(START) $(END) $(STEP)
	bash script/create_database.sh lsm $(START) $(END) $(STEP)

# Test the $(OP) operation on all databases
test:
	bash script/$(OP).sh $(TREE_TYPE) $(START) $(END) $(AMOUNT_FOR_OP) $(STEP)

# Run all operations on Btree databases
test_btree:
	bash script/open.sh btree $(START) $(END) $(AMOUNT_FOR_OP) $(STEP)
	bash script/insert.sh btree $(START) $(END) $(AMOUNT_FOR_OP) $(STEP)
	bash script/search.sh btree $(START) $(END) $(AMOUNT_FOR_OP) $(STEP)
	bash script/update.sh btree $(START) $(END) $(AMOUNT_FOR_OP) $(STEP)
	bash script/delete.sh btree $(START) $(END) $(AMOUNT_FOR_OP) $(STEP)

# Run all operations on lsm tree databases
test_lsm:
	bash script/open.sh lsm $(START) $(END) $(AMOUNT_FOR_OP) $(STEP)
	bash script/insert.sh lsm $(START) $(END) $(AMOUNT_FOR_OP) $(STEP)
	bash script/search.sh lsm $(START) $(END) $(AMOUNT_FOR_OP) $(STEP)
	bash script/update.sh lsm $(START) $(END) $(AMOUNT_FOR_OP) $(STEP)
	bash script/delete.sh lsm $(START) $(END) $(AMOUNT_FOR_OP) $(STEP)

# Check results and fix errors by running failing test cases again
check_and_fix:
	bin/check_and_fix $(START) $(END) $(STEP)

# Fix a result of $(OP) on a database which has $(DB_SIZE) records
fix:
	/usr/bin/time -v -o result/$(TREE_TYPE)/$(OP)/$(DB_SIZE)/time.txt \
	bin/$(OP) $(TREE_TYPE) $(DB_SIZE) $(TREE_TYPE)_db/$(DB_SIZE) $(AMOUNT_FOR_OP) | \
	bash script/measure_swinfo.sh $(TREE_TYPE) $(OP) $(DB_SIZE) $(AMOUNT_FOR_OP)

# Fix a result of creating database operation
fix_create_database:
	/usr/bin/time -v -o result/$(TREE_TYPE)/create_database/$(DB_SIZE)/time.txt \
        bin/create_$(TREE_TYPE)_table $(DB_SIZE) $(TREE_TYPE)_db/$(DB_SIZE) | \
		bash script/measure_swinfo.sh $(TREE_TYPE) create_database $(DB_SIZE)

# remove btree_db, lsm_db and bin directory
clean_all:
	rm -rf btree_db
	rm -rf lsm_db
	rm -rf bin

# Make csv files from tested results
csv:
	bin/make_csv lsm create_database $(START) $(END) $(STEP)
	bin/make_csv lsm open $(START) $(END) $(STEP)
	bin/make_csv lsm insert $(START) $(END) $(STEP)
	bin/make_csv lsm search $(START) $(END) $(STEP)
	bin/make_csv lsm update $(START) $(END) $(STEP)
	bin/make_csv lsm delete $(START) $(END) $(STEP)

	bin/make_csv btree create_database $(START) $(END) $(STEP)
	bin/make_csv btree open $(START) $(END) $(STEP)
	bin/make_csv btree insert $(START) $(END) $(STEP)
	bin/make_csv btree search $(START) $(END) $(STEP)
	bin/make_csv btree update $(START) $(END) $(STEP)
	bin/make_csv btree delete $(START) $(END) $(STEP)

# Merge lsm tree databases if they're possible
compact:
	bash script/compact.sh $(START) $(END) $(STEP)
	
# Print all records on a database having $(DB_SIZE) records
print_db:
	bin/print_db $(TREE_TYPE) $(TREE_TYPE)_db/$(DB_SIZE)
