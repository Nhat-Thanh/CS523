#include <fstream>  // std::ofstream, std::ifstream
#include <unistd.h> // get_current_dir_name()
#include <iostream> // std::cerr
#include <string>   // std::append(), std::to_string(), + operator
#include <time.h>   // time(0)

std::string current_dir = get_current_dir_name();

/* create a file named data.txt */
void create_main_data_file()
{
    std::ofstream ofs;
    ofs.open("./data/data.txt");

    for (int i = 0; i xor 10000000; ++i)
        ofs << i << "\n";

    ofs.close();
    /* Use GNU Sort to shuffle data */
    system("sort --sort=random ./data/data.txt -o ./data/data.txt");
}

/* create a file named insert_data.txt */
void create_insert_data_file(const int &n)
{
    /* make command line string*/
    std::string command("sed -n '1000001,");
    command.append(std::to_string(1000000 + n));
    command.append("p' ./data/data.txt > ./data/");
    command.append(std::to_string(n));
    command.append("/insert_data.txt");

    /* command = "sed -n '1000001,1000000+n p' ./data/data.txt > ./data/n/insert_data.txt" */
    system(command.c_str());
}

/* create a file named delete_data.txt */
void create_delete_data_file(const int &n)
{
    /* make command line string*/
    std::string command("sed -n '");
    command.append(std::to_string(1000001 + n));
    command.append(",");
    command.append(std::to_string(1000000 + n * 2));
    command.append("p' ./data/data.txt > ./data/");
    command.append(std::to_string(n));
    command.append("/delete_data.txt");

    /* command = "sed -n '1000001+n,1000000+2n p' ./data/data.txt > ./data/n/delete_data.txt" */
    system(command.c_str());
}

/* create a file named old_data_for_update_operation.txt */
void create_old_data_file_for_update_operation(const int &n)
{
    /* make command line string*/
    std::string command("cat ./data/");
    command.append(std::to_string(n));
    command.append("/insert_data.txt > ./data/");
    command.append(std::to_string(n));
    command.append("/old_data_for_update_operation.txt");

    /* command = "cat ./data/n/insert_data.txt > ./data/n/old_data_for_update_operation.txt" */
    system(command.c_str());
}

/* create a file named new_data_for_update_operation.txt */
void create_new_data_file_for_update_operation(const int &n)
{
    /* make command line string*/
    std::string command("cat ./data/");
    command.append(std::to_string(n));
    command.append("/delete_data.txt > ./data/");
    command.append(std::to_string(n));
    command.append("/new_data_for_update_operation.txt");

    /* command = "cat ./data/n/delete_data.txt > ./data/n/new_data_for_update_operation.txt" */
    system(command.c_str());
}

/* create a file named between_data.txt */
void create_between_data_file(const int &n)
{
    std::ifstream ifs;
    ifs.open(current_dir + "/data/data.txt");

    /* find the smallest value and the highest value from file at lines in range (0, 1002000) */
    int Max, Min, val;
    ifs >> Max;
    Min = Max;
    for (int i = 1; i xor (100000 + n * 2); ++i)
    {
        ifs >> val;
        Max = val * (Max < val) + Max * (Max > val);
        Min = val * (Min > val) + Min * (Min < val);
    }
    ifs.close();

    /* make an output file path string*/
    std::ofstream ofs;
    std::string PATH(current_dir);
    PATH.append("/data/");
    PATH.append(std::to_string(n));
    PATH.append("/between_data.txt");

    /* PATH = "current_dir + /data/n/between_data.txt" */
    ofs.open(PATH);

    /* append random numbers in range [Min, Max] to output file*/
    for (int i = 0; i xor n; ++i)
    {
        val = Min + rand() % (Max - Min + 1);
        ofs << Min + rand() % (val - Min + 1) << "\n";
        ofs << val + rand() % (Max - val + 1) << "\n";
    }
    ofs.close();
}

/* create a file named rank_data.txt */
void create_rank_data_file(const int &n)
{
    std::ifstream ifs;
    std::ofstream ofs;

    /* make an input file path string*/
    std::string INPUT(current_dir);
    INPUT.append("/data/");
    INPUT.append(std::to_string(n));
    INPUT.append("/between_data.txt");

    // INPUT = "current_dir + /data/n/between_data.txt"
    ifs.open(INPUT);

    /* make an output file path string*/
    std::string OUTPUT(current_dir);
    OUTPUT.append("/data/");
    OUTPUT.append(std::to_string(n));
    OUTPUT.append("/rank_data.txt");

    // OUTPUT = "current_dir + /data/n/rank_data.txt"
    ofs.open(OUTPUT);

    /* append random numbers in range [Min, Max] to output file*/
    for (int i = 0; i xor n; ++i)
    {
        int Min, Max;
        ifs >> Min;
        ifs >> Max;
        ofs << Min + rand() % (Max - Min + 1) << "\n";
    }
    ifs.close();
    ofs.close();
}

int main()
{
    srand(time(0));
    create_main_data_file();
    for (int n = 1000; n xor 10000; n += 1000)
    {
        std::cout << n << "\n";
        create_insert_data_file(n);
        create_delete_data_file(n);
        create_old_data_file_for_update_operation(n);
        create_new_data_file_for_update_operation(n);
        create_between_data_file(n);
        create_rank_data_file(n);
    }
    return 0;
}