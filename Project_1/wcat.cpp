//ECS 150
//Hagos Worrede
#include <iostream>
#include <cstdlib>
#include <fcntl.h>
#include <unistd.h>

void checking_Cat(const char* filename) {
    int checking_forFile = open(filename, O_RDONLY);
    //checking for the first test that comes from the file above / std::cout << "when test 1\n";
    if (checking_forFile == -1) {
        std::cout << "wcat: cannot open file\n";
        exit(1);//check 
    }
    
    
    
    char fixing_finalBuff[1028]; 
    ssize_t reading_bytes;
    while ((reading_bytes = read(checking_forFile, fixing_finalBuff, sizeof(fixing_finalBuff))) > 0) {
    //checking for the first test that comes from the file above / std::cout << "when test 2\n";
        ssize_t reading_theWrite = write(STDOUT_FILENO, fixing_finalBuff, reading_bytes);
        if (reading_theWrite == -1) {
    //checking for the first test that comes from the file above / std::cout << "when test 3\n";
            exit(1);
        }
    }

    if (reading_bytes == -1) {
        exit(1);//check 
    }
    close(checking_forFile);
}



//now we close the check for the file
int main(int argc, char* argv[]) {
    if (argc == 1) {
        return 0;//check for the error
    }
//check for the last final out 
    int finalOut = 0; 
    for (int i = 1; i < argc; ++i) {
        checking_Cat(argv[i]);
    }//check 

    return finalOut;
}



