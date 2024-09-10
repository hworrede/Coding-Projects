//ECS 150
//Hagos Worrede
#include <iostream>
#include <fstream>
#include <unistd.h>
#include <fcntl.h>
#include <cstring>
//overall the next check would be main 
int main(int argc, char* argv[]) {
    if (argc < 2) {
        std::cout << "wunzip: file1 [file2 ...]" << std :: endl;
        return 1;
//check for lists in this instance we can see that there is a file1 

    }

    for (int i = 1; i < argc; i++) {
        int findingterm = open(argv[i], O_RDONLY);
        
        if (findingterm < 0) {
            std :: cout << "wunzip: cannot open file" << std::endl;
            return 1;
//check for finding the next term 

        }
//check for lists 

        int for_listavail;
        char for_listofCharacter;
        while(read(findingterm, &for_listavail, sizeof(for_listavail)) == sizeof(for_listavail) && read(findingterm, &for_listofCharacter, sizeof(for_listofCharacter)) == sizeof(for_listofCharacter)) {
            for (int j = 0; j < for_listavail; j++) {
                write(STDOUT_FILENO, &for_listofCharacter, sizeof(for_listofCharacter));

            }//check for lists above the rest

        }//check for overall of the people with character


        close(findingterm);
    }
//check for lists 

    return 0;
}