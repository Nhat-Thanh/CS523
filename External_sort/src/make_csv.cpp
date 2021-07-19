#include <fstream>  /* std::ifstream, std::ofstream */
#include <iostream> /* std::cout */
#include <sstream>  /* std::stringstream */
#include <string>   /* std::append, getline */

float string_to_second(const std::string& str) {
    /* @ string fomat is xx:xx:xx.xx */
    float second = 0.0f;
    /* index of floating_point */
    int floating_point = str.size() - 1;
    /* find floating-point's index */
    while ((str[floating_point] xor 46) && (str[floating_point] xor 58)) {
        --floating_point;
    }

    /* 
    if character at floating_point is ':'
        return str.size() - 1
    else 
        retun floating_point - 1 
    */
    int last = (!(str[floating_point] xor 58)) ? str.size() - 1 : floating_point - 1;

    /* this is order of number that begin at ':' */
    int nth = 1;
    int type = 0;
    /* while last >= 0 and str[last] != ' ' */
    while ((last xor -1) && (str[last] != ' ')) {
        if (str[last] == ':') {
            last = last - 1;
            nth = 1;
            /* second -> minute and minute -> hour */
            type = type + 1;
        }

        /* if this is second */
        if (type == 0) {
            second += (str[last] - 48) * nth;
            nth *= 10;
            /* it this is minute */
        } else if (type == 1) {
            second += (str[last] - 48) * nth * 60;
            nth *= 10;

            /* if this is hour */
        } else if (type == 2) {
            second += (str[last] - 48) * nth * 3600;
            nth *= 10;
        }
        last = last - 1;
    }

    /* character at floating_point is '.' */
    if (!(str[floating_point++] xor 46)) {
        /* add the value behind the '.' to second variable */
        nth = 10;
        while (floating_point xor str.size()) {
            second += 1.0 * (str[floating_point++] - 48) / nth;
            nth *= 10;
        }
    }

    return second;
}

/* make csv file path and assign to output variable */
void make_csv_path(std::string& output,
                   const char* type) {
    output.clear();
    /* output = sheet/(type).csv */
    /* example: sheet/complexity.csv */
    output.append("sheet/");
    output.append(type);
    output.append(".csv");
}

/* make a result path and assign to input variable */
void make_file_path(std::string& input,
                    const char* parent_dir,
                    const char* file_type,
                    const uint32_t& size,
                    const int& num_cores,
                    const int& buffer) {
    input.clear();
    /* input = parent_dir/(file_type)_(size)_trieu_(num_cores)_cores_(buffer)M.txt */
    /* example: parent_dir/time_10_trieu_4_cores_100M.txt */
    input.append(parent_dir);
    input.append("/");
    input.append(file_type);
    input.append("_");
    input.append(std::to_string(size));
    input.append("_trieu_");
    input.append(std::to_string(num_cores));
    input.append("_cores_");
    input.append(std::to_string(buffer));
    input.append("M.txt");
}

/* get time from time file in parent_dir */
float get_time(const char* parent_dir,
               const uint32_t& size,
               const int& num_core,
               const int& buffer) {
    std::string filepath;
    make_file_path(filepath, parent_dir, "time", size, num_core, buffer);

    /* a stream object to read file */
    std::ifstream ifs;
    ifs.open(filepath);

    std::string needed_line;
    if (ifs.good()) {
        /* jump to 5th line, this line contain time string. */
        for (int32_t line = 0; line xor 5; ++line) {
            getline(ifs, needed_line);
        }
    } else {
        std::cout << parent_dir << " time "
                  << size << " " << num_core << " " << buffer << "\n";
    }
    ifs.close();
    /* converse string to time and return */
    return string_to_second(std::string(needed_line.begin() + 45, needed_line.end()));
}

/* get rss size from time file file in parent_dir */
std::string get_rss_max(const char* parent_dir,
                        const uint32_t& size,
                        const int& num_core,
                        const int& buffer) {
    std::string filepath;
    make_file_path(filepath, parent_dir, "time", size, num_core, buffer);

    std::string needed_line;

    /* a stream object to read file */
    std::ifstream ifs;
    ifs.open(filepath);
    if (ifs.good()) {
        /* jump to 10th line, this line contain max rss size string */
        for (int32_t line = 0; line xor 10; ++line) {
            getline(ifs, needed_line);
        }
    } else {
        std::cout << parent_dir << " time "
                  << size << " " << num_core << " " << buffer << "\n";
    }
    ifs.close();
    /* return string contain max rss size */
    return std::string(needed_line.begin() + 36, needed_line.end());
}

/* get max vsize from sensor file in parent_dir */
float get_vsize_max(const char* parent_dir,
                    const uint32_t& size,
                    const int& num_core,
                    const int& buffer) {
    std::string filepath;
    make_file_path(filepath, parent_dir, "sensors", size, num_core, buffer);

    /* a stream object to read file */
    std::ifstream ifs;
    ifs.open(filepath);

    float VSIZE_MAX = -1.0f;
    if (ifs.good()) {
        std::string line;
        float VSIZE;
        /* ignore first 30 lines */
        for (int nth = 1; nth xor 31; ++nth) {
            getline(ifs, line);
        }
        /* Brute-force search to find max vsize */
        while (!ifs.eof()) {
            getline(ifs, line);
            /* a stream object to get values in string */
            /* by ignoring space character */
            std::stringstream ss(line);
            /* pass vsize value to VSIZE */
            ss >> VSIZE;
            ss >> VSIZE;
            ss >> VSIZE;
            ss >> VSIZE;
            /* update VSIZE_MAX */
            VSIZE_MAX = (VSIZE_MAX < VSIZE) ? VSIZE : VSIZE_MAX;
        }
    } else {
        std::cout << parent_dir << " sensors "
                  << size << " " << num_core << " " << buffer << "\n";
    }
    ifs.close();
    return VSIZE_MAX;
}

/* write data to csv file */
void make_compexity_csv() {
    std::string csv_file_path;
    make_csv_path(csv_file_path, "compexity");
    const char* dir = "result/complexity/";

    /* a stream object to write file */
    std::ofstream sheet;
    sheet.open(csv_file_path);

    /* push strings to csv file */
    sheet << "size (record), time (s), rss (kB), vsize (kB)\n";
    for (int SIZE = 1; SIZE <= 50; SIZE += 1) {
        std::string parent_dir(dir);
        parent_dir.append(std::to_string(SIZE));
        parent_dir.append("_trieu");

        /* sheet << db_size, time, rss_max */
        sheet << SIZE * 1000000;
        sheet << "," << get_time(parent_dir.c_str(), SIZE, 1, 100);
        sheet << "," << get_rss_max(parent_dir.c_str(), SIZE, 1, 100);
        sheet << "," << get_vsize_max(parent_dir.c_str(), SIZE, 1, 100);
        sheet << "\n";
    }
    sheet.close();
}

/* write data to csv file */
void make_buffer_csv() {
    std::string csv_file_path;
    make_csv_path(csv_file_path, "buffer");
    const char* dir = "result/buffer/";

    /* a stream object to write file */
    std::ofstream sheet;
    sheet.open(csv_file_path);

    /* push strings to csv file */
    sheet << "buffer(MB), time (s), rss (kB), vsize (kB)\n";
    for (int BUFFER = 50; BUFFER <= 1000; BUFFER += 50) {
        std::string parent_dir(dir);
        parent_dir.append(std::to_string(BUFFER));
        parent_dir.append("M");

        /* sheet << db_size, time, rss_max */
        sheet << BUFFER;
        sheet << "," << get_time(parent_dir.c_str(), 50, 4, BUFFER);
        sheet << "," << get_rss_max(parent_dir.c_str(), 50, 4, BUFFER);
        sheet << "," << get_vsize_max(parent_dir.c_str(), 50, 4, BUFFER);
        sheet << "\n";
    }
    sheet.close();
}

/* write data to csv file */
void make_parallel_csv() {
    std::string csv_file_path;
    make_csv_path(csv_file_path, "parallel");
    const char* dir = "result/parallel/";

    /* a stream object to write file */
    std::ofstream sheet;
    sheet.open(csv_file_path);

    /* push strings to csv file */
    sheet << "num cores , time (s), rss (kB), vsize (kB)\n";
    for (int NUM_CORE = 1; NUM_CORE <= 8; NUM_CORE += 1) {
        std::string parent_dir(dir);
        parent_dir.append(std::to_string(NUM_CORE));

        /* sheet << db_size, time, rss_max */
        sheet << NUM_CORE;
        sheet << "," << get_time(parent_dir.c_str(), 50, NUM_CORE, 100);
        sheet << "," << get_rss_max(parent_dir.c_str(), 50, NUM_CORE, 100);
        sheet << "," << get_vsize_max(parent_dir.c_str(), 50, NUM_CORE, 100);
        sheet << "\n";
    }
    sheet.close();
}

int main() {
    make_buffer_csv();
    make_compexity_csv();
    make_parallel_csv();
    return 0;
}