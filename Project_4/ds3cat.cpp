#include <iostream>
#include <string>
#include <cstdlib>
#include <cmath> 
#include <vector>
#include <cassert>
#include <cstring> 

#include "LocalFileSystem.h"
#include "Disk.h"
#include "ufs.h"

#define UFS_DIRECT_BLOCKS 12

using namespace std;

int main(int argc, char *argv[]) {
    if (argc != 3) {
        cout << "Usage: " << argv[0] << " findtheImage findingtheinode" << endl;        
        return 1;
    }
//check for the next overall Imagereading
    std::string findtheImage = argv[1];
    uint32_t findingtheinode = std::stoi(argv[2]);
//next find the data that creates the better image. 
    Disk disk(findtheImage, UFS_BLOCK_SIZE);
    LocalFileSystem lfs(&disk);
//for the overall of the following events we need to find overall
    inode_t find_OverallStruct;
    int forOverallnext = lfs.stat(findingtheinode, &find_OverallStruct);
    if (forOverallnext < 0) {
        //for the overall of the following events we need to find overall

        return forOverallnext; 
    }
    //for the overall of the following events we need to find overall


    int find_nextBlock = find_OverallStruct.size / UFS_BLOCK_SIZE;
    //for the overall of the following events we need to find overall

    if ((find_OverallStruct.size % UFS_BLOCK_SIZE) != 0) {
        find_nextBlock += 1;
        //for the overall of the following events we need to find overall

    }
    std::cout << "File blocks" << std::endl;
    for (int i = 0; i < UFS_DIRECT_BLOCKS && i < find_nextBlock; ++i) {
        if (find_OverallStruct.direct[i] != 0) {
            std::cout << find_OverallStruct.direct[i] << std::endl;
            //for the overall of the following events we need to find overall

        }
    }
    //for the overall of the following events we need to find overall

    std::cout << std::endl;
//for the overall of the following events we need to find overall

    std::cout << "File data" << std::endl;

    char* forthenextBuffer = new char[find_OverallStruct.size];
//for the overall of the following events we need to find overall

    int bytes_read = 0;
    for (int i = 0; i < DIRECT_PTRS && bytes_read < find_OverallStruct.size; ++i) {
        if (find_OverallStruct.direct[i] == 0) {
            break; 
        }//for the overall of the following events we need to find overall


        int Overall_hide = find_OverallStruct.direct[i];
        int find_nextread = std::min(find_OverallStruct.size - bytes_read, UFS_BLOCK_SIZE);

        char block_data[UFS_BLOCK_SIZE];

        // int Overall_hide = find_OverallStruct.direct[i];
        // int find_nextread = std::min(find_OverallStruct.size - bytes_read, UFS_BLOCK_SIZE);

        // char block_data[UFS_BLOCK_SIZE];

        //for the overall of the following events we need to find overall

        disk.readBlock(Overall_hide, block_data);
        //for the overall of the following events we need to find overall

        memcpy(forthenextBuffer + bytes_read, block_data, find_nextread);
        bytes_read += find_nextread;
    }

   
    std::cout << forthenextBuffer;

    // print "file contents" at the end
    //std::cout << "file contents" << std::endl;

    
    delete[] forthenextBuffer;

    return 0;
}
