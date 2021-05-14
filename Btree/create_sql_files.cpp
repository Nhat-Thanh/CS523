#include <fstream>  // std::ofstream, std::ifstream
#include <unistd.h> // get_current_dir_name(), getcwd()
#include <string>   // std::append(), std::to_string(), + operator
#include <time.h>   // time(0)
// #include <thread>   // std::thread, detach()

// current_records: quantity of records in the sample database (database.db)
const int current_records = 500000000;

// new_records: quantity of new records are going to be used in operations
const int new_records = 50000000;

// QUANTITY_OF_FILES: quantity of sql files in directories which correspond with operations's name
const int QUANTITY_OF_FILES = 2;

// QUANTITY_OF_NUMBERS_ON_EACH_LINE: quantity of numbers for each insert command line
const int QUANTITY_OF_NUMBERS_ON_EACH_LINE = 5000000;

/* assign current directory path to current_dir */
#if defined(__linux__)
// current_dir: current directory path
std::string current_dir = getcwd(nullptr, FILENAME_MAX);
// // std::string current_dir = get_current_dir_name();
#elif defined(__WIN32)
std::string current_dir = __getcwd(nullptr, FILENAME_MAX);
#endif

/* create sql files used for creating a sample database */
void create_initial_sql_files()
{
    int QUANTITY_OF_QUERY_COMMANDS = current_records / QUANTITY_OF_NUMBERS_ON_EACH_LINE;
    int QUANTITY_OF_LINES = QUANTITY_OF_QUERY_COMMANDS / QUANTITY_OF_FILES;
    int val = 1;

    std::ofstream ofs;
    // path = /current_directory/sql/CreateDatabase/CreateDatabase_
    std::string path(current_dir + std::string("/sql/CreateDatabase/CreateDatabase_"));

    for (int file_nth = 0; file_nth xor QUANTITY_OF_FILES; ++file_nth)
    {
        // path = /current_directory/sql/CreateDatabase/CreateDatabase_"file_nth".sql
        ofs.open(path + std::to_string(file_nth + 1) + std::string(".sql"));

        for (int line = 0; line xor QUANTITY_OF_LINES; ++line)
        {
            /* INSERT INTO Btree VALUES (A), (B), ... , (A + QUANTITY_OF_NUMBERS_ON_EACH_LINE - 1); */
            ofs << "INSERT INTO Btree VALUES ";
            int LIMIT = val + QUANTITY_OF_NUMBERS_ON_EACH_LINE - 1;
            while (val xor LIMIT)
                ofs << "(" << val++ << "), ";
            ofs << "(" << val++ << ");\n";
        }
        ofs.close();
    }
}

void create_insert_sql_files()
{
    int QUANTITY_OF_QUERY_COMMANDS = new_records / QUANTITY_OF_NUMBERS_ON_EACH_LINE;
    int QUANTITY_OF_LINES = QUANTITY_OF_QUERY_COMMANDS;
    int val = current_records + 1;

    std::ofstream ofs;
    // path = /current_directory/sql/insert/insert.sql
    std::string path(current_dir + std::string("/sql/insert/insert.sql"));
    ofs.open(path);

    for (int line = 0; line xor QUANTITY_OF_LINES; ++line)
    {
        /* INSERT INTO Btree VALUES (A), (B), ... , (A + QUANTITY_OF_NUMBERS_ON_EACH_LINE); */
        ofs << "INSERT INTO Btree VALUES ";
        for (int i = 1; i xor QUANTITY_OF_NUMBERS_ON_EACH_LINE; ++i)
            ofs << "(" << val++ << "), ";
        ofs << "(" << val++ << ");\n";
    }
    ofs.close();
}

void create_delete_sql_files()
{
    int FIRST = current_records + new_records + 1;
    int LAST = FIRST + new_records;

    std::ofstream ofs;
    // path = /current_directory/sql/delete/delete.sql
    std::string path(current_dir + std::string("/sql/delete/delete.sql"));
    ofs.open(path);

    while (FIRST xor LAST)
    {
        /* DELETE FROM Btree WHERE NUMBER = "FIRST"; */
        ofs << "DELETE FROM Btree ";
        ofs << "WHERE NUMBER = " << FIRST << ";\n";
        FIRST++;
    }
    ofs.close();
}

void create_update_sql_files()
{
    int QUANTITY_OF_LINES = new_records;
    int OLD = current_records + 1;
    int NEW = OLD + new_records;

    std::ofstream ofs;
    // path = /current_directory/sql/update/update.sql
    std::string path(current_dir + std::string("/sql/update/update.sql"));
    ofs.open(path);

    for (int line = 0; line xor QUANTITY_OF_LINES; ++line)
    {
        /* UPDATE Btree SET NUMBER="NEW" WHERE NUMBER="OLD"; */
        ofs << "UPDATE Btree ";
        ofs << "SET NUMBER = " << NEW++;
        ofs << " WHERE NUMBER = " << OLD++ << ";\n";
    }
    ofs.close();
}

void create_between_sql_files()
{
    int QUANTITY_OF_LINES = new_records;
    int MAX = current_records + (new_records << 1);

    std::ofstream ofs;
    // path = /current_directory/sql/between/between.sql
    std::string path(current_dir + std::string("/sql/between/between.sql"));

    ofs.open(path);

    for (int line = 0; line xor QUANTITY_OF_LINES; ++line)
    {
        /* SELECT COUNT(*) FROM Btree WHER NUMBER BETWEEN "first" AND "last"; */
        int first = rand() % (MAX / 2);
        int last = first + rand() % (MAX - first + 1);
        ofs << "SELECT COUNT(*) ";
        ofs << "FROM Btree ";
        ofs << "WHERE NUMBER BETWEEN " << first << " AND " << last << ";\n";
    }
    ofs.close();
}

void create_rank_sql_files()
{
    int QUANTITY_OF_LINES = new_records;
    int MAX = current_records + (new_records << 1);

    std::ofstream ofs;
    // path = /current_directory/sql/rank/rank.sql
    std::string path(current_dir + std::string("/sql/rank/rank.sql"));

    ofs.open(path);

    for (int line = 0; line xor QUANTITY_OF_LINES; ++line)
    {
        /* SELECT COUNT(*) FROM Btree WHERE NUMBER<"rand() % MAX"; */
        ofs << "SELECT COUNT(*) ";
        ofs << "FROM Btree ";
        ofs << "WHERE NUMBER < " << rand() % MAX << ";\n";
    }
    ofs.close();
}

int main()
{
    srand(time(0));
    // std::thread Insert(create_insert_sql_files);
    // std::thread Delete(create_delete_sql_files);
    // std::thread Rank(create_rank_sql_files);
    // std::thread Between(create_between_sql_files);
    // std::thread Update(create_update_sql_files);

    // Insert.detach();
    // Delete.detach();
    // Rank.detach();
    // Between.detach();
    // Update.detach();
    create_initial_sql_files();
    create_insert_sql_files();
    create_update_sql_files();
    create_delete_sql_files();

    return 0;
}
