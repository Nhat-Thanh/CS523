all: SQL database

SQL:
	g++ create_sql_files.cpp -pthread -o create_sql_files && ./create_sql_files

database:
	bash ./CreateDatabase.sh

clean:
	rm create_sql_files
