/* 
* This program takes 5 arguments
* argv[1] -> A string, tree type (lsm or btree)
* argv[2] -> A string, the name of operation (open, insert, ..)
* argv[3] -> An integer, the smallest database size
* argv[4] -> An integer, the biggest database size
* argv[5] -> An integer, the discrepancy between 2 adjacent database size
*/

#include <fstream>  /* std::ifstream, std::ofstream */
#include <iostream> /* std::cout */
#include <sstream>  /* std::stringstream */
#include <string>   /* std::append, getline */

int g_nStart; /* The smallest database size */
int g_nEnd;   /* The biggest database size */
int g_nStep;  /* The discrepancy between 2 adjacent database size */

/*
todo: Converse a formatted string to second
* str: A string has format hh::mm::ss.ss 
	* h-> hour
	* m -> minute
	* s -> second
*/
float string_to_second(const std::string& str) {
    // @ second: Final returned value
    float second = 0.0f;
    
    // @ fp_idx: floating-point index
    int fp_idx = str.size() - 1;

    // todo: Find floating-point's index, floating-point is '.'
    while ((str[fp_idx] xor 46) && (str[fp_idx] xor 58))
        --fp_idx;

    /* 
    if the character at fp_idx is ':'
        return str.size() - 1
    else
        return fp_idx - 1 
    */
    int last = (!(str[fp_idx] xor 58)) ? str.size() - 1 : fp_idx - 1;

    // @ the order of digit that begins at ':'
    int nth = 1;

    /* 
    todo: The time type
    @ type = 0 -> second
    @ type = 1 -> minute
    @ type = 2 -> hour
    */
    int type = 0;

    /* while last >= 0 and str[last] != ' ' */
    while ((last xor -1) && (str[last] != ' ')) {
        if (str[last] == ':') {
            last = last - 1;
            nth = 1;
            type = type + 1;
        }

        if (type == 0) { /* second */
            second += (str[last] - 48) * nth;
            nth *= 10;

        } else if (type == 1) { /* minute */
            second += (str[last] - 48) * nth * 60;
            nth *= 10;

        } else if (type == 2) { /* hour */
            second += (str[last] - 48) * nth * 3600;
            nth *= 10;
        }

        last = last - 1;
    }

    /* if the character at fp_idx is '.' */
    if (!(str[fp_idx++] xor 46)) {
        // todo: Add the value behind '.' to second variable
        nth = 10;
        while (fp_idx xor str.size()) {
            second += 1.0 * (str[fp_idx++] - 48) / nth;
            nth *= 10;
        }
    }

    return second;
}


/* 
todo: Make csv file path and assign to output variable 
* output: Hold full csv file path
* tree_type: lsm or btree
* op: Operation's name
*/
void make_csv_path(std::string& output,
                   const char* tree_type,
                   const char* op) {
    /* 
    @ output = sheet/"tree_type"_"op".csv
    @ example: sheet/lsm_insert.csv 
    */
    output.clear();
    output.append("sheet/");
    output.append(tree_type);
    output.append("_");
    output.append(op);
    output.append(".csv");
}


/* 
todo: Make a result path and assign to input variable
* input: Hold full directory path
* tree_type: lsm or btree
* op: Operation's name
* db_size: The number of records of target database
*/
void make_res_dir_path(std::string& input,
                       const char* tree_type,
                       const char* op,
                       const int& db_size) {
    /* 
    @ input = result/tree_type/op/db_size/
    @ example: result/lsm/insert/100000/ 
    */
    input.clear();
    input.append("result/");
    input.append(tree_type);
    input.append("/");
    input.append(op);
    input.append("/");
    input.append(std::to_string(db_size));
    input.append("/");
}


/* 
todo: Get time from time.txt in result/tree_type/op/db_size/ 
* tree_type: lsm or btree
* op: Operation's name
* db_size: The number of records of target database
*/
float get_time(const char* tree_type,
               const char* op,
               const int& db_size) {
    /* 
    @ file_path = result/tree_type/op/db_size/time.txt
    @ example: result/lsm/insert/100000/time.txt 
    */
    std::string file_path;
    make_res_dir_path(file_path, tree_type, op, db_size);
    file_path.append("time.txt");

    /* 
    @ The stream object to read a file 
    */
    std::ifstream ifs;
    ifs.open(file_path);

    std::string needed_line;
    if (ifs.good()) {
        // todo: Jump to the 5th line, this line contains time string.
        for (int32_t line = 0; line xor 5; ++line)
            getline(ifs, needed_line);
    }
    ifs.close();

    return string_to_second(std::string(needed_line.begin() + 45, needed_line.end()));
}


/* 
todo: Get Maximum rss size from time.txt file in result/tree_type/op/db_size/ 
* tree_type: lsm or btree
* op: Operation's name
* db_size: The number of records of target database
*/
std::string get_rss_max(const char* tree_type,
                        const char* op,
                        const int& db_size) {
    /* 
    @ file_path = result/tree_type/op/db_size/time.txt
    @ example: result/lsm/insert/100000/time.txt 
    */
    std::string file_path;
    make_res_dir_path(file_path, tree_type, op, db_size);
    file_path.append("time.txt");

    /* 
    @ The stream object to read a file 
    */
    std::ifstream ifs;
    ifs.open(file_path);

    std::string needed_line;
    if (ifs.good()) {
        // todo: Jump to 10th line, this line contains rss size string
        for (int32_t line = 0; line xor 10; ++line)
            getline(ifs, needed_line);
    }
    ifs.close();

    return std::string(needed_line.begin() + 36, needed_line.end());
}


/* 
todo: Get maximum vsize from sensor.txt in result/tree_type/op/db_size/ 
* tree_type: lsm or btree
* op: Operation's name
* db_size: The number of records of target database
*/
float get_vsize_max(const char* tree_type,
                    const char* op,
                    const int& db_size) {
    /* 
    @ file_path = result/tree_type/op/db_size/sensor.txt
    @ example: result/lsm/insert/100000/sensor.txt 
    */
    std::string file_path;
    make_res_dir_path(file_path, tree_type, op, db_size);
    file_path.append("sensor.txt");

    /* 
    @ The stream object to read a file 
    */
    std::ifstream ifs;
    ifs.open(file_path);

    float VSIZE_MAX = 0.0f;
    if (ifs.good()) {
        std::string line;
        float VSIZE;

        // todo: Ignore first 30 lines
        for (int nth = 1; nth xor 31; ++nth) 
            getline(ifs, line);

        // todo: Use linear search to find maximum vsize
        while (!ifs.eof()) {
            getline(ifs, line);
            std::stringstream ss(line);

            // todo: Pass vsize value to VSIZE
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


/* 
todo: Get max disk size from disk.txt in result/tree_type/op/db_size/ 
* tree_type: lsm or btree
* op: Operation's name
* db_size: The number of records of target database
*/
int get_disk_max(const char* tree_type,
                 const char* op,
                 const int& db_size) {
    /* 
    @ file_path = result/tree_type/op/db_size/disk.txt
    @ example: result/lsm/insert/100000/disk.txt 
    */
    std::string file_path;
    make_res_dir_path(file_path, tree_type, op, db_size);
    file_path.append("disk.txt");

    /* 
    @ The stream object to read a file 
    */
    std::ifstream ifs;
    ifs.open(file_path);

    std::string line;
    int DISK_SIZE_MAX = 0;
    
    if (ifs.good()) {
        /* ignorge first line */
        /* the actual data is from second line */
        getline(ifs, line);
        int DISK_SIZE;

        // todo: Use linear search to find maximum vsize
        while (!ifs.eof()) {
            getline(ifs, line);
            std::stringstream ss(line);

            // todo: Pass value to DISK_SIZE variable
            ss >> DISK_SIZE;

            DISK_SIZE_MAX = (DISK_SIZE_MAX < DISK_SIZE) ? DISK_SIZE : DISK_SIZE_MAX;
        }
    }
    ifs.close();

    return DISK_SIZE_MAX;
}


/* 
todo: Write data to csv file 
* tree_type: lsm or btree
* op: Operation's name
*/
void make_csv(const char* tree_type, const char* op) {
    /* 
    @ csv_file_path = sheet/"tree_type"_"op".csv
    @ example: sheet/lsm_insert.csv 
    */
    std::string csv_file_path;
    make_csv_path(csv_file_path, tree_type, op);

    /* 
    @ The stream object to write a file 
    */
    std::ofstream sheet;
    sheet.open(csv_file_path);

    // todo: Push strings to csv file
    sheet << "size (record), time (s), rss (kB), vsize (kB), disk (kB)\n";
    for (int db_size = g_nStart; db_size <= g_nEnd; db_size += g_nStep) {
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
    * This program takes 5 arguments
    * argv[1] -> A string, tree type (lsm or btree)
    * argv[2] -> A stirng, the name of operation (open, insert, ..)
    * argv[3] -> An integer, the smallest database size
    * argv[4] -> An integer, the biggest database size
    * argv[5] -> An integer, the discrepancy between 2 adjacent database size
    */

    g_nStart = std::stoi(argv[3]);
    g_nEnd = std::stoi(argv[4]);
    g_nStep = std::stoi(argv[5]);

    make_csv(argv[1], argv[2]);

    return 0;
}
