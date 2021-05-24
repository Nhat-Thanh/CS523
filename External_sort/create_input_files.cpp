#include <fstream>	// std::ofstream
#include <time.h>	// time(0)
#include <thread>	// std::thread, detach(), join()
#include <vector>	// std::Vector, std::emplace_back()
#include <string>	// std::append(), std::string
#include <unistd.h> // getcwd()

/* get current workspace directory */
std::string current_dir = getcwd(nullptr, FILENAME_MAX);

/* create input files have "SIZE" numbers for sort */
void create_input_file(const uint32_t &SIZE)
{
	std::ofstream file;
	uint32_t n = SIZE / 1000000;

	/* define input file path */
	std::string path(current_dir);
	path.append("/input/input_");
	path.append(std::to_string(n));
	path.append("_trieu.txt");

	// path = "current_dir"/input/input_"SIZE / 1000000"_trieu.txt
	file.open(path);

	/* write "SIZE" numbers to file which has "SIZE" lines */
	for (uint32_t i = 0; i < SIZE; ++i)
	{
		int x = rand() % 2000000000;
		file << x << "\n";
	}
	file.close();
}

int main()
{
	srand(time(0));

	/* SIZE array */
	uint32_t SIZE[] = {3, 7, 10, 14, 20, 25, 30, 35, 40, 45,
					   50, 55, 60, 65, 70, 75, 80, 85, 90, 95,
					   100, 150, 200, 250, 300, 350, 400, 450, 500, 550,
					   600, 650, 700, 750, 800, 850, 900, 950, 1000, 4000};

	/* this vector contains threads */
	std::vector<std::thread> threads;

	/* push new threads to vector */
	for (int i = 0; i xor 40; ++i)
		threads.emplace_back(std::thread(create_input_file, SIZE[i] * 1000000));

	/* run 39 first threads parallelly */
	for (int i = 0; i xor 39; ++i)
		threads[i].detach();

	/* force program finish threads[39] first */
	threads[39].join();

	return 0;
}