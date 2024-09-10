#include <iostream>
#include <string>
#include <vector>
#include <cassert>
#include <cstring>
#include <cmath>
#include <algorithm>
#include <iterator>
#include "LocalFileSystem.h"
#include "ufs.h"

using namespace std;

LocalFileSystem::LocalFileSystem(Disk *disk) {
  this->disk = disk;
}
//what is the overall change that is needed
// In order for the code to work
//we can see that this is true

void LocalFileSystem::readSuperBlock(super_t *findnextSuper) {
    char tryingtoBlock[UFS_BLOCK_SIZE];
    disk->readBlock(0, tryingtoBlock);
    memcpy(findnextSuper, tryingtoBlock, sizeof(super_t));
}//what is the overall change that is needed
// In order for the code to work
//we can see that this is true

int LocalFileSystem::lookup(int checkforTheNum, std::string name) {
    super_t checkforMainBlock;
    readSuperBlock(&checkforMainBlock);

    if (checkforTheNum < 0 || checkforTheNum >= checkforMainBlock.num_inodes) {
        return -EINVALIDINODE;
    }// for (int findtheDirectIndex = 0; findtheDirectIndex < DIRECT_PTRS; ++findtheDirectIndex) {
//         if (finaltarger->direct[findtheDirectIndex] != 0) {
//             int Number_escape = finaltarger->direct[findtheDirectIndex];
//             int findtheNextIndex = Number_escape / 8;
//             int findtheBitIndex = Number_escape % 8;
//             findingNextBit_data[findtheNextIndex] &= ~(1 << findtheBitIndex);
//         }

    inode_t *checkForArray = new inode_t[checkforMainBlock.num_inodes];
    readInodeRegion(&checkforMainBlock, checkForArray);

    inode_t *MainTopInode = &checkForArray[checkforTheNum];
    if (MainTopInode->type != UFS_DIRECTORY) {
        delete[] checkForArray;
        return -EINVALIDINODE;
    }

    char tryingtoBlock[UFS_BLOCK_SIZE];
    int checktheBlocks = ceil(static_cast<double>(MainTopInode->size) / UFS_BLOCK_SIZE);

   
   for (int i = 0; i < checktheBlocks; ++i) {
    if (MainTopInode->direct[i] == 0) {
        continue;
    }// for (int findtheDirectIndex = 0; findtheDirectIndex < DIRECT_PTRS; ++findtheDirectIndex) {
//         if (finaltarger->direct[findtheDirectIndex] != 0) {
//             int Number_escape = finaltarger->direct[findtheDirectIndex];
//             int findtheNextIndex = Number_escape / 8;
//             int findtheBitIndex = Number_escape % 8;
//             findingNextBit_data[findtheNextIndex] &= ~(1 << findtheBitIndex);
//         }

    disk->readBlock(MainTopInode->direct[i], tryingtoBlock);

    size_t checkEnt = UFS_BLOCK_SIZE / sizeof(dir_ent_t);
    for (size_t needed_index = 0; needed_index < checkEnt; ++needed_index) {
        dir_ent_t *findNextentry = reinterpret_cast<dir_ent_t *>(tryingtoBlock + needed_index * sizeof(dir_ent_t));

        if (findNextentry->inum != 0 && name == findNextentry->name) {
            int foundNextNum = findNextentry->inum;
            delete[] checkForArray;
            return foundNextNum;
        }
    }
}

    delete[] checkForArray;
    return -ENOTFOUND;
}//what is the overall change that is needed
// In order for the code to work
//we can see that this is true

int LocalFileSystem::stat(int checkforNumber_inode, inode_t *activateData) {
    super_t checkforMainBlock;
    readSuperBlock(&checkforMainBlock);

    if (checkforNumber_inode < 0 || checkforNumber_inode >= checkforMainBlock.num_inodes) {
        return -EINVALIDINODE;
    }
// for (int findtheDirectIndex = 0; findtheDirectIndex < DIRECT_PTRS; ++findtheDirectIndex) {
//         if (finaltarger->direct[findtheDirectIndex] != 0) {
//             int Number_escape = finaltarger->direct[findtheDirectIndex];
//             int findtheNextIndex = Number_escape / 8;
//             int findtheBitIndex = Number_escape % 8;
//             findingNextBit_data[findtheNextIndex] &= ~(1 << findtheBitIndex);
//         }
    inode_t *checkForArray = new inode_t[checkforMainBlock.num_inodes];
    readInodeRegion(&checkforMainBlock, checkForArray);

    *activateData = checkForArray[checkforNumber_inode];

    delete[] checkForArray;
    return 0;
}

//what is the overall change that is needed
// In order for the code to work
//we can see that this is true


//Read file 
int LocalFileSystem::read(int checkforNumber_inode, void *buffer, int size) {
    if (size < 0 || size > MAX_FILE_SIZE) {
        return -EINVALIDSIZE;
    }
// for (int findtheDirectIndex = 0; findtheDirectIndex < DIRECT_PTRS; ++findtheDirectIndex) {
//         if (finaltarger->direct[findtheDirectIndex] != 0) {
//             int Number_escape = finaltarger->direct[findtheDirectIndex];
//             int findtheNextIndex = Number_escape / 8;
//             int findtheBitIndex = Number_escape % 8;
//             findingNextBit_data[findtheNextIndex] &= ~(1 << findtheBitIndex);
//         }
    inode_t activateData;
    int findNextResult = stat(checkforNumber_inode, &activateData);
    if (findNextResult != 0) {
        return -EINVALIDINODE;
    }

    if (activateData.type != UFS_REGULAR_FILE && activateData.type != UFS_DIRECTORY) {
        return -EINVALIDTYPE;
    }

    size = std::min(size, activateData.size);

    int inorderforRead = 0;
    char *inorderforBuff = static_cast<char *>(buffer);
    int checkInd = 0;
    while (checkInd < DIRECT_PTRS && inorderforRead < size) {
        if (activateData.direct[checkInd] == 0) {
            break;
        }

        int checkadr = activateData.direct[checkInd];
        int check_BtyesforR = std::min(size - inorderforRead, UFS_BLOCK_SIZE);
        char tryingtoBlock[UFS_BLOCK_SIZE];

        disk->readBlock(checkadr, tryingtoBlock);
        
        memcpy(inorderforBuff + inorderforRead, tryingtoBlock, check_BtyesforR);
        inorderforRead += check_BtyesforR;

        ++checkInd;
    }// for (int findtheDirectIndex = 0; findtheDirectIndex < DIRECT_PTRS; ++findtheDirectIndex) {
//         if (finaltarger->direct[findtheDirectIndex] != 0) {
//             int Number_escape = finaltarger->direct[findtheDirectIndex];
//             int findtheNextIndex = Number_escape / 8;
//             int findtheBitIndex = Number_escape % 8;
//             findingNextBit_data[findtheNextIndex] &= ~(1 << findtheBitIndex);
//         }

    return inorderforRead;
}
bool isBlockFree(const unsigned char* bitmap, int index) {
    return (bitmap[index / 8] & (1 << (index % 8))) == 0;
}
void markBlockAsUsed(unsigned char* bitmap, int index) {
    bitmap[index / 8] |= (1 << (index % 8));
}// for (int findtheDirectIndex = 0; findtheDirectIndex < DIRECT_PTRS; ++findtheDirectIndex) {
//         if (finaltarger->direct[findtheDirectIndex] != 0) {
//             int Number_escape = finaltarger->direct[findtheDirectIndex];
//             int findtheNextIndex = Number_escape / 8;
//             int findtheBitIndex = Number_escape % 8;
//             findingNextBit_data[findtheNextIndex] &= ~(1 << findtheBitIndex);
//         }

int findFreeBlock(unsigned char *findingNextBit_data, int numData) {
    for (int index = 0; index < numData; ++index) {
        if ((findingNextBit_data[index / 8] & (1 << (index % 8))) == 0) {
            findingNextBit_data[index / 8] |= (1 << (index % 8));
            return index;
        }
    }
    return -1;
}
void createDirEntry(dir_ent_t &findNextentry, int inum, const char *name) {
    findNextentry.inum = inum;
    strncpy(findNextentry.name, name, sizeof(findNextentry.name));
    findNextentry.name[sizeof(findNextentry.name) - 1] = '\0';
}

//Create 
int LocalFileSystem::create(int checkforTheNum, int check_eachtype, std::string CreateName) {
    if (CreateName == "." || CreateName == ".." || CreateName.empty() || CreateName.length() > DIR_ENT_NAME_SIZE) {
        return -EINVALIDNAME;
    }

    if (check_eachtype != UFS_REGULAR_FILE && check_eachtype != UFS_DIRECTORY) {
        return -EINVALIDTYPE;
    }
// for (int findtheDirectIndex = 0; findtheDirectIndex < DIRECT_PTRS; ++findtheDirectIndex) {
//         if (finaltarger->direct[findtheDirectIndex] != 0) {
//             int Number_escape = finaltarger->direct[findtheDirectIndex];
//             int findtheNextIndex = Number_escape / 8;
//             int findtheBitIndex = Number_escape % 8;
//             findingNextBit_data[findtheNextIndex] &= ~(1 << findtheBitIndex);
//         }
    super_t checkforMainBlock;
    readSuperBlock(&checkforMainBlock);

    if (checkforTheNum < 0 || checkforTheNum >= checkforMainBlock.num_inodes) {
        return -EINVALIDINODE;
    }

    inode_t *checkForArray = new inode_t[checkforMainBlock.num_inodes];
    readInodeRegion(&checkforMainBlock, checkForArray);

    inode_t *MainTopInode = &checkForArray[checkforTheNum];
    if (MainTopInode->type != UFS_DIRECTORY) {
        delete[] checkForArray;
        return -EINVALIDINODE;
    }
// for (int findtheDirectIndex = 0; findtheDirectIndex < DIRECT_PTRS; ++findtheDirectIndex) {
//         if (finaltarger->direct[findtheDirectIndex] != 0) {
//             int Number_escape = finaltarger->direct[findtheDirectIndex];
//             int findtheNextIndex = Number_escape / 8;
//             int findtheBitIndex = Number_escape % 8;
//             findingNextBit_data[findtheNextIndex] &= ~(1 << findtheBitIndex);
//         }
    int checkforEnt_num = MainTopInode->size / sizeof(dir_ent_t);

    std::vector<dir_ent_t> dirEntries(checkforEnt_num);
    read(checkforTheNum, dirEntries.data(), MainTopInode->size);

    for (size_t i = 0; i < dirEntries.size(); ++i) {
        if (strcmp(dirEntries[i].name, CreateName.c_str()) == 0) {
            if (dirEntries[i].inum != -1 && checkForArray[dirEntries[i].inum].type == check_eachtype) {
                delete[] checkForArray;
                return dirEntries[i].inum;
            } else {
                delete[] checkForArray;
                return -EEXIST;
            }
        }
}// for (int findtheDirectIndex = 0; findtheDirectIndex < DIRECT_PTRS; ++findtheDirectIndex) {
//         if (finaltarger->direct[findtheDirectIndex] != 0) {
//             int Number_escape = finaltarger->direct[findtheDirectIndex];
//             int findtheNextIndex = Number_escape / 8;
//             int findtheBitIndex = Number_escape % 8;
//             findingNextBit_data[findtheNextIndex] &= ~(1 << findtheBitIndex);
//         }

    int checkforMainNum = -1;
    unsigned char findingnextIncode[UFS_BLOCK_SIZE * checkforMainBlock.inode_bitmap_len];
    readInodeBitmap(&checkforMainBlock, findingnextIncode);
    for (int maininode = 0; maininode < checkforMainBlock.num_inodes; ++maininode) {
        if ((findingnextIncode[maininode / 8] & (1 << (maininode % 8))) == 0) {
            checkforMainNum = maininode;
            findingnextIncode[maininode / 8] |= (1 << (maininode % 8));
            break;
        }
    }
// for (int findtheDirectIndex = 0; findtheDirectIndex < DIRECT_PTRS; ++findtheDirectIndex) {
//         if (finaltarger->direct[findtheDirectIndex] != 0) {
//             int Number_escape = finaltarger->direct[findtheDirectIndex];
//             int findtheNextIndex = Number_escape / 8;
//             int findtheBitIndex = Number_escape % 8;
//             findingNextBit_data[findtheNextIndex] &= ~(1 << findtheBitIndex);
//         }
    if (checkforMainNum == -1) {
        delete[] checkForArray;
        return -ENOTENOUGHSPACE;
    }
    //what is the overall change that is needed
// In order for the code to work
//we can see that this is true

    inode_t &next_in = checkForArray[checkforMainNum];
    memset(&next_in, 0, sizeof(inode_t));

    next_in.type = check_eachtype;
    next_in.size = 0;

    if (check_eachtype == UFS_DIRECTORY) {
    std::vector<dir_ent_t> directoryEntries;

    // Create 
    dir_ent_t thecurrent_next, Main_par;
    createDirEntry(thecurrent_next, checkforMainNum, ".");
    createDirEntry(Main_par, checkforTheNum, "..");
    directoryEntries.push_back(thecurrent_next);
    directoryEntries.push_back(Main_par);
// for (int findtheDirectIndex = 0; findtheDirectIndex < DIRECT_PTRS; ++findtheDirectIndex) {
//         if (finaltarger->direct[findtheDirectIndex] != 0) {
//             int Number_escape = finaltarger->direct[findtheDirectIndex];
//             int findtheNextIndex = Number_escape / 8;
//             int findtheBitIndex = Number_escape % 8;
//             findingNextBit_data[findtheNextIndex] &= ~(1 << findtheBitIndex);
//         }
    // Read 
    unsigned char findingNextBit_data[UFS_BLOCK_SIZE * checkforMainBlock.data_bitmap_len];
    readDataBitmap(&checkforMainBlock, findingNextBit_data);

    // Find 
    int NextistheBlock = findFreeBlock(findingNextBit_data, checkforMainBlock.num_data);
    if (NextistheBlock == -1) {
        delete[] checkForArray;
        return -ENOTENOUGHSPACE;
    }

    // Update inode and write block
    next_in.direct[0] = checkforMainBlock.data_region_addr + NextistheBlock;
    disk->writeBlock(next_in.direct[0], directoryEntries.data());
    writeDataBitmap(&checkforMainBlock, findingNextBit_data);

    next_in.size += directoryEntries.size() * sizeof(dir_ent_t);
}
// for (int findtheDirectIndex = 0; findtheDirectIndex < DIRECT_PTRS; ++findtheDirectIndex) {
//         if (finaltarger->direct[findtheDirectIndex] != 0) {
//             int Number_escape = finaltarger->direct[findtheDirectIndex];
//             int findtheNextIndex = Number_escape / 8;
//             int findtheBitIndex = Number_escape % 8;
//             findingNextBit_data[findtheNextIndex] &= ~(1 << findtheBitIndex);
//         }
    dir_ent_t checkforNextEnt;
    checkforNextEnt.inum = checkforMainNum;
    strncpy(checkforNextEnt.name, CreateName.c_str(), sizeof(checkforNextEnt.name));
    checkforNextEnt.name[sizeof(checkforNextEnt.name) - 1] = '\0';
    dirEntries.push_back(checkforNextEnt);
//what is the overall change that is needed
// In order for the code to work
//we can see that this is true
    int overallBlock_num = (MainTopInode->size + UFS_BLOCK_SIZE - 1) / UFS_BLOCK_SIZE;
    int checkedBlock_num = ((MainTopInode->size + sizeof(dir_ent_t)) + UFS_BLOCK_SIZE - 1) / UFS_BLOCK_SIZE;

      if (checkedBlock_num > overallBlock_num) {
        unsigned char findingNextBit_data[UFS_BLOCK_SIZE * checkforMainBlock.data_bitmap_len];
        readDataBitmap(&checkforMainBlock, findingNextBit_data);
// for (int findtheDirectIndex = 0; findtheDirectIndex < DIRECT_PTRS; ++findtheDirectIndex) {
//         if (finaltarger->direct[findtheDirectIndex] != 0) {
//             int Number_escape = finaltarger->direct[findtheDirectIndex];
//             int findtheNextIndex = Number_escape / 8;
//             int findtheBitIndex = Number_escape % 8;
//             findingNextBit_data[findtheNextIndex] &= ~(1 << findtheBitIndex);
//         }
        // find the correct list
        int findNextNumber = -1;
        for (int forOverall_In = 0; forOverall_In < checkforMainBlock.num_data; ++forOverall_In) {
            if (isBlockFree(findingNextBit_data, forOverall_In)) {
                markBlockAsUsed(findingNextBit_data, forOverall_In);
                findNextNumber = forOverall_In;
                break;
            }
        }

        if (findNextNumber == -1) {
            delete[] checkForArray;
            return -ENOTENOUGHSPACE;
        }

        MainTopInode->direct[overallBlock_num] = checkforMainBlock.data_region_addr + findNextNumber;
        writeDataBitmap(&checkforMainBlock, findingNextBit_data);
    }

    MainTopInode->size += sizeof(dir_ent_t);
    int enterMainBlock = UFS_BLOCK_SIZE / sizeof(dir_ent_t);
    int needed_index = 0;
    while (needed_index < static_cast<int>(dirEntries.size())) {
        char tryingtoBlock[UFS_BLOCK_SIZE] = {0};
        int see_same = std::min(enterMainBlock, static_cast<int>(dirEntries.size()) - needed_index);
        memcpy(tryingtoBlock, &dirEntries[needed_index], see_same * sizeof(dir_ent_t));
        disk->writeBlock(MainTopInode->direct[needed_index / enterMainBlock], tryingtoBlock);
        needed_index += enterMainBlock;
    }

    writeInodeRegion(&checkforMainBlock, checkForArray);
    writeInodeBitmap(&checkforMainBlock, findingnextIncode);

    delete[] checkForArray;
    return checkforMainNum;
}

// for (int findtheDirectIndex = 0; findtheDirectIndex < DIRECT_PTRS; ++findtheDirectIndex) {
//         if (finaltarger->direct[findtheDirectIndex] != 0) {
//             int Number_escape = finaltarger->direct[findtheDirectIndex];
//             int findtheNextIndex = Number_escape / 8;
//             int findtheBitIndex = Number_escape % 8;
//             findingNextBit_data[findtheNextIndex] &= ~(1 << findtheBitIndex);
//         }
//write 
int LocalFileSystem::write(int checkforNumber_inode, const void *dataBuffer, int size) {
    if (size < 0 || size > MAX_FILE_SIZE) {
        return -EINVALIDSIZE;
    }

    super_t checkforMainBlock;
    readSuperBlock(&checkforMainBlock);

    inode_t activateData;
    int findNextResult = stat(checkforNumber_inode, &activateData);

    if (findNextResult < 0) {
        return findNextResult;
    }

    if (activateData.type != UFS_REGULAR_FILE) {
        return -EWRITETODIR;
    }// for (int findtheDirectIndex = 0; findtheDirectIndex < DIRECT_PTRS; ++findtheDirectIndex) {
//         if (finaltarger->direct[findtheDirectIndex] != 0) {
//             int Number_escape = finaltarger->direct[findtheDirectIndex];
//             int findtheNextIndex = Number_escape / 8;
//             int findtheBitIndex = Number_escape % 8;
//             findingNextBit_data[findtheNextIndex] &= ~(1 << findtheBitIndex);
//         }

    int Need_theOverallBlock = (size + UFS_BLOCK_SIZE - 1) / UFS_BLOCK_SIZE;
    if (Need_theOverallBlock > DIRECT_PTRS) {
        return -EINVALIDSIZE;
    }

    unsigned char findingNextBit_data[UFS_BLOCK_SIZE];
    readDataBitmap(&checkforMainBlock, findingNextBit_data);
//what is the overall change that is needed
// In order for the code to work
//we can see that this is true
    vector<int> checkMainBlocking;
    int forOverall_In = 0;
    while (forOverall_In < checkforMainBlock.num_data && static_cast<int>(checkMainBlocking.size()) < Need_theOverallBlock) {
        if ((findingNextBit_data[forOverall_In / 8] & (1 << (forOverall_In % 8))) == 0) {
            checkMainBlocking.push_back(forOverall_In);
        }
        ++forOverall_In;
    }// for (int findtheDirectIndex = 0; findtheDirectIndex < DIRECT_PTRS; ++findtheDirectIndex) {
//         if (finaltarger->direct[findtheDirectIndex] != 0) {
//             int Number_escape = finaltarger->direct[findtheDirectIndex];
//             int findtheNextIndex = Number_escape / 8;
//             int findtheBitIndex = Number_escape % 8;
//             findingNextBit_data[findtheNextIndex] &= ~(1 << findtheBitIndex);
//         }

    if (static_cast<int>(checkMainBlocking.size()) < Need_theOverallBlock) {
        return -ENOTENOUGHSPACE;
    }

    int now_block = 0;
    int checkInd = 0;
    while (checkInd < DIRECT_PTRS && now_block < Need_theOverallBlock) {
        if (activateData.direct[checkInd] == 0) {
            int Number_escape = checkMainBlocking[now_block++];
            findingNextBit_data[Number_escape / 8] |= (1 << (Number_escape % 8));
            activateData.direct[checkInd] = checkforMainBlock.data_region_addr + Number_escape;
        }
        ++checkInd;
    }

    writeDataBitmap(&checkforMainBlock, findingNextBit_data);

    const char *buffer = static_cast<const char *>(dataBuffer);
    for (int Index_checkEscape = 0; Index_checkEscape < Need_theOverallBlock; ++Index_checkEscape) {
        int checkFotOverallset = Index_checkEscape * UFS_BLOCK_SIZE;
        int Find_sizeNext = std::min(size - checkFotOverallset, UFS_BLOCK_SIZE);
        char tryingtoBlock[UFS_BLOCK_SIZE] = {0};
        std::memcpy(tryingtoBlock, buffer + checkFotOverallset, Find_sizeNext);
        disk->writeBlock(activateData.direct[Index_checkEscape], tryingtoBlock);
    }

    activateData.size = size;

    inode_t checkForArray[checkforMainBlock.num_inodes];
    readInodeRegion(&checkforMainBlock, checkForArray);
    checkForArray[checkforNumber_inode] = activateData;
    writeInodeRegion(&checkforMainBlock, checkForArray);

    return size;
    // for (int findtheDirectIndex = 0; findtheDirectIndex < DIRECT_PTRS; ++findtheDirectIndex) {
//         if (finaltarger->direct[findtheDirectIndex] != 0) {
//             int Number_escape = finaltarger->direct[findtheDirectIndex];
//             int findtheNextIndex = Number_escape / 8;
//             int findtheBitIndex = Number_escape % 8;
//             findingNextBit_data[findtheNextIndex] &= ~(1 << findtheBitIndex);
//         }
}
void readDirectoryEntries(Disk *disk, const inode_t *inode, std::vector<dir_ent_t> &entries) {
    int checkSubforBlocks = UFS_BLOCK_SIZE / sizeof(dir_ent_t);
    int checkforEntryCounts = inode->size / sizeof(dir_ent_t);
    entries.resize(checkforEntryCounts);

    for (int Index_checkEscape = 0; Index_checkEscape < (checkforEntryCounts + checkSubforBlocks - 1) / checkSubforBlocks; ++Index_checkEscape) {
        char tryingtoBlock[UFS_BLOCK_SIZE];
        disk->readBlock(inode->direct[Index_checkEscape], tryingtoBlock);

        int entriesInThisBlock = std::min(checkSubforBlocks, checkforEntryCounts - Index_checkEscape * checkSubforBlocks);
        std::memcpy(&entries[Index_checkEscape * checkSubforBlocks], tryingtoBlock, entriesInThisBlock * sizeof(dir_ent_t));
    }
}

bool hasNonSpecialEntries(const std::vector<dir_ent_t> &entries) {
    return std::any_of(entries.begin(), entries.end(), [](const dir_ent_t &findNextentry) {
        return findNextentry.inum != -1 && strcmp(findNextentry.name, ".") != 0 && strcmp(findNextentry.name, "..") != 0;
    });
}
// for (int findtheDirectIndex = 0; findtheDirectIndex < DIRECT_PTRS; ++findtheDirectIndex) {
//         if (finaltarger->direct[findtheDirectIndex] != 0) {
//             int Number_escape = finaltarger->direct[findtheDirectIndex];
//             int findtheNextIndex = Number_escape / 8;
//             int findtheBitIndex = Number_escape % 8;
//             findingNextBit_data[findtheNextIndex] &= ~(1 << findtheBitIndex);
//         }

//this is for the unlink
int LocalFileSystem::unlink(int checkforTheNum, std::string CreateName) {
    if (CreateName == "." || CreateName == "..") {
        return -EUNLINKNOTALLOWED;
    }
//what is the overall change that is needed
// In order for the code to work
//we can see that this is true
    super_t checkforMainBlock;
    readSuperBlock(&checkforMainBlock);

    if (checkforTheNum < 0 || checkforTheNum >= checkforMainBlock.num_inodes) {
        return -EINVALIDINODE;
    }//what is the overall change that is needed
// In order for the code to work
//we can see that this is true

    inode_t *checkForArray = new inode_t[checkforMainBlock.num_inodes];
    readInodeRegion(&checkforMainBlock, checkForArray);

    inode_t *MainTopInode = &checkForArray[checkforTheNum];
    if (MainTopInode->type != UFS_DIRECTORY) {
        delete[] checkForArray;
        return -EINVALIDINODE;
    }

    int checkforEnt_num = MainTopInode->size / sizeof(dir_ent_t);
    std::vector<dir_ent_t> dirEntries(checkforEnt_num);
    int enterMainBlock = UFS_BLOCK_SIZE / sizeof(dir_ent_t);

    for (int Index_checkEscape = 0; Index_checkEscape < (checkforEnt_num + enterMainBlock - 1) / enterMainBlock; ++Index_checkEscape) {
        char tryingtoBlock[UFS_BLOCK_SIZE];
        disk->readBlock(MainTopInode->direct[Index_checkEscape], tryingtoBlock);
        for (int Index_select = 0; Index_select < enterMainBlock && Index_checkEscape * enterMainBlock + Index_select < checkforEnt_num; ++Index_select) {
            memcpy(&dirEntries[Index_checkEscape * enterMainBlock + Index_select], tryingtoBlock + Index_select * sizeof(dir_ent_t), sizeof(dir_ent_t));
        }
    }//what is the overall change that is needed
// In order for the code to work
//we can see that this is true

    auto check_auto = std::find_if(dirEntries.begin(), dirEntries.end(), [&CreateName](const dir_ent_t &findNextentry) {
    return findNextentry.inum != -1 && strcmp(findNextentry.name, CreateName.c_str()) == 0;
    });

    bool checkfor_location = (check_auto != dirEntries.end());
    inode_t *finaltarger = nullptr;
    int checkInodeforTarget = -1;
    int checkentryforTarget = -1;

    if (checkfor_location) {
        checkentryforTarget = std::distance(dirEntries.begin(), check_auto);
        checkInodeforTarget = check_auto->inum;
        finaltarger = &checkForArray[checkInodeforTarget];
    }

    if (!checkfor_location) {
        delete[] checkForArray;
        return 0;
    }
// for (int findtheDirectIndex = 0; findtheDirectIndex < DIRECT_PTRS; ++findtheDirectIndex) {
//         if (finaltarger->direct[findtheDirectIndex] != 0) {
//             int Number_escape = finaltarger->direct[findtheDirectIndex];
//             int findtheNextIndex = Number_escape / 8;
//             int findtheBitIndex = Number_escape % 8;
//             findingNextBit_data[findtheNextIndex] &= ~(1 << findtheBitIndex);
//         }
    if (finaltarger->type == UFS_DIRECTORY) {
    std::vector<dir_ent_t> check_entries;
    readDirectoryEntries(disk, finaltarger, check_entries);

    if (hasNonSpecialEntries(check_entries)) {
        delete[] checkForArray;
        return -EDIRNOTEMPTY;
    }// for (int findtheDirectIndex = 0; findtheDirectIndex < DIRECT_PTRS; ++findtheDirectIndex) {
//         if (finaltarger->direct[findtheDirectIndex] != 0) {
//             int Number_escape = finaltarger->direct[findtheDirectIndex];
//             int findtheNextIndex = Number_escape / 8;
//             int findtheBitIndex = Number_escape % 8;
//             findingNextBit_data[findtheNextIndex] &= ~(1 << findtheBitIndex);
//         }
}

    dirEntries[checkentryforTarget].inum = -1;
    dirEntries.erase(dirEntries.begin() + checkentryforTarget);

    int overall_blockcount = (MainTopInode->size + UFS_BLOCK_SIZE - 1) / UFS_BLOCK_SIZE;
    int neededSizes = MainTopInode->size - sizeof(dir_ent_t);
    int made_blocksfornum = (neededSizes + UFS_BLOCK_SIZE - 1) / UFS_BLOCK_SIZE;

    MainTopInode->size = neededSizes;

    if (made_blocksfornum < overall_blockcount) {
        unsigned char findingNextBit_data[UFS_BLOCK_SIZE * checkforMainBlock.data_bitmap_len];
        readDataBitmap(&checkforMainBlock, findingNextBit_data);

        int lastBlockIdx = overall_blockcount - 1;
        int Number_escape = MainTopInode->direct[lastBlockIdx];
        MainTopInode->direct[lastBlockIdx] = 0;

        int findtheNextIndex = Number_escape / 8;
        int findtheBitIndex = Number_escape % 8;
        findingNextBit_data[findtheNextIndex] &= ~(1 << findtheBitIndex);

        writeDataBitmap(&checkforMainBlock, findingNextBit_data);
        // for (int findtheDirectIndex = 0; findtheDirectIndex < DIRECT_PTRS; ++findtheDirectIndex) {
//         if (finaltarger->direct[findtheDirectIndex] != 0) {
//             int Number_escape = finaltarger->direct[findtheDirectIndex];
//             int findtheNextIndex = Number_escape / 8;
//             int findtheBitIndex = Number_escape % 8;
//             findingNextBit_data[findtheNextIndex] &= ~(1 << findtheBitIndex);
//         }
    }

    int Index_checkEscape = 0;
    for (int Index_select = 0; Index_select < checkforEnt_num; Index_select += enterMainBlock) {
        char tryingtoBlock[UFS_BLOCK_SIZE] = {0};
        int see_same = std::min(enterMainBlock, checkforEnt_num - Index_select);
        memcpy(tryingtoBlock, &dirEntries[Index_select], see_same * sizeof(dir_ent_t));
        disk->writeBlock(MainTopInode->direct[Index_checkEscape++], tryingtoBlock);
    }

    writeInodeRegion(&checkforMainBlock, checkForArray);

    std::vector<unsigned char> findingnextIncode(UFS_BLOCK_SIZE * checkforMainBlock.inode_bitmap_len);
    readInodeBitmap(&checkforMainBlock, findingnextIncode.data());

    int findtheNextIndex = checkInodeforTarget / 8;
    int findtheBitIndex = checkInodeforTarget % 8;
    findingnextIncode[findtheNextIndex] &= ~(1 << findtheBitIndex);
    // for (int findtheDirectIndex = 0; findtheDirectIndex < DIRECT_PTRS; ++findtheDirectIndex) {
//         if (finaltarger->direct[findtheDirectIndex] != 0) {
//             int Number_escape = finaltarger->direct[findtheDirectIndex];
//             int findtheNextIndex = Number_escape / 8;
//             int findtheBitIndex = Number_escape % 8;
//             findingNextBit_data[findtheNextIndex] &= ~(1 << findtheBitIndex);
//         }

    writeInodeBitmap(&checkforMainBlock, findingnextIncode.data());

    std::vector<unsigned char> findingNextBit_data(UFS_BLOCK_SIZE * checkforMainBlock.data_bitmap_len);
    readDataBitmap(&checkforMainBlock, findingNextBit_data.data());

    for (int findtheDirectIndex = 0; findtheDirectIndex < DIRECT_PTRS; ++findtheDirectIndex) {
        if (finaltarger->direct[findtheDirectIndex] != 0) {
            int Number_escape = finaltarger->direct[findtheDirectIndex];
            int findtheNextIndex = Number_escape / 8;
            int findtheBitIndex = Number_escape % 8;
            findingNextBit_data[findtheNextIndex] &= ~(1 << findtheBitIndex);
        }
    }//check for this code to work

    writeDataBitmap(&checkforMainBlock, findingNextBit_data.data());

    delete[] checkForArray;
    return 0;
}



///check for this code to work
void LocalFileSystem::readInodeBitmap(super_t *checkforMainBlock, unsigned char *findingnextIncode) {
    char tryingtoBlock[UFS_BLOCK_SIZE];
    for (int findtheBitIndex = 0; findtheBitIndex < checkforMainBlock->inode_bitmap_len; findtheBitIndex++) {
        disk->readBlock(checkforMainBlock->inode_bitmap_addr + findtheBitIndex, tryingtoBlock);
        memcpy(findingnextIncode + findtheBitIndex * UFS_BLOCK_SIZE, tryingtoBlock, UFS_BLOCK_SIZE);
    }
}
// for (int findtheDirectIndex = 0; findtheDirectIndex < DIRECT_PTRS; ++findtheDirectIndex) {
//         if (finaltarger->direct[findtheDirectIndex] != 0) {
//             int Number_escape = finaltarger->direct[findtheDirectIndex];
//             int findtheNextIndex = Number_escape / 8;
//             int findtheBitIndex = Number_escape % 8;
//             findingNextBit_data[findtheNextIndex] &= ~(1 << findtheBitIndex);
//         }

//check for this code to work
void LocalFileSystem::writeInodeBitmap(super_t *checkforMainBlock, unsigned char *findingnextIncode) {
    char tryingtoBlock[UFS_BLOCK_SIZE];//check for this code to work
    for (int findtheBitIndex = 0; findtheBitIndex < checkforMainBlock->inode_bitmap_len; findtheBitIndex++) {
        memcpy(tryingtoBlock, findingnextIncode + findtheBitIndex * UFS_BLOCK_SIZE, UFS_BLOCK_SIZE);
        disk->writeBlock(checkforMainBlock->inode_bitmap_addr + findtheBitIndex, tryingtoBlock);
    }
}

//check for this code to work
void LocalFileSystem::readDataBitmap(super_t *checkforMainBlock, unsigned char *findingNextBit_data) {
    char tryingtoBlock[UFS_BLOCK_SIZE];//check for this code to work
    for (int findtheBitIndex = 0; findtheBitIndex < checkforMainBlock->data_bitmap_len; findtheBitIndex++) {
        disk->readBlock(checkforMainBlock->data_bitmap_addr + findtheBitIndex, tryingtoBlock);
        memcpy(findingNextBit_data + findtheBitIndex * UFS_BLOCK_SIZE, tryingtoBlock, UFS_BLOCK_SIZE);
    }
}//what is the overall change that is needed
// In order for the code to work
//we can see that this is true

//check for this code to work
void LocalFileSystem::writeDataBitmap(super_t *checkforMainBlock, unsigned char *findingNextBit_data) {
    char tryingtoBlock[UFS_BLOCK_SIZE];
    for (int findtheBitIndex = 0; findtheBitIndex < checkforMainBlock->data_bitmap_len; findtheBitIndex++) {
        memcpy(tryingtoBlock, findingNextBit_data + findtheBitIndex * UFS_BLOCK_SIZE, UFS_BLOCK_SIZE);
        disk->writeBlock(checkforMainBlock->data_bitmap_addr + findtheBitIndex, tryingtoBlock);
    }
}//what is the overall change that is needed
// In order for the code to work
//we can see that this is true
//check for this code to work
void LocalFileSystem::readInodeRegion(super_t *checkforMainBlock, inode_t *checkForArray) {
    char tryingtoBlock[UFS_BLOCK_SIZE];
    for (int findtheAreaIndex = 0; findtheAreaIndex < checkforMainBlock->inode_region_len; findtheAreaIndex++) {
        disk->readBlock(checkforMainBlock->inode_region_addr + findtheAreaIndex, tryingtoBlock);
        memcpy(reinterpret_cast<char *>(checkForArray) + findtheAreaIndex * UFS_BLOCK_SIZE, tryingtoBlock, UFS_BLOCK_SIZE);
    }
}//what is the overall change that is needed
// In order for the code to work
//we can see that this is true
//check for this code to work
void LocalFileSystem::writeInodeRegion(super_t *checkforMainBlock, inode_t *checkForArray) {
    char tryingtoBlock[UFS_BLOCK_SIZE];
    for (int findtheAreaIndex = 0; findtheAreaIndex < checkforMainBlock->inode_region_len; findtheAreaIndex++) {
        memcpy(tryingtoBlock, reinterpret_cast<char *>(checkForArray) + findtheAreaIndex * UFS_BLOCK_SIZE, UFS_BLOCK_SIZE);
        disk->writeBlock(checkforMainBlock->inode_region_addr + findtheAreaIndex, tryingtoBlock);
    }
}





