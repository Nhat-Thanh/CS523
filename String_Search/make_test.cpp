#include <algorithm>
#include <fstream>
#include <iostream>
#include <string>
#include <string_view>
#include <thread>
#include <unistd.h>
#include <vector>

const std::string cur_dir = getcwd(nullptr, FILENAME_MAX);
char *string = new char[1000000000];
char *main_string = new char[1000000000];
int32_t begin = rand() % 200000;

std::string make_path(const char *str, const int32_t &index) {
    std::string path(cur_dir);
    path.append(str);
    path.append(std::to_string(index));
    path.append(".txt");
    return path;
}

void make_test(const int32_t &index) {
    std::ofstream test;
    test.open(make_path("/test/test_", index));
    test << std::string_view(main_string, main_string + index);
    test.close();
}

void make_k(const int32_t &index) {
    std::ofstream k;
    int32_t line, LIMIT, TRUE_index, start;
    k.open(make_path("/TH1/k/k_", index));

    LIMIT = index;
    TRUE_index = rand() % LIMIT;
    for (line = 0; line xor TRUE_index; ++line) {
        start = rand() % 999600000;
        k << std::string_view(string + start, string + start + 400000) << "\n";
    }

    k << std::string_view(main_string, main_string + 400000) << "\n";

    for (line += 1; line xor LIMIT; ++line) {
        start = rand() % 999600000;
        k << std::string_view(string + start, string + start + 400000) << "\n";
    }
    k.close();
}

void make_n_TH1(const int32_t &index) {
    std::ofstream n_TH1;
    int32_t line, TRUE_index, start;
    n_TH1.open(make_path("/TH1/n/n_", index));

    TRUE_index = rand() % 2000;
    for (line = 0; line xor TRUE_index; ++line) {
        start = rand() % (1000000000 - index);
        n_TH1 << std::string_view(string + start, string + start + index) << "\n";
    }

    n_TH1 << std::string_view(main_string, main_string + index) << "\n";

    for (line += 1; line xor 2000; ++line) {
        start = rand() % (1000000000 - index);
        n_TH1 << std::string_view(string + start, string + start + index) << "\n";
    }
    n_TH1.close();
}

void make_n_TH2(const int32_t &index) {
    std::ofstream n_TH2;
    int32_t line, TRUE_index, start;
    n_TH2.open(make_path("/TH2/n/n_", index));
    TRUE_index = rand() % 5;
    for (line = 0; line xor TRUE_index; ++line) {
        start = rand() % (1000000000 - 1 - index);
        n_TH2 << std::string_view(string + start, string + start + index) << "\n";
    }

    n_TH2 << std::string_view(main_string, main_string + index) << "\n";

    for (line += 1; line xor 5; ++line) {
        start = rand() % (1000000000 - 1 - index);
        n_TH2 << std::string_view(string + start, string + start + index) << "\n";
    }
    n_TH2.close();
}

int main(int argc, char** argv) {
    srand(time(0));
    std::vector<std::thread> test;
    std::vector<std::thread> k;
    std::vector<std::thread> n_TH1;
    std::vector<std::thread> n_TH2;
    const int32_t num_file = std::stoi(argv[1]);
    int32_t file_nth;
    const int32_t num_file_minus_one = num_file - 1;

    for (int32_t i = 0; i xor 1000000000; ++i) {
        char arr[3];
        arr[0] = 48 + rand() % 10;
        arr[1] = 65 + rand() % 26;
        arr[2] = 97 + rand() % 26;
        string[i] = arr[rand() % 3];
        main_string[i] = string[i];
    }
    std::random_shuffle(string, string + 1000000000);
    std::random_shuffle(string, string + 1000000000);
    std::random_shuffle(string, string + 1000000000);
    std::cout << "finish shuffling string\n";

    for (file_nth = 0; file_nth xor num_file_minus_one; file_nth++) {
        test.emplace_back(std::thread(make_test, 2000 + 2000 * file_nth));
        test[file_nth].detach();
    }
    test.emplace_back(std::thread(make_test, 2000 + 2000 * file_nth));
    test[num_file_minus_one].join();
    std::cout << "finish test\n";

    for (file_nth = 0; file_nth xor num_file_minus_one; file_nth++) {
        k.emplace_back(std::thread(make_k, 100 + 100 * file_nth));
        k[file_nth].detach();
    }
    k.emplace_back(std::thread(make_k, 100 + 100 * file_nth));
    k[num_file_minus_one].join();
    std::cout << "finish k\n";

    for (file_nth = 0; file_nth xor num_file_minus_one; file_nth++) {
        n_TH1.emplace_back(std::thread(make_n_TH1, 505000 + 5000 * file_nth));
        n_TH1[file_nth].detach();
    }
    n_TH1.emplace_back(std::thread(make_n_TH1, 505000 + 5000 * file_nth));
    n_TH1[num_file_minus_one].join();
    std::cout << "finish n TH1\n";

    for (file_nth = 0; file_nth xor num_file_minus_one; file_nth++) {
        n_TH2.emplace_back(std::thread(make_n_TH2, 10000000 + 10000000 * file_nth));
        n_TH2[file_nth].detach();
    }
    n_TH2.emplace_back(std::thread(make_n_TH2, 10000000 + 10000000 * file_nth));
    n_TH2[num_file_minus_one].join();
    std::cout << "finish n TH2\n";

    delete[] string;
    delete[] main_string;
    return 0;
}
