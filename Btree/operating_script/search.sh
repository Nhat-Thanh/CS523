SIZE=$1
sqlite3 ./database_$SIZE.db < ./sql/search/$SIZE/search.sql