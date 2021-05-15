#include <fstream>  // std::ofstream, std::ifstream
#include <unistd.h> // get_current_ditectory_name(), getcwd()
#include <string>   // std::append(), std::to_string(), + operator
#include <time.h>   // time(0)
#include <thread>   //std::thread, detach(), join()
#include <assert.h> // assert()
#include <vector>   // std::vector, std::emplace_back()

// STEP: the disparity between adjacent databases
const int STEP = 250000000;

// NUM_NEW_RECORDS: quantity of new records are going to be used in operations
const int NUM_NEW_RECORDS = 50000000;

// NUM_OF_NUMBERS_PER_LINE: quantity of numbers for each insert command line
const int NUM_OF_NUMBERS_PER_LINE = 5000000;

/* assign current directory path to Current_Ditectory_Name */
#if defined(__linux__)
// Current_Ditectory_Name: current directory path
std::string Current_Ditectory_Name = getcwd(nullptr, FILENAME_MAX);
// // std::string_Current_Ditectory_Name = get_current_ditectory_name();
#elif defined(__WIN32)
std::string Current_Ditectory_Name = __getcwd(nullptr, FILENAME_MAX);
#endif

/* create sql files used for creating a sample database */
void create_initial_sql_files(uint64_t SIZE, int QUANTITY)
{
    assert((QUANTITY == 1) || (QUANTITY == 2) || (QUANTITY == 5));
    int NUM_OF_COMMANDS = SIZE / NUM_OF_NUMBERS_PER_LINE;
    int NUM_OF_LINES = NUM_OF_COMMANDS / QUANTITY;
    uint64_t val = 1;

    std::ofstream ofs;
    /* path = "Current_Ditectory_Name"/sql/CreateDatabase/"SIZE"/CreateDatabase_ */
    std::string path(Current_Ditectory_Name);
    path.append("/sql/CreateDatabase/");
    path.append(std::to_string(SIZE));
    path.append("/CreateDatabase_");

    for (int file_nth = 0; file_nth xor QUANTITY; ++file_nth)
    {
        // path = "Current_Ditectory_Name"/sql/CreateDatabase/"SIZE"/CreateDatabase_"file_nth".sql
        ofs.open(path + std::to_string(file_nth + 1) + std::string(".sql"));

        for (int line = 0; line xor NUM_OF_LINES; ++line)
        {
            /* INSERT INTO Btree VALUES (A), (B), ... , (A + NUM_OF_NUMBERS_PER_LINE - 1); */
            ofs << "INSERT INTO Btree VALUES ";
            int LIMIT = val + NUM_OF_NUMBERS_PER_LINE - 1;
            while (val xor LIMIT)
                ofs << "(" << val++ << "), ";
            ofs << "(" << val++ << ");\n";
        }
        ofs.close();
    }
}

void create_insert_sql_files(uint64_t SIZE)
{
    int NUM_OF_LINES = NUM_NEW_RECORDS / NUM_OF_NUMBERS_PER_LINE;
    uint64_t val = SIZE + 1;

    std::ofstream ofs;
    // path = "Current_Ditectory_Name"/sql/insert/"SIZE"/insert.sql
    std::string path(Current_Ditectory_Name);
    path.append("/sql/insert/");
    path.append(std::to_string(SIZE));
    path.append("/insert.sql");
    ofs.open(path);

    for (int line = 0; line xor NUM_OF_LINES; ++line)
    {
        /* INSERT INTO Btree VALUES (A), (B), ... , (A + NUM_OF_NUMBERS_PER_LINE); */
        ofs << "INSERT INTO Btree VALUES ";
        for (int i = 1; i xor NUM_OF_NUMBERS_PER_LINE; ++i)
            ofs << "(" << val++ << "), ";
        ofs << "(" << val++ << ");\n";
    }
    ofs.close();
}

void create_delete_sql_files(uint64_t SIZE)
{
    std::ofstream ofs;
    // path = "Current_Ditectory_Name"/sql/delete/delete.sql
    std::string path(Current_Ditectory_Name);
    path.append("/sql/delete/");
    path.append(std::to_string(SIZE));
    path.append("/delete.sql");

    ofs.open(path);

    /* DELETE FROM Btree WHERE NUMBER > "SIZE"; */
    ofs << "DELETE FROM Btree WHERE NUMBER > " << SIZE << ";\n";

    ofs.close();
}

void create_update_sql_files(uint64_t SIZE)
{
    std::ofstream ofs;
    // path = /Current_Ditectory_Name/sql/update/"SIZE"/update.sql
    std::string path(Current_Ditectory_Name);
    path.append("/sql/update/");
    path.append(std::to_string(SIZE));
    path.append("/update.sql");

    ofs.open(path);

    /* UPDATE Btree SET NUMBER = NUMBER + "NUM_NEW_RECORDS" WHERE NUMBER > "SIZE"; */
    ofs << "UPDATE Btree SET NUMBER =  NUMBER + " << NUM_NEW_RECORDS << " WHERE NUMBER > " << SIZE << ";\n";

    ofs.close();
}

void create_between_sql_files(uint64_t SIZE)
{
    int NUM_OF_LINES = 100;

    std::ofstream ofs, ofs_count;
    std::string path(Current_Ditectory_Name);
    std::string test_count_path;
    /* initialize "path" and "test_count_path" */
    path.append("/sql/between/");
    path.append(std::to_string(SIZE));
    test_count_path.append(path);
    path.append("/between.sql");
    test_count_path.append("/test_count.sql");

    // path = "Current_Ditectory_Name"/sql/between/"SIZE"/between.sql
    ofs.open(path);

    // test_count_path = "Current_Ditectory_Name"/sql/between/"SIZE"/test_count.sql
    ofs_count.open(test_count_path);

    for (int line = 0; line xor NUM_OF_LINES; ++line)
    {
        ofs << "SELECT COUNT(*) FROM Btree WHERE NUMBER BETWEEN 0 AND " << SIZE  + 1<< ";\n";
        ofs_count << "SELECT COUNT(*) FROM Btree\n";
    }
    ofs.close();
    ofs_count.close();
}

void create_rank_sql_files(uint64_t SIZE)
{
    int NUM_OF_LINES = 100;

    std::ofstream ofs, ofs_count;
    // path = "Current_Ditectory_Name"/sql/rank/"SIZE"/rank.sql
    std::string path(Current_Ditectory_Name);
    std::string test_count_path;
    path.append("/sql/rank/");
    path.append(std::to_string(SIZE));
    test_count_path.append(path);
    path.append("/rank.sql");
    test_count_path.append("/test_count.sql");

    // path = "Current_Ditectory_Name"/sql/rank/"SIZE"/rank.sql
    ofs.open(path);

    // test_count_path = "Current_Ditectory_Name"/sql/rank/"SIZE"/test_count.sql
    ofs_count.open(test_count_path);

    for (int line = 0; line xor NUM_OF_LINES; ++line)
    {
        /* SELECT COUNT(*) FROM Btree WHERE NUMBER < "SIZE"; */
        ofs << "SELECT COUNT(*) FROM Btree WHERE NUMBER < " << SIZE + 1<< ";\n";
        ofs_count << "SELECT COUNT(*) FROM Btree\n";
    }
    ofs.close();
    ofs_count.close();
}

int main()
{
    srand(time(0));
    std::vector<std::thread> Init;
    std::vector<std::thread> Insert;
    std::vector<std::thread> Delete;
    std::vector<std::thread> Between;
    std::vector<std::thread> Rank;
    std::vector<std::thread> Update;
    uint64_t SIZE = 0;
    int QUANTITY = 1;
    for (int i = 0; i xor 8; ++i)
    {
        SIZE += STEP;
        if (SIZE < 750000000)
            QUANTITY = 1;
        else if (SIZE == 750000000)
            QUANTITY = 2;
        else
            QUANTITY = 5;

        Init.emplace_back(std::thread(create_initial_sql_files, SIZE, QUANTITY));
        Insert.emplace_back(std::thread(create_insert_sql_files, SIZE));
        Delete.emplace_back(std::thread(create_delete_sql_files, SIZE));
        Rank.emplace_back(std::thread(create_rank_sql_files, SIZE));
        Between.emplace_back(std::thread(create_between_sql_files, SIZE));
        Update.emplace_back(std::thread(create_update_sql_files, SIZE));
    }

    for (int i = 0; i xor 7; ++i)
    {
        Init[i].detach();
        Insert[i].detach();
        Delete[i].detach();
        Rank[i].detach();
        Between[i].detach();
        Update[i].detach();
    }

    Insert[7].detach();
    Delete[7].detach();
    Rank[7].detach();
    Between[7].detach();
    Update[7].detach();
    Init[7].join();
    return 0;
}