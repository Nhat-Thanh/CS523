#include <fstream>     // std::ofstream
#include <string>      // std::append(), std::string
#include <thread>      // std::thread, detach(), join()
#include <time.h>      // time(0)
#include <vector>      // std::Vector, std::emplace_back()

/* create input files have "SIZE" numbers for sort */
void create_input_file(const uint32_t &SIZE) {
    std::ofstream file;
    uint32_t n = SIZE / 1000000;

    /* define input file path */
    std::string path;
    path.append("input/");
    path.append(std::to_string(n));
    path.append("_trieu.txt");

    // path = "current_dir"/input/input_"SIZE / 1000000"_trieu.txt
    file.open(path);

    /* write "SIZE" numbers to file which has "SIZE" lines */
    for (uint32_t i = 0; i < SIZE; ++i) {
        int x = rand() % 2000000000;
        file << x << "\n";
    }
    file.close();
}

int main() {
    srand(time(0));

    /* this vector contains threads */
    std::vector<std::thread> threads;

    /* push new threads to vector */
    for (int SIZE = 1; SIZE xor 51; ++SIZE)
        threads.emplace_back(std::thread(create_input_file, SIZE * 1000000));

    /* run 39 first threads parallelly */
    for (int i = 0; i xor 50; ++i)
        threads[i].detach();

    std::thread _4_ti(create_input_file, 4000000000);
    /* force program finish thread _4_ti before exiting */
    _4_ti.join();
    return 0;
}