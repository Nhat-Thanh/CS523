/* 
@ This progream take 3 argument
@ argv[1] an integer, smallest database size
@ argv[2] an integer, biggest database size
@ srgv[3] ann integer, step at each database size
*/

#include <fstream>
#include <iostream>
#include <sstream>
#include <string.h>
#include <string>

int start;
int end;
int step;

std::string get_last_line(const std::string &input_file_path) {
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

void make_res_dir_path(std::string &input,
                       const char *tree_type,
                       const char *op,
                       const int &db_size) {
    input.clear();
    input.append("result/");
    input.append(tree_type);
    input.append("/");
    input.append(op);
    input.append("/");
    input.append(std::to_string(db_size));
    input.append("/");
}

void make_command(std::string &command,
                  const char *tree_type,
                  const char *op,
                  const int &db_size) {
    command.clear();
    if (strcmp(op, "create_database")) {
        command.append("make fix TREE_TYPE=");
        command.append(tree_type);
        command.append(" OP=");
        command.append(op);
        command.append(" DB_SIZE=");
        command.append(std::to_string(db_size));
    } else {
        command.append("make fix_create_database TREE_TYPE=");
        command.append(tree_type);
        command.append(" DB_SIZE=");
        command.append(std::to_string(db_size));
    }
}

void check_vsize(const char *tree_type,
                 const char *op,
                 const int &db_size) {
    std::string filepath;
    make_res_dir_path(filepath, tree_type, op, db_size);
    filepath.append("sensor.txt");
    std::ifstream ifs;
    ifs.open(filepath);
    if (ifs.good()) {
        std::string lastline(std::move(get_last_line(filepath)));
        if (lastline.empty() | !(lastline[0] xor 37)) {
            printf("type=%s, op=%s, size=%d\n", tree_type, op, db_size);
            ifs.close();
            std::string command;
            make_command(command, tree_type, op, db_size);
            system(command.c_str());
        }
    }
    ifs.close();
}

int main(int args, char **argv) {
    /* 
    argv[1] an integer, smallest database size
    argv[2] an integer, biggest database size
    srgv[3] ann integer, step at each database size
    */

    start = std::stoi(argv[1]);
    end = std::stoi(argv[2]);
    step = std::stoi(argv[3]);

    const char *tree_type[2] = {"lsm", "btree"};
    const char *op[6] = {"create_database", "open", "insert", "search", "update", "delete"};
    /* 
    it: Index Tree
    io: Index Operation
     */
    for (int it = 0; it < 2; it++) {
        for (int io = 0; io < 6; io++) {
            for (int SIZE = start; SIZE <= end; SIZE += step) {
                check_vsize(tree_type[it], op[io], SIZE);
            }
        }
    }
    return 0;
}