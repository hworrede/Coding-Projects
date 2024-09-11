//ECS150
//Hagos Worrede
#include <iostream>
#include <unistd.h>
#include <fcntl.h>

void finding_thezip(int checkfor_num, char character_listcheck){
    write(STDOUT_FILENO, &checkfor_num, sizeof(checkfor_num));
    write(STDOUT_FILENO, &character_listcheck, sizeof(character_listcheck) );
}
//writing the next term with finding 
int main(int argc, char *argv[]) {
    
    if (argc < 2) {
        std::cout << "wzip: file1 [file2 ...]\n";
        return 1;
    }//check for finding the next term 


    char checkfor_character = 0;
    int checkfor_num = 0;
//for the list that comes with the overall check 
    for(int i = 1; i < argc ; ++i) {
        int filename = open(argv[i], O_RDONLY);
        
        if (filename == -1){
            std::cout << "wzip: cannot open file\n";
            return 1;
        }//check for finding the next term that comes after


//lists that change the overall appearance 






        char character_listcheck;
        ssize_t reading_bytes;

        while ((reading_bytes = read(filename, &character_listcheck, 1)) > 0) {
            if (character_listcheck == checkfor_character) {
                checkfor_num++;
            } else {
                if (checkfor_num > 0) {
                    finding_thezip(checkfor_num, checkfor_character);
                }
                checkfor_character = character_listcheck;
                checkfor_num = 1;
            }//check for finding what happens after list

        }

        close(filename);
    }//check for finding file name


    if (checkfor_num > 0) {
        finding_thezip(checkfor_num, checkfor_character);
    }//check for finding number


    return 0;
}