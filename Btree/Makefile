SIZE ?= 250000000

all: SQL database

auto:
	bash ./CreateDatabase.sh 250000000
	bash Btree.sh all 250000000
	rm -f database_250000000.db
	
	bash ./CreateDatabase.sh 500000000
	bash Btree.sh all 500000000
	rm -f database_500000000.db

	bash ./CreateDatabase.sh 750000000
	bash Btree.sh all 750000000
	rm -f database_750000000.db

	bash ./CreateDatabase.sh 1000000000
	bash Btree.sh all 1000000000
	rm -f database_1000000000.db

	bash ./CreateDatabase.sh 1250000000
	bash Btree.sh all 1250000000
	rm -f database_1250000000.db
	
	bash ./CreateDatabase.sh 1500000000
	bash Btree.sh all 1500000000
	rm -f database_1500000000.db

	bash ./CreateDatabase.sh 1750000000
	bash Btree.sh all 1750000000
	rm -f database_1750000000.db

	bash ./CreateDatabase.sh 2000000000
	bash Btree.sh all 2000000000
	rm -f database_2000000000.db

SQL:
	g++ create_sql_files.cpp -pthread -o create_sql_files && ./create_sql_files
	rm -f create_sql_files

database:
	bash ./CreateDatabase.sh $(SIZE)