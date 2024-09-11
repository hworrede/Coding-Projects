#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <cstring>

#include "LocalFileSystem.h"
#include "Disk.h"
#include "ufs.h"

using namespace std;

void printDirectory(LocalFileSystem &fs, int checking_Inode, const string &path) {

    inode_t checkingtheNextInode;
    if (fs.stat(checking_Inode, &checkingtheNextInode) != 0) {
        cerr << "ERROR" << endl;
        return;
    }//checking for the intial errors that come from this file 

    if (checkingtheNextInode.type != UFS_DIRECTORY) {
        cerr << "ERROR" << endl;
        return;
    }//checking for the intial errors that come from this file 

    vector<dir_ent_t> entries(checkingtheNextInode.size / sizeof(dir_ent_t));
    fs.read(checking_Inode, entries.data(), checkingtheNextInode.size);
//We need to find that there is a entry 
    
    cout << "Directory " << path << endl;
//We need to find that there is a entry 

    vector<dir_ent_t> makeSure_perfect;
    for (const auto &entry : entries) {
        if (entry.inum != -1) {//We need to find that there is a entry 

            makeSure_perfect.push_back(entry);
        }//We need to find that there is a entry 

    }//   sort(makeSure_perfect.begin(), makeSure_perfect.end(), [](const dir_ent_t &a, const dir_ent_t &b) {
//         return strcmp(a.name, b.name) < 0;
//     });

    sort(makeSure_perfect.begin(), makeSure_perfect.end(), [](const dir_ent_t &a, const dir_ent_t &b) {
        return strcmp(a.name, b.name) < 0;
    });

//   sort(makeSure_perfect.begin(), makeSure_perfect.end(), [](const dir_ent_t &a, const dir_ent_t &b) {
//         return strcmp(a.name, b.name) < 0;
//     });
    for (const auto &entry : makeSure_perfect) {
        cout << entry.inum << "\t" << entry.name << endl;
    }//We need to find that there is a entry 

    cout << endl;
//We need to find that there is a entry 

    for (const auto &entry : makeSure_perfect) {
        if (strcmp(entry.name, ".") != 0 && strcmp(entry.name, "..") != 0) {
            inode_t find_node;//We need to find that there is a entry 
            if (fs.stat(entry.inum, &find_node) == 0 && find_node.type == UFS_DIRECTORY) {
                //We need to find that there is a entry 
                printDirectory(fs, entry.inum, path + entry.name + "/");
            }//We need to find that there is a entry 
        }
    }
}

//   for (const auto &entry : makeSure_perfect) {
//         if (strcmp(entry.name, ".") != 0 && strcmp(entry.name, "..") != 0) {
//             inode_t find_node;

int main(int argc, char *argv[]) {
    if (argc != 2) {//We need to find that there is a entry 
        cout << argv[0] << ": diskImageFile" << endl;
        return 1;//We need to find that there is a entry 
    }

    string checking_forImageFile = argv[1];
//We need to find that there is a entry 
    Disk disk(checking_forImageFile, UFS_BLOCK_SIZE);
    LocalFileSystem fs(&disk);

    //check for final prep
    printDirectory(fs, UFS_ROOT_DIRECTORY_INODE_NUMBER, "/");

    return 0;
}
