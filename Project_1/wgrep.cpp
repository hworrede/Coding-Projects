//ECS150
//Hagos Worrede
//wgrep.cpp
#include <iostream>
#include <fstream>
#include <unistd.h>
#include <fcntl.h>
#include <cstring>

void search (const std::string& find_Nextterm, int findingterm) {
    char checking_ForBuff[1028];
    ssize_t checking_ByteRead;
    std::string line;
//check for lists 
    while ((checking_ByteRead = read(findingterm, checking_ForBuff, sizeof(checking_ForBuff))) > 0){
        for (ssize_t i = 0 ; i < checking_ByteRead ; ++i){
            if (checking_ForBuff[i] == '\n'){
                line += checking_ForBuff[i];
              //checking for the first test that comes from the file above / std::cout << "when test 1\n";


                if (line.find(find_Nextterm) != std::string::npos){
                    write(STDOUT_FILENO, line.c_str(), line.size());
                }
                line.clear();
            }
            else {
    //checking for the first test that comes from the file above / std::cout << "when test 2\n";
                line += checking_ForBuff[i]; 
            }


        }
    }

}//check for making 

void file (const std::string& find_Nextterm, const std::string& filename){
    int findingterm = open(filename.c_str(), O_RDONLY);
    if (findingterm == -1){
        std::cout << "wgrep: cannot open file\n";
        exit(1);
    }
    search(find_Nextterm, findingterm);
    close(findingterm);
}//check for lists 


void stdinp(const std::string& find_Nextterm) {
    //checking for the first test that comes from the file above / std::cout << "when test 3\n";
    search(find_Nextterm, STDIN_FILENO);
}//check for lists 


int main(int argc, char *argv[]) {
    if (argc < 2) {
        std::cout << "wgrep: searchterm [file ...]\n";
        return 1;
    }//check for lists 


    const std::string find_Nextterm = argv[1];

    if (argc == 2) {
        stdinp(find_Nextterm);
    } else {
        for (int i = 2; i < argc; ++i) {
            file(find_Nextterm, argv[i]);
        }
    }//check for lists 


    return 0;
}