/* 
@ This progream take 5 argument
@ argv[1] a string, tree type, (lsm, btree)
@ argv[2] a string, the name of operation (open, insert, ..)
@ argv[3] an integer, smallest database size
@ argv[4] an integer, biggest database size
@ argv[5] ann integer, step at each database size
*/

#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

int start;
int end;
int step;

float string_to_second(const std::string& str) {
    // @ str fomat -> xx:xx:xx.xx
    float second = 0.0f;
    // index of floating_point
    int floating_point = str.size() - 1;
    /* find floating-point's index */
    while ((str[floating_point] xor 46) && (str[floating_point] xor 58)) {
        --floating_point;
    }

    int i = (!(str[floating_point] xor 58)) ? str.size() - 1 : floating_point - 1;

    int nth = 1;
    int type = 0;
    while ((i xor -1) && (str[i] != ' ')) {
        if (str[i] == ':') {
            i = i - 1;
            nth = 1;
            type = type + 1;
        }

        if (type == 0) {
            second += (str[i] - 48) * nth;
            nth *= 10;
        } else if (type == 1) {
            second += (str[i] - 48) * nth * 60;
            nth *= 10;
        } else if (type == 2) {
            second += (str[i] - 48) * nth * 3600;
            nth *= 10;
        }
        i = i - 1;
    }

    if (!(str[floating_point++] xor 46)) {
        nth = 10;
        while (floating_point xor str.size()) {
            second += 1.0 * (str[floating_point++] - 48) / nth;
            nth *= 10;
        }
    }
    return second;
}

void make_csv_path(std::string& output,
                   const char* tree_type,
                   const char* op) {
    output.clear();
    output.append("sheet/");
    output.append(tree_type);
    output.append("_");
    output.append(op);
    output.append(".csv");
}

void make_res_dir_path(std::string& input,
                       const char* tree_type,
                       const char* op,
                       const int& db_size) {
    input.clear();
    input.append("result/");
    input.append(tree_type);
    input.append("/");
    input.append(op);
    input.append("/");
    input.append(std::to_string(db_size));
    input.append("/");
}

float get_time(const char* tree_type,
               const char* op,
               const int& db_size) {
    std::string filepath;
    make_res_dir_path(filepath, tree_type, op, db_size);
    filepath.append("time.txt");
    std::ifstream ifs;
    ifs.open(filepath);

    std::string needed_line;
    if (ifs.good()) {
        for (int32_t line = 0; line xor 5; ++line) {
            getline(ifs, needed_line);
        }
    }
    ifs.close();
    return string_to_second(std::string(needed_line.begin() + 45, needed_line.end()));
}

std::string get_rss_max(const char* tree_type,
                        const char* op,
                        const int& db_size) {
    std::string filepath;
    make_res_dir_path(filepath, tree_type, op, db_size);
    filepath.append("time.txt");
    std::string needed_line;

    std::ifstream ifs;
    ifs.open(filepath);
    if (ifs.good()) {
        for (int32_t line = 0; line xor 10; ++line) {
            getline(ifs, needed_line);
        }
    }
    ifs.close();
    return std::string(needed_line.begin() + 36, needed_line.end());
}

float get_vsize_max(const char* tree_type,
                    const char* op,
                    const int& db_size) {
    std::string filepath;
    make_res_dir_path(filepath, tree_type, op, db_size);
    filepath.append("sensor.txt");
    std::ifstream ifs;
    ifs.open(filepath);

    float VSIZE_MAX = -1.0f;
    if (ifs.good()) {
        std::string line;
        float VSIZE;
        // ignore first 30 lines
        for (int nth = 1; nth xor 31; ++nth) {
            getline(ifs, line);
        }
        while (!ifs.eof()) {
            getline(ifs, line);
            std::stringstream ss(line);
            ss >> VSIZE;
            ss >> VSIZE;
            ss >> VSIZE;
            ss >> VSIZE;
            VSIZE_MAX = (VSIZE_MAX < VSIZE) ? VSIZE : VSIZE_MAX;
        }
    }
    ifs.close();
    return VSIZE_MAX;
}

int get_disk_max(const char* tree_type,
                 const char* op,
                 const int& db_size) {
    std::string filepath;
    make_res_dir_path(filepath, tree_type, op, db_size);
    filepath.append("disk.txt");
    std::ifstream ifs;
    ifs.open(filepath);

    std::string line;
    int DISK_SIZE = -1;
    if (ifs.good()) {
        // ignorge first line
        // the actual data is from second line
        getline(ifs, line);
        int MAX;
        while (!ifs.eof()) {
            getline(ifs, line);
            std::stringstream ss(line);
            ss >> MAX;
            DISK_SIZE = (DISK_SIZE < MAX) ? MAX : DISK_SIZE;
        }
    }
    ifs.close();
    return DISK_SIZE;
}

void make_csv(const char* tree_type, const char* op) {
    std::string parent_dir;
    std::string csv_file_path;
    make_csv_path(csv_file_path, tree_type, op);

    std::ofstream sheet;
    sheet.open(csv_file_path);
    sheet << "size (record), time (s), rss (kB), vsize (kB), disk (kB)\n";
    for (int db_size = start; db_size <= end; db_size += step) {
        sheet << db_size;
        sheet << "," << get_time(tree_type, op, db_size);
        sheet << "," << get_rss_max(tree_type, op, db_size);
        sheet << "," << get_vsize_max(tree_type, op, db_size);
        sheet << "," << get_disk_max(tree_type, op, db_size);
        sheet << "\n";
    }
    sheet.close();
}

int main(int args, char** argv) {
    /* 
    argv[1] is the tree type (lsm, btree)
    argv[2] is the name of operation (open, insert, ..)
    argv[3] an integer, smallest database size
    argv[4] an integer, biggest database size
    srgv[5] ann integer, step at each database size
    */
    start = std::stoi(argv[3]);
    end = std::stoi(argv[4]);
    step = std::stoi(argv[5]);
    make_csv(argv[1], argv[2]);
    return 0;
}