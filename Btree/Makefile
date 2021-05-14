SIZE ?= 250000000

all: SQL clean database 

SQL:
	g++ create_sql_files.cpp -pthread -o create_sql_files && ./create_sql_files

database:
	bash ./CreateDatabase.sh $(SIZE)

clean:
	rm -f create_sql_files
