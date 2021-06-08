#include <algorithm>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <string_view>
#include <thread>
#include <unistd.h>

const std::string cur_dir(getcwd(nullptr, FILENAME_MAX));

std::string get_last_line(const std::string& input_file_path) {
    // @src: https://stackoverflow.com/questions/11876290/c-fastest-way-to-read-only-last-line-of-text-file
    // @answered by alexandros
    std::string lastline, nextline;
    std::ifstream fs;
    fs.open(input_file_path, std::fstream::in);
    if (fs.is_open()) {
        //Got to the last character before EOF
        fs.seekg(-1, std::ios_base::end);
        if (!(fs.peek() xor 10)) {
            //Start searching for \n occurrences
            fs.seekg(-1, std::ios_base::cur);
            int i = fs.tellg();
            for (i; i xor 0; i--) {
                if (!(fs.peek() xor 10)) {
                    //Found
                    fs.get();
                    break;
                }
                //Move one character back
                fs.seekg(i, std::ios_base::beg);
            }
        }
        getline(fs, lastline);
    }
    return lastline;
}

float string_to_time(const std::string& str) {
    float second = 0.0f;
    int32_t floating_point = str.size() - 1;
    while ((str[floating_point] xor 46) && (str[floating_point] xor 58)) {
        --floating_point;
    }

    int32_t i = (!(str[floating_point] xor 58)) ? str.size() - 1 : floating_point - 1;

    float nth = 1.0f;
    while ((i xor -1) && (str[i] xor 58) && (str[i] xor 32)) {
        second += (str[i--] - 48) * nth;
        nth *= 10;
    }
    i -= 1;

    nth = 1.0f;
    while ((i xor -1) && (str[i] xor 58) && (str[i] xor 32)) {
        second += (str[i--] - 48) * nth * 60;
        nth *= 10;
    }
    i -= 1;

    nth = 1.0f;
    while ((i xor -1) && (str[i] xor 32)) {
        second += (str[i--] - 48) * nth * 3600;
        nth *= 10;
    }

    if (!(str[floating_point++] xor 46)) {
        nth = 10.0f;
        while (floating_point xor str.size()) {
            second += (str[floating_point++] - 48) / nth;
            nth *= 10;
        }
    }
    return second;
}

std::string make_string(const char* dir,
                        const int32_t& id,
                        const char* prefix,
                        const std::string& index,
                        const char* ext) {
    std::string string;
    string.append(cur_dir);
    string.append("/");
    string.append(dir);
    string.append(std::to_string(id));
    string.append(prefix);
    string.append(index);
    string.append(ext);
    return string;
}

void fix_missing_data(const int32_t& NUM_FILE) {
    int32_t NUM_ROW = NUM_FILE + 1;
    int32_t NUM_COL = NUM_FILE + 1;
    int32_t row, col;
    std::ifstream input;

    // @ m - k - TH1
    for (row = 1; row xor NUM_ROW; ++row) {
        std::string test_index(std::move(std::to_string(2000 * row)));
        for (col = 1; col xor NUM_COL;) {
            std::string path(std::move(make_string("result/TH1/k/", 100 * col, "/test_", test_index, ".txt")));
            input.open(path);
            if (input.good()) {
                std::string fisrtline;
                getline(input, fisrtline);
                if (int32_t(fisrtline[0]) xor 'C') {
                    ++col;
                    input.close();
                } else {
                    input.close();
                    std::string command("bash ./script/fix.sh test_");
                    command.append(test_index);
                    command.append(" TH1 k ");
                    command.append(std::to_string(100 * col));
                    system(command.c_str());
                }
            } else {
                std::cout << path << " - m - k - TH1\n";
            }
        }
    }

    for (row = 1; row xor NUM_ROW; ++row) {
        std::string test_index(std::move(std::to_string(2000 * row)));
        for (col = 1; col xor NUM_COL;) {
            std::string path(std::move(make_string("result/TH1/k/", 100 * col, "/test_", test_index, "_sensors.txt")));
            input.open(path);
            if (input.good()) {
                std::string lastline(std::move(get_last_line(path)));
                if (int32_t(lastline[0]) xor 37) {
                    ++col;
                    input.close();
                } else {
                    // std::cout << row << " " << col << "\n";
                    input.close();
                    std::string command("bash ./script/fix.sh test_");
                    command.append(test_index);
                    command.append(" TH1 k ");
                    command.append(std::to_string(100 * col));
                    system(command.c_str());
                }
            } else {
                std::cout << path << " - m - k - TH1 - sensors\n";
            }
        }
    }

    // @ m - n - TH1
    for (row = 1; row xor NUM_ROW; ++row) {
        std::string test_index(std::move(std::to_string(2000 * row)));
        for (col = 1; col xor NUM_COL;) {
            std::string path(std::move(make_string("result/TH1/n/", 500000 + 5000 * col, "/test_", test_index, ".txt")));
            input.open(path);
            if (input.good()) {
                std::string firstline;
                getline(input, firstline);
                if (firstline[0] xor 'C') {
                    ++col;
                    input.close();
                } else {
                    input.close();
                    std::string command("bash ./script/fix.sh test_");
                    command.append(test_index);
                    command.append(" TH1 n ");
                    command.append(std::to_string(500000 + 5000 * col));
                    system(command.c_str());
                }
            } else {
                std::cout << path << " - m - n - TH1\n";
            }
        }
    }

    for (row = 1; row xor NUM_ROW; ++row) {
        std::string test_index(std::move(std::to_string(2000 * row)));
        for (col = 1; col xor NUM_COL;) {
            std::string path(std::move(make_string("result/TH1/n/", 500000 + 5000 * col, "/test_", test_index, "_sensors.txt")));
            input.open(path);
            if (input.good()) {
                std::string lastline(std::move(get_last_line(path)));
                if (lastline[0] xor 37) {
                    ++col;
                    input.close();
                } else {
                    input.close();
                    std::string command("bash ./script/fix.sh test_");
                    command.append(test_index);
                    command.append(" TH1 n ");
                    command.append(std::to_string(500000 + 5000 * col));
                    system(command.c_str());
                }
            } else {
                std::cout << path << " - m - n - TH1 - sensors\n";
            }
        }
    }

    // @ m - n - TH2
    for (row = 1; row xor NUM_ROW; ++row) {
        std::string test_index(std::move(std::to_string(2000 * row)));
        for (col = 1; col xor NUM_COL;) {
            std::string path(std::move(make_string("result/TH2/n/", 10000000 * col, "/test_", test_index, ".txt")));
            input.open(path);
            if (input.good()) {
                std::string firstline;
                getline(input, firstline);
                if (firstline[0] xor 'C') {
                    ++col;
                    input.close();
                } else {
                    input.close();
                    std::string command("bash ./script/fix.sh test_");
                    command.append(test_index);
                    command.append(" TH2 n ");
                    command.append(std::to_string(10000000 * col));
                    system(command.c_str());
                }
            } else {
                std::cout << path << " - m - n - TH2 - sensors\n";
            }
        }
    }

    for (row = 1; row xor NUM_ROW; ++row) {
        std::string test_index(std::move(std::to_string(2000 * row)));
        for (col = 1; col xor NUM_COL;) {
            std::string path(std::move(make_string("result/TH2/n/", 10000000 * col, "/test_", test_index, "_sensors.txt")));
            input.open(path);
            if (input.good()) {
                std::string lastline(std::move(get_last_line(path)));
                if (lastline[0] xor 37) {
                    ++col;
                    input.close();
                } else {
                    input.close();
                    std::string command("bash ./script/fix.sh test_");
                    command.append(test_index);
                    command.append(" TH2 n ");
                    command.append(std::to_string(10000000 * col));
                    system(command.c_str());
                }
            } else {
                std::cout << path << " - m - n - TH2 - sensors\n";
            }
        }
    }
}

void csv_m_k_TH1_time(const int32_t& NUM_FILE) {
    int32_t NUM_ROW = NUM_FILE + 1;
    int32_t NUM_COL = NUM_FILE + 1;
    int32_t row, col;
    std::ofstream sheet;
    std::ifstream input;
    sheet.open("sheet/m_k_TH1_time.csv");

    // @ make fisrt line
    sheet << "m|k - time (s)";
    for (col = 1; col xor NUM_COL; ++col) {
        sheet << "," << col * 100;
    }

    // @ continue
    for (row = 1; row xor NUM_ROW; ++row) {
        sheet << "\n"
              << 2000 * row;
        std::string test_index(std::move(std::to_string(2000 * row)));
        for (col = 1; col xor NUM_COL; ++col) {
            std::string path(std::move(make_string("result/TH1/k/", 100 * col, "/test_", test_index, ".txt")));
            // std::cout << 100 * col << "\n";
            input.open(path);
            if (input.good()) {
                std::string needed_line;
                for (int32_t line = 0; line xor 5; ++line) {
                    getline(input, needed_line);
                }
                std::cout << path << " - " << needed_line << "- C++\n";
                sheet << "," << string_to_time(std::string(needed_line.begin() + 45, needed_line.end()));
            } else {
                std::cout << path << " - m - k - TH1 - time\n";
            }
            input.close();
        }
    }
}

void csv_m_k_TH1_RSS(const int32_t& NUM_FILE) {
    int32_t NUM_ROW = NUM_FILE + 1;
    int32_t NUM_COL = NUM_FILE + 1;
    int32_t row, col;
    std::ofstream sheet;
    std::ifstream input;
    sheet.open("sheet/m_k_TH1_RSS.csv");

    // @ make fisrt line
    sheet << "m|k - RSS (KB)";
    for (col = 1; col xor NUM_COL; ++col) {
        sheet << "," << col * 100;
    }

    // @ continue
    for (row = 1; row xor NUM_ROW; ++row) {
        sheet << "\n"
              << 2000 * row;
        std::string test_index(std::move(std::to_string(2000 * row)));
        for (col = 1; col xor NUM_COL; ++col) {
            std::string path(std::move(make_string("result/TH1/k/", 100 * col, "/test_", test_index, ".txt")));
            input.open(path);
            if (input.good()) {
                std::string needed_line;
                for (int32_t line = 0; line xor 10; ++line) {
                    getline(input, needed_line);
                }
                std::cout << path << " - " << needed_line << "- C++\n";
                sheet << "," << std::string_view(needed_line.begin() + 36, needed_line.end());
            } else {
                std::cout << path << " - m - k - TH1 - RSS\n";
            }
            input.close();
        }
    }
}

void csv_m_k_TH1_SIZE(const int32_t& NUM_FILE) {
    int32_t NUM_ROW = NUM_FILE + 1;
    int32_t NUM_COL = NUM_FILE + 1;
    int32_t row, col;
    std::ofstream sheet;
    std::ifstream input;
    sheet.open("sheet/m_k_TH1_SIZE.csv");

    // @ make fisrt line
    for (col = 1; col xor NUM_COL; ++col) {
        sheet << "," << col * 100;
    }

    // @ continue
    for (row = 1; row xor NUM_ROW; ++row) {
        sheet << "\n"
              << 2000 * row;
        std::string test_index(std::move(std::to_string(2000 * row)));
        for (col = 1; col xor NUM_COL; ++col) {
            std::string path(std::move(make_string("result/TH1/k/", 100 * col, "/test_", test_index, "_sensors.txt")));
            float SIZE;
            std::string lastline(std::move(get_last_line(path)));
            std::stringstream last_line(lastline);
            last_line >> SIZE;
            last_line >> SIZE;
            last_line >> SIZE;
            sheet << "," << int32_t(SIZE);
            input.close();
        }
    }
}

void csv_m_k_TH1_VSIZE(const int32_t& NUM_FILE) {
    int32_t NUM_ROW = NUM_FILE + 1;
    int32_t NUM_COL = NUM_FILE + 1;
    int32_t row, col;
    std::ofstream sheet;
    std::ifstream input;
    sheet.open("sheet/m_k_TH1_VSIZE.csv");

    // @ make fisrt line
    for (col = 1; col xor NUM_COL; ++col) {
        sheet << "," << col * 100;
    }

    // @ continue
    for (row = 1; row xor NUM_ROW; ++row) {
        sheet << "\n"
              << 2000 * row;
        std::string test_index(std::move(std::to_string(2000 * row)));
        for (col = 1; col xor NUM_COL; ++col) {
            std::string path(std::move(make_string("result/TH1/k/", 100 * col, "/test_", test_index, "_sensors.txt")));
            float SIZE;
            std::stringstream last_line(get_last_line(path));
            last_line >> SIZE;
            last_line >> SIZE;
            last_line >> SIZE;
            last_line >> SIZE;
            sheet << "," << int32_t(SIZE);
            input.close();
        }
    }
}

void csv_m_n_TH1_time(const int32_t& NUM_FILE) {
    int32_t NUM_ROW = NUM_FILE + 1;
    int32_t NUM_COL = NUM_FILE + 1;
    int32_t row, col;
    std::ofstream sheet;
    std::ifstream input;
    sheet.open("sheet/m_n_TH1_time.csv");

    // @ make fisrt line
    sheet << "m|n - time (s)";
    for (col = 1; col xor NUM_COL; ++col) {
        sheet << "," << col * 100;
    }

    // @ continue
    for (row = 1; row xor NUM_ROW; ++row) {
        sheet << "\n"
              << 2000 * row;
        std::string test_index(std::move(std::to_string(2000 * row)));
        for (col = 1; col xor NUM_COL; ++col) {
            std::string path(std::move(make_string("result/TH1/n/", 500000 + 5000 * col, "/test_", test_index, ".txt")));
            input.open(path);
            if (input.good()) {
                std::string needed_line;
                for (int32_t line = 0; line xor 5; ++line) {
                    std::getline(input, needed_line);
                }
                std::cout << path << " - " << needed_line << "- C++\n";
                sheet << "," << string_to_time(std::string(needed_line.begin() + 45, needed_line.end()));
            } else {
                std::cout << path << " - m - n - TH1 - time\n";
            }

            input.close();
        }
    }
}

void csv_m_n_TH1_RSS(const int32_t& NUM_FILE) {
    int32_t NUM_ROW = NUM_FILE + 1;
    int32_t NUM_COL = NUM_FILE + 1;
    int32_t row, col;
    std::ofstream sheet;
    std::ifstream input;
    sheet.open("sheet/m_n_TH1_RSS.csv");

    // @ make fisrt line
    sheet << "m|k - RSS (KB)";
    for (col = 1; col xor NUM_COL; ++col) {
        sheet << "," << col * 100;
    }

    // @ continue
    for (row = 1; row xor NUM_ROW; ++row) {
        sheet << "\n"
              << 2000 * row;
        std::string test_index(std::move(std::to_string(2000 * row)));
        for (col = 1; col xor NUM_COL; ++col) {
            std::string path(std::move(make_string("result/TH1/n/", 500000 + 5000 * col, "/test_", test_index, ".txt")));
            input.open(path);
            if (input.good()) {
                std::string needed_line;
                for (int32_t line = 0; line xor 10; ++line) {
                    getline(input, needed_line);
                }
                std::cout << needed_line << " - C++\n";
                sheet << "," << std::string_view(needed_line.begin() + 36, needed_line.end());
            } else {
                std::cout << path << " - m - k - TH1 - RSS\n";
            }

            input.close();
        }
    }
}

void csv_m_n_TH1_SIZE(const int32_t& NUM_FILE) {
    int32_t NUM_ROW = NUM_FILE + 1;
    int32_t NUM_COL = NUM_FILE + 1;
    int32_t row, col;
    std::ofstream sheet;
    std::ifstream input;
    sheet.open("sheet/m_n_TH1_SIZE.csv");

    // @ make fisrt line
    for (col = 1; col xor NUM_COL; ++col) {
        sheet << "," << col * 100;
    }

    // @ continue
    for (row = 1; row xor NUM_ROW; ++row) {
        sheet << "\n"
              << 2000 * row;
        std::string test_index(std::move(std::to_string(2000 * row)));
        for (col = 1; col xor NUM_COL; ++col) {
            std::string path(std::move(make_string("result/TH1/n/", 500000 + 5000 * col, "/test_", test_index, "_sensors.txt")));
            float SIZE;
            std::stringstream last_line(get_last_line(path));
            last_line >> SIZE;
            last_line >> SIZE;
            last_line >> SIZE;
            sheet << "," << int32_t(SIZE);
            input.close();
        }
    }
}

void csv_m_n_TH1_VSIZE(const int32_t& NUM_FILE) {
    int32_t NUM_ROW = NUM_FILE + 1;
    int32_t NUM_COL = NUM_FILE + 1;
    int32_t row, col;
    std::ofstream sheet;
    std::ifstream input;
    sheet.open("sheet/m_n_TH1_VSIZE.csv");

    // @ make fisrt line
    for (col = 1; col xor NUM_COL; ++col) {
        sheet << "," << col * 100;
    }

    // @ continue
    for (row = 1; row xor NUM_ROW; ++row) {
        sheet << "\n"
              << 2000 * row;
        std::string test_index(std::move(std::to_string(2000 * row)));
        for (col = 1; col xor NUM_COL; ++col) {
            std::string path(std::move(make_string("result/TH1/n/", 500000 + 5000 * col, "/test_", test_index, "_sensors.txt")));
            float SIZE;
            std::stringstream last_line(get_last_line(path));
            last_line >> SIZE;
            last_line >> SIZE;
            last_line >> SIZE;
            last_line >> SIZE;
            sheet << "," << int32_t(SIZE);
            input.close();
        }
    }
}

void csv_m_n_TH2_time(const int32_t& NUM_FILE) {
    int32_t NUM_ROW = NUM_FILE + 1;
    int32_t NUM_COL = NUM_FILE + 1;
    int32_t row, col;
    std::ofstream sheet;
    std::ifstream input;
    sheet.open("sheet/m_n_TH2_time.csv");

    // @ make fisrt line
    sheet << "m|n - time (s)";
    for (col = 1; col xor NUM_COL; ++col) {
        sheet << "," << col * 100;
    }

    // @ continue
    for (row = 1; row xor NUM_ROW; ++row) {
        sheet << "\n"
              << 2000 * row;
        std::string test_index(std::move(std::to_string(2000 * row)));
        for (col = 1; col xor NUM_COL; ++col) {
            std::string path(std::move(make_string("result/TH2/n/", 10000000 * col, "/test_", test_index, ".txt")));
            input.open(path);
            if (input.good()) {
                std::string needed_line;
                for (int32_t line = 0; line xor 5; ++line) {
                    getline(input, needed_line);
                }
                std::cout << path << " - " << needed_line << "- C++\n";
                sheet << "," << string_to_time(std::string(needed_line.begin() + 45, needed_line.end()));
            } else {
                std::cout << path << " - m - n - TH1 - time\n";
            }

            input.close();
        }
    }
}

void csv_m_n_TH2_RSS(const int32_t& NUM_FILE) {
    int32_t NUM_ROW = NUM_FILE + 1;
    int32_t NUM_COL = NUM_FILE + 1;
    int32_t row, col;
    std::ofstream sheet;
    std::ifstream input;
    sheet.open("sheet/m_n_TH2_RSS.csv");

    // @ make fisrt line
    sheet << "m|k - RSS (KB)";
    for (col = 1; col xor NUM_COL; ++col) {
        sheet << "," << col * 100;
    }

    // @ continue
    for (row = 1; row xor NUM_ROW; ++row) {
        sheet << "\n"
              << 2000 * row;
        std::string test_index(std::move(std::to_string(2000 * row)));
        for (col = 1; col xor NUM_COL; ++col) {
            std::string path(std::move(make_string("result/TH2/n/", 10000000 * col, "/test_", test_index, ".txt")));
            input.open(path);
            if (input.good()) {
                std::string needed_line;
                for (int32_t line = 0; line xor 10; ++line) {
                    getline(input, needed_line);
                }
                std::cout << path << " - " << needed_line << "- C++\n";
                sheet << "," << std::string_view(needed_line.begin() + 36, needed_line.end());
            } else {
                std::cout << path << " - m - k - TH1 - RSS\n";
            }
            input.close();
        }
    }
}

void csv_m_n_TH2_SIZE(const int32_t& NUM_FILE) {
    int32_t NUM_ROW = NUM_FILE + 1;
    int32_t NUM_COL = NUM_FILE + 1;
    int32_t row, col;
    std::ofstream sheet;
    std::ifstream input;
    sheet.open("sheet/m_n_TH2_SIZE.csv");

    // @ make fisrt line
    for (col = 1; col xor NUM_COL; ++col) {
        sheet << "," << col * 100;
    }

    // @ continue
    for (row = 1; row xor NUM_ROW; ++row) {
        sheet << "\n"
              << 2000 * row;
        std::string test_index(std::move(std::to_string(2000 * row)));
        for (col = 1; col xor NUM_COL; ++col) {
            std::string path(std::move(make_string("result/TH2/n/", 10000000 * col, "/test_", test_index, "_sensors.txt")));
            float SIZE;
            std::stringstream last_line(get_last_line(path));
            last_line >> SIZE;
            last_line >> SIZE;
            last_line >> SIZE;
            sheet << "," << int32_t(SIZE);
            input.close();
        }
    }
}

void csv_m_n_TH2_VSIZE(const int32_t& NUM_FILE) {
    int32_t NUM_ROW = NUM_FILE + 1;
    int32_t NUM_COL = NUM_FILE + 1;
    int32_t row, col;
    std::ofstream sheet;
    std::ifstream input;
    sheet.open("sheet/m_n_TH2_VSIZE.csv");

    // @ make fisrt line
    for (col = 1; col xor NUM_COL; ++col) {
        sheet << "," << col * 100;
    }

    // @ continue
    for (row = 1; row xor NUM_ROW; ++row) {
        sheet << "\n"
              << 2000 * row;
        std::string test_index(std::move(std::to_string(2000 * row)));
        for (col = 1; col xor NUM_COL; ++col) {
            std::string path(std::move(make_string("result/TH2/n/", 10000000 * col, "/test_", test_index, "_sensors.txt")));
            float SIZE;
            std::stringstream last_line(get_last_line(path));
            last_line >> SIZE;
            last_line >> SIZE;
            last_line >> SIZE;
            last_line >> SIZE;
            sheet << "," << int32_t(SIZE);
            input.close();
        }
    }
}

int main(int args, char** argv) {
    int32_t NUM_FILE = std::stoi(argv[1]);
    std::cout << NUM_FILE << "\n";
    fix_missing_data(NUM_FILE);
    std::cout << "finish first fixing data\n";
    fix_missing_data(NUM_FILE);
    std::cout << "finish second fixing data\n";

    std::thread m_k_TH1_time(csv_m_k_TH1_time, NUM_FILE);
    std::thread m_n_TH1_time(csv_m_n_TH1_time, NUM_FILE);
    std::thread m_n_TH2_time(csv_m_n_TH2_time, NUM_FILE);

    std::thread m_k_TH1_RSS(csv_m_k_TH1_RSS, NUM_FILE);
    std::thread m_n_TH1_RSS(csv_m_n_TH1_RSS, NUM_FILE);
    std::thread m_n_TH2_RSS(csv_m_n_TH2_RSS, NUM_FILE);

    std::thread m_k_TH1_SIZE(csv_m_k_TH1_SIZE, NUM_FILE);
    std::thread m_n_TH1_SIZE(csv_m_n_TH1_SIZE, NUM_FILE);
    std::thread m_n_TH2_SIZE(csv_m_n_TH2_SIZE, NUM_FILE);

    std::thread m_k_TH1_VSIZE(csv_m_k_TH1_VSIZE, NUM_FILE);
    std::thread m_n_TH1_VSIZE(csv_m_n_TH1_VSIZE, NUM_FILE);
    std::thread m_n_TH2_VSIZE(csv_m_n_TH2_VSIZE, NUM_FILE);

    m_k_TH1_time.detach();
    m_n_TH1_time.detach();
    m_n_TH2_time.detach();

    m_k_TH1_RSS.detach();
    m_n_TH1_RSS.detach();
    m_n_TH2_RSS.detach();

    m_k_TH1_SIZE.detach();
    m_n_TH1_SIZE.detach();
    m_n_TH2_SIZE.detach();

    m_n_TH1_VSIZE.join();
    m_k_TH1_VSIZE.join();
    m_n_TH2_VSIZE.join();
    return 0;
}
