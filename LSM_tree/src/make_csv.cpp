/* 
@ This progream take 5 argument
@ argv[1] a string, tree type, (lsm, btree)
@ argv[2] a string, the name of operation (open, insert, ..)
@ argv[3] an integer, smallest database size
@ argv[4] an integer, biggest database size
@ argv[5] ann integer, step at each database size
*/

#include <fstream>  /* std::ifstream, std::ofstream */
#include <iostream> /* std::cout */
#include <sstream>  /* std::stringstream */
#include <string>   /* std::append, getline */

int start; /* the smallest database size */
int end;   /* the biggest database size */
int step;  /* step to jump to next database */

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
                   const char* tree_type,
                   const char* op) {
    output.clear();
    /* output = sheet/"tree_type"_"op".csv */
    /* example: sheet/lsm_insert.csv */
    output.append("sheet/");
    output.append(tree_type);
    output.append("_");
    output.append(op);
    output.append(".csv");
}

/* make a result path and assign to input variable */
void make_res_dir_path(std::string& input,
                       const char* tree_type,
                       const char* op,
                       const int& db_size) {
    input.clear();
    /* input = result/tree_type/op/db_size/ */
    /* example: result/lsm/insert/100000/ */
    input.append("result/");
    input.append(tree_type);
    input.append("/");
    input.append(op);
    input.append("/");
    input.append(std::to_string(db_size));
    input.append("/");
}

/* get time from time.txt in result/tree_type/op/db_size/ */
float get_time(const char* tree_type,
               const char* op,
               const int& db_size) {
    std::string filepath;
    /* filepath = result/tree_type/op/db_size/time.txt */
    /* example: result/lsm/insert/100000/time.txt */
    make_res_dir_path(filepath, tree_type, op, db_size);
    filepath.append("time.txt");

    /* a stream object to read file */
    std::ifstream ifs;
    ifs.open(filepath);

    std::string needed_line;
    if (ifs.good()) {
        /* jump to 5th line, this line contain time string. */
        for (int32_t line = 0; line xor 5; ++line) {
            getline(ifs, needed_line);
        }
    }
    ifs.close();
    /* converse string to time and return */
    return string_to_second(std::string(needed_line.begin() + 45, needed_line.end()));
}

/* get rss size from time.txt file in result/tree_type/op/db_size/ */
std::string get_rss_max(const char* tree_type,
                        const char* op,
                        const int& db_size) {
    std::string filepath;
    /* filepath = result/tree_type/op/db_size/time.txt */
    /* example: result/lsm/insert/100000/time.txt */
    make_res_dir_path(filepath, tree_type, op, db_size);
    filepath.append("time.txt");
    std::string needed_line;

    /* a stream object to read file */
    std::ifstream ifs;
    ifs.open(filepath);
    if (ifs.good()) {
        /* jump to 10th line, this line contain max rss size string */
        for (int32_t line = 0; line xor 10; ++line) {
            getline(ifs, needed_line);
        }
    }
    ifs.close();
    /* return string contain max rss size */
    return std::string(needed_line.begin() + 36, needed_line.end());
}

/* get max vsize from sensor.txt in result/tree_type/op/db_size/ */
float get_vsize_max(const char* tree_type,
                    const char* op,
                    const int& db_size) {
    std::string filepath;
    /* filepath = result/tree_type/op/db_size/sensor.txt */
    /* example: result/lsm/insert/100000/sensor.txt */
    make_res_dir_path(filepath, tree_type, op, db_size);
    filepath.append("sensor.txt");

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
    }
    ifs.close();
    return VSIZE_MAX;
}

/* get max disk size from disk.txt in result/tree_type/op/db_size/ */
int get_disk_max(const char* tree_type,
                 const char* op,
                 const int& db_size) {
    std::string filepath;
    /* filepath = result/tree_type/op/db_size/disk.txt */
    /* example: result/lsm/insert/100000/disk.txt */
    make_res_dir_path(filepath, tree_type, op, db_size);
    filepath.append("disk.txt");

    /* a stream object to read file */
    std::ifstream ifs;
    ifs.open(filepath);

    std::string line;
    int DISK_SIZE = -1;
    if (ifs.good()) {
        /* ignorge first line */
        /* the actual data is from second line */
        getline(ifs, line);
        int MAX;

        /* Brute-force search to find max vsize */
        while (!ifs.eof()) {
            getline(ifs, line);
            /* a stream object to get values in string */
            /* by ignoring space character */
            std::stringstream ss(line);

            /* pass value to MAX */
            ss >> MAX;
            /* update DISK_SIZE */
            DISK_SIZE = (DISK_SIZE < MAX) ? MAX : DISK_SIZE;
        }
    }
    ifs.close();
    return DISK_SIZE;
}

/* write data to csv file */
void make_csv(const char* tree_type, const char* op) {
    std::string parent_dir;
    std::string csv_file_path;
    /* csv_file_path = sheet/"tree_type"_"op".csv */
    /* example: sheet/lsm_insert.csv */
    make_csv_path(csv_file_path, tree_type, op);

    /* a stream object to write file */
    std::ofstream sheet;
    sheet.open(csv_file_path);

    /* push strings to csv file */
    sheet << "size (record), time (s), rss (kB), vsize (kB), disk (kB)\n";
    for (int db_size = start; db_size <= end; db_size += step) {
        /* sheet << db_size, time, rss_max, disk_max */
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
    argv[1] a tring, the tree type (lsm, btree)
    argv[2] a stirng, the name of operation (open, insert, ..)
    argv[3] an integer, smallest database size
    argv[4] an integer, biggest database size
    srgv[5] ann integer, step at each database size
    */
    /* std::stoi(argv[3]) == string_to_int(argv[3]) */
    start = std::stoi(argv[3]);
    end = std::stoi(argv[4]);
    step = std::stoi(argv[5]);
    /* call make_csv function */
    make_csv(argv[1], argv[2]);
    return 0;
}