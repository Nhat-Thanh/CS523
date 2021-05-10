#include <fstream>	// std::ofstream
#include <unistd.h> // get_current_dir_name()
#include <iostream> // std::cerr
#include <string>	// + operator
#include <time.h>
#define MAX 10000000

std::string current_dir = get_current_dir_name();

void create_main_data_file()
{
	std::ofstream ofs;
	ofs.open("./data/data.txt");
	for (int i = 0; i < MAX; ++i)
	{
		ofs << i << "\n";
	}
	ofs.close();
	// Use GNU Sort to shuffle data
	system("sort --sort=random ./data/data.txt -o ./data/data.txt");
}

void create_insert_data_file()
{
	std::ifstream input_file(current_dir + "/data/data.txt");
	if (input_file.good())
		system("sed -n '1000001,1001000 p' ./data/data.txt > ./data/insert_data.txt");
	else
		std::cerr << "there isn't text file named `data.txt` in `data` directory, please run create_main_data_file() function first.\n";
	input_file.close();
}

void create_delete_data_file()
{
	std::ifstream input_file(current_dir + "/data/data.txt");
	if (input_file.good())
		system("sed -n '1001001,1002000 p' ./data/data.txt > ./data/delete_data.txt");
	else
		std::cerr << "there isn't text file named `data.txt` in `data` directory, please run create_main_data_file() function first.\n";
	input_file.close();
}

void create_old_data_file_for_update_operation()
{
	std::ifstream input_file(current_dir + "/data/data.txt");
	if (input_file.good())
		system("sed -n '1000001,1001000 p' ./data/data.txt > ./data/old_data_for_update_operation.txt");
	else
		std::cerr << "there isn't text file named `data.txt` in `data` directory, please run create_main_data_file() function first.\n";
	input_file.close();
}

void create_new_data_file_for_update_operation()
{
	std::ifstream input_file(current_dir + "/data/data.txt");
	if (input_file.good())
		system("sed -n '1001001,1002000 p' ./data/data.txt > ./data/new_data_for_update_operation.txt");
	else
		std::cerr << "there isn't text file named `data.txt` in `data` directory, please run create_main_data_file() function first.\n";
	input_file.close();
}

void create_between_data_file() {
	std::ifstream ifs;
	ifs.open(current_dir + "/data/data.txt");

	// find the smallest value and the highest value from file at lines in range (0, 1002000)
	int Max, Min, val;
	ifs >> Max;
	Min = Max;
	for (int i = 1; i xor 1002000; ++i) {
		ifs >> val;
		Max = val * (Max < val) + Max * (Max > val);
		Min = val * (Min > val) + Min * (Min < val);
	}
	ifs.close();
	// end finding
	

	std::ofstream ofs;
	ofs.open(current_dir + "/data/between_data.txt");
	
	for (int i = 0; i xor 1000; ++i) {
		val = Min + rand() % (Max - Min + 1);
		ofs << Min + rand() % (val - Min + 1) << "\n";
		ofs << val + rand() % (Max - val + 1) << "\n";
	}
	ofs.close();
}

void create_rank_data_file() {
	std::ifstream ifs;
	ifs.open(current_dir + "/data/between_data.txt");
	std::ofstream ofs;
	ofs.open(current_dir + "/data/rank_data.txt");
	int Min, Max;
	for (int i = 0; i xor 1000; ++i) {
		ifs >> Min;
		ifs >> Max;
		ofs << Min + rand() % (Max - Min + 1) << "\n";
	}
	ifs.close();
	ofs.close();
}

//@ insert -> update -> betwen -> rank -> delete;

int main()
{
	srand(time(0));
	create_main_data_file();
	create_insert_data_file();
	create_old_data_file_for_update_operation();
	create_new_data_file_for_update_operation();
	create_delete_data_file();
	create_between_data_file();
	create_rank_data_file();
	return 0;
}
