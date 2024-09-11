#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <cstring>
#include <sstream> 
#include "LocalFileSystem.h"
#include "Disk.h"
#include "ufs.h"
#include "DistributedFileSystemService.h"
#include "ClientError.h"
#include "WwwFormEncodedDict.h"

using namespace std;

void listDirectory(LocalFileSystem &find_mainfinal, int checkforIncode, const string &find_mainPath) {
    inode_t checkforTheNextData;
    int weNeedStatus = find_mainfinal.stat(checkforIncode, &checkforTheNextData);
    if (weNeedStatus < 0) {
        return;
    }//what is the overall change that is needed
// In order for the code to work
//we can see that this is true

    if (checkforTheNextData.type != UFS_DIRECTORY) {
        return;
    }//what is the overall change that is needed
// In order for the code to work
//we can see that this is true

    int checkfortheOverallcount = checkforTheNextData.size / sizeof(dir_ent_t);
    vector<dir_ent_t> directoryEntries(checkfortheOverallcount);
    weNeedStatus = find_mainfinal.read(checkforIncode, directoryEntries.data(), checkforTheNextData.size);
    if (weNeedStatus < 0) {
        return;
    }

    directoryEntries.erase(remove_if(directoryEntries.begin(), directoryEntries.end(),
                                     [](const dir_ent_t &checkfortheOverallentry) { return checkfortheOverallentry.inum == -1; }),
                           directoryEntries.end());

    sort(directoryEntries.begin(), directoryEntries.end(),
         [](const dir_ent_t &a, const dir_ent_t &b) { return strcmp(a.name, b.name) < 0; });
//what is the overall change that is needed
// In order for the code to work
//we can see that this is true
    cout << "Directory " << find_mainPath << endl;
    for (const dir_ent_t &checkfortheOverallentry : directoryEntries) {
        cout << checkfortheOverallentry.inum << "\t" << checkfortheOverallentry.name << endl;
    }

    cout << endl;
//what is the overall change that is needed
// In order for the code to work
//we can see that this is true
    for (const dir_ent_t &checkfortheOverallentry : directoryEntries) {
        if (strcmp(checkfortheOverallentry.name, ".") != 0 && strcmp(checkfortheOverallentry.name, "..") != 0) {
            string checkfortheOverallPath = find_mainPath + checkfortheOverallentry.name + "/";
            listDirectory(find_mainfinal, checkfortheOverallentry.inum, checkfortheOverallPath);
        }
    }
}

DistributedFileSystemService::DistributedFileSystemService(string diskFile) : HttpService("/ds3/") {
    this->fileSystem = new LocalFileSystem(new Disk(diskFile, UFS_BLOCK_SIZE));
}
//what is the overall change that is needed
// In order for the code to work
//we can see that this is true
void DistributedFileSystemService::get(HTTPRequest *request, HTTPResponse *response) {
    cout << "ERROR" << request->getPath() << endl;

    string find_mainPathrequest = request->getPath().substr(4);
    super_t create_overallBlock;
    fileSystem->readSuperBlock(&create_overallBlock);

    try {
        size_t NeedThe_NextSlash = find_mainPathrequest.find_last_of('/');
        int checkforOverallNode = UFS_ROOT_DIRECTORY_INODE_NUMBER;

        if (NeedThe_NextSlash != string::npos) {
            string NeedtheDirectPath = find_mainPathrequest.substr(0, NeedThe_NextSlash);
            vector<string> dirs = StringUtils::split(NeedtheDirectPath, '/');
            for (const string &dir : dirs) {
                int NeedtheincodePath = fileSystem->lookup(checkforOverallNode, dir);
                if (NeedtheincodePath < 0) {
                    if (NeedtheincodePath == -ENOTFOUND) {
                        cerr << "ERROR " << dir << endl;
                        throw ClientError::notFound();
                    } else {
                        cerr << "ERROR " << dir << endl;
                        throw ClientError::badRequest();
                    }//what is the overall change that is needed
// In order for the code to work
//we can see that this is true
                } else {
                    inode_t NeedtheincodeData;
                    fileSystem->stat(NeedtheincodePath, &NeedtheincodeData);
                    if (NeedtheincodeData.type != UFS_DIRECTORY) {
                        cerr << "Conflict: " << dir << " is not a directory." << endl;
                        throw ClientError::conflict();
                    }
                    checkforOverallNode = NeedtheincodePath;
                }
                // string find_mainSym = find_mainPathrequest.substr(NeedThe_NextSlash + 1);
//         if (find_mainSym.empty()) {
//             find_mainSym = ".";
//         }
//         int find_mainIncode = fileSystem->lookup(checkforOverallNode, find_mainSym);
//         if (find_mainIncode < 0) {
//             cerr << "Item not found: " << find_mainSym << endl;
//             throw ClientError::notFound();
//         }

//         inode_t CheckforTheItemData;
//         fileSystem->stat(find_mainIncode, &CheckforTheItemData);

//         if (CheckforTheItemData.type == UFS_REGULAR_FILE) {
//             char buffer[MAX_FILE_SIZE];
//             int CheckforTheByte = fileSystem->read(find_mainIncode, buffer, CheckforTheItemData.size);
//             response->setBody(string(buffer, CheckforTheByte));
//         } else if (CheckforTheItemData.type == UFS_DIRECTORY) {
//             char buffer[MAX_FILE_SIZE];
//             int CheckforTheByte = fileSystem->read(find_mainIncode, buffer, CheckforTheItemData.size);
            }
        }//what is the overall change that is needed
// In order for the code to work
//we can see that this is true

        string find_mainSym = find_mainPathrequest.substr(NeedThe_NextSlash + 1);
        if (find_mainSym.empty()) {
            find_mainSym = ".";
        }
        int find_mainIncode = fileSystem->lookup(checkforOverallNode, find_mainSym);
        if (find_mainIncode < 0) {
            cerr << "Item not found: " << find_mainSym << endl;
            throw ClientError::notFound();
        }
// string find_mainSym = find_mainPathrequest.substr(NeedThe_NextSlash + 1);
//         if (find_mainSym.empty()) {
//             find_mainSym = ".";
//         }
//         int find_mainIncode = fileSystem->lookup(checkforOverallNode, find_mainSym);
//         if (find_mainIncode < 0) {
//             cerr << "Item not found: " << find_mainSym << endl;
//             throw ClientError::notFound();
//         }

//         inode_t CheckforTheItemData;
//         fileSystem->stat(find_mainIncode, &CheckforTheItemData);

//         if (CheckforTheItemData.type == UFS_REGULAR_FILE) {
//             char buffer[MAX_FILE_SIZE];
//             int CheckforTheByte = fileSystem->read(find_mainIncode, buffer, CheckforTheItemData.size);
//             response->setBody(string(buffer, CheckforTheByte));
//         } else if (CheckforTheItemData.type == UFS_DIRECTORY) {
//             char buffer[MAX_FILE_SIZE];
//             int CheckforTheByte = fileSystem->read(find_mainIncode, buffer, CheckforTheItemData.size);
        inode_t CheckforTheItemData;
        fileSystem->stat(find_mainIncode, &CheckforTheItemData);

        if (CheckforTheItemData.type == UFS_REGULAR_FILE) {
            char buffer[MAX_FILE_SIZE];
            int CheckforTheByte = fileSystem->read(find_mainIncode, buffer, CheckforTheItemData.size);
            response->setBody(string(buffer, CheckforTheByte));
        } else if (CheckforTheItemData.type == UFS_DIRECTORY) {
            char buffer[MAX_FILE_SIZE];
            int CheckforTheByte = fileSystem->read(find_mainIncode, buffer, CheckforTheItemData.size);
//what is the overall change that is needed
// In order for the code to work
//we can see that this is true
            vector<string> entVect;
            dir_ent_t *CheckforTheentries = (dir_ent_t *)buffer;

            for (size_t i = 0; i < CheckforTheByte / sizeof(dir_ent_t); ++i) {
                if (CheckforTheentries[i].inum != 0 && CheckforTheentries[i].name[0] != '\0' && strcmp(CheckforTheentries[i].name, ".") != 0 && strcmp(CheckforTheentries[i].name, "..") != 0) {
                    string CheckforThename = CheckforTheentries[i].name;
                    inode_t CheckforTheIncodeInt;
                    fileSystem->stat(CheckforTheentries[i].inum, &CheckforTheIncodeInt);
                    if (CheckforTheIncodeInt.type == UFS_DIRECTORY) {
                        CheckforThename += "/";
                    }
                    entVect.push_back(CheckforThename);
                }
            }
//what is the overall change that is needed
// In order for the code to work
//we can see that this is true
            sort(entVect.begin(), entVect.end());
            stringstream CheckforTheList;
            for (const string &checkfortheOverallentry : entVect) {
                CheckforTheList << checkfortheOverallentry << "\n";
            }
            response->setBody(CheckforTheList.str());
        } else {
            cerr << "ERROR" << endl;
            throw ClientError::badRequest();
        }
//what is the overall change that is needed
// In order for the code to work
//we can see that this is true
    } catch (const ClientError &e) {
        cerr << "ERROR " << e.what() << endl;
        throw e;
    } catch (...) {
        cerr << "ERROR" << endl;
        throw ClientError::badRequest();
    }
}
//what is the overall change that is needed
// In order for the code to work
//we can see that this is true
void DistributedFileSystemService::put(HTTPRequest *request, HTTPResponse *response) {
    cout << "Processing PUT for: " << request->getPath() << endl;

    string find_mainPathrequest = request->getPath().substr(4);
    string mainList = request->getBody();

    super_t create_overallBlock;
    fileSystem->readSuperBlock(&create_overallBlock);

    listDirectory(*fileSystem, UFS_ROOT_DIRECTORY_INODE_NUMBER, "/");
//what is the overall change that is needed
// In order for the code to work
//we can see that this is true
    try {
        size_t NeedThe_NextSlash = find_mainPathrequest.find_last_of('/');
        int checkforOverallNode = UFS_ROOT_DIRECTORY_INODE_NUMBER;

        if (NeedThe_NextSlash != string::npos) {
            string NeedtheDirectPath = find_mainPathrequest.substr(0, NeedThe_NextSlash);
            vector<string> dirs = StringUtils::split(NeedtheDirectPath, '/');
            for (const string &dir : dirs) {
                int NeedtheincodePath = fileSystem->lookup(checkforOverallNode, dir);
                if (NeedtheincodePath < 0) {
                    if (NeedtheincodePath == -ENOTFOUND) {
                        int needtheNextInode = fileSystem->create(checkforOverallNode, UFS_DIRECTORY, dir);
                        if (needtheNextInode < 0) {
                            cerr << "Insufficient storage to create directory: " << dir << endl;
                            throw ClientError::insufficientStorage();
                        }//what is the overall change that is needed
// In order for the code to work
//we can see that this is true
                        checkforOverallNode = needtheNextInode;
                    } else {
                        cerr << "Bad request while creating directory: " << dir << endl;
                        throw ClientError::badRequest();
                    }
                } else {
                    inode_t NeedtheincodeData;
                    fileSystem->stat(NeedtheincodePath, &NeedtheincodeData);
                    if (NeedtheincodeData.type != UFS_DIRECTORY) {
                        cerr << "Conflict: " << dir << " is not a directory." << endl;
                        throw ClientError::conflict();
                    }
                    checkforOverallNode = NeedtheincodePath;
                }
            }//what is the overall change that is needed
// In order for the code to work
//we can see that this is true
        }

        string findFileName = find_mainPathrequest.substr(NeedThe_NextSlash + 1);
        int findtheFileoverall = fileSystem->create(checkforOverallNode, UFS_REGULAR_FILE, findFileName);
        if (findtheFileoverall < 0) {
            cerr << "ERROR " << findFileName << endl;
            throw ClientError::insufficientStorage();
        }

        int findtheFileresult = fileSystem->write(findtheFileoverall, mainList.c_str(), mainList.size());
        if (findtheFileresult < 0) {
            cerr << "ERROR " << findFileName << endl;
            throw ClientError::insufficientStorage();
        }//what is the overall change that is needed
// In order for the code to work
//we can see that this is true

    } catch (const ClientError &e) {
        cerr << "ERROR" << e.what() << endl;
        throw e;
    } catch (const std::exception &e) {
        cerr << "ERROR " << e.what() << endl;
        throw ClientError::badRequest();
    } catch (...) {
        cerr << "ERROR" << endl;
        throw ClientError::badRequest();
    }
}
//what is the overall change that is needed
// In order for the code to work
//we can see that this is true
void DistributedFileSystemService::del(HTTPRequest *request, HTTPResponse *response) {
    cout << "ERROR " << request->getPath() << endl;

    string findtheFilePath = request->getPath().substr(4);
    super_t create_overallBlock;
    fileSystem->readSuperBlock(&create_overallBlock);

    listDirectory(*fileSystem, UFS_ROOT_DIRECTORY_INODE_NUMBER, "/");

    try {
        vector<string> components = StringUtils::split(findtheFilePath, '/');
        if (components.empty()) {
            cerr << "Bad request: Path is empty." << endl;
            throw ClientError::badRequest();
        }
//what is the overall change that is needed
// In order for the code to work
//we can see that this is true
        int checkforOverallNode = UFS_ROOT_DIRECTORY_INODE_NUMBER;
        for (size_t i = 0; i < components.size() - 1; ++i) {
            int NeedtheincodePath = fileSystem->lookup(checkforOverallNode, components[i]);
            if (NeedtheincodePath < 0) {
                if (NeedtheincodePath == -ENOTFOUND) {
                    // string find_mainSym = find_mainPathrequest.substr(NeedThe_NextSlash + 1);
//         if (find_mainSym.empty()) {
//             find_mainSym = ".";
//         }
//         int find_mainIncode = fileSystem->lookup(checkforOverallNode, find_mainSym);
//         if (find_mainIncode < 0) {
//             cerr << "Item not found: " << find_mainSym << endl;
//             throw ClientError::notFound();
//         }

//         inode_t CheckforTheItemData;
//         fileSystem->stat(find_mainIncode, &CheckforTheItemData);

//         if (CheckforTheItemData.type == UFS_REGULAR_FILE) {
//             char buffer[MAX_FILE_SIZE];
//             int CheckforTheByte = fileSystem->read(find_mainIncode, buffer, CheckforTheItemData.size);
//             response->setBody(string(buffer, CheckforTheByte));
//         } else if (CheckforTheItemData.type == UFS_DIRECTORY) {
//             char buffer[MAX_FILE_SIZE];
//             int CheckforTheByte = fileSystem->read(find_mainIncode, buffer, CheckforTheItemData.size);
                    cerr << "ERROR " << components[i] << endl;
                    throw ClientError::notFound();
                } else {
                    cerr << "ERROR" << components[i] << endl;
                    throw ClientError::badRequest();
                }
//we can see that this is true
            }
            inode_t NeedtheincodeData;
            fileSystem->stat(NeedtheincodePath, &NeedtheincodeData);
            if (NeedtheincodeData.type != UFS_DIRECTORY) {
                cerr << "Conflict: " << components[i] << " is not a directory." << endl;
                throw ClientError::conflict();
            }
            checkforOverallNode = NeedtheincodePath;
        }
//we can see that this is true

        string find_mainSym = components.back();
        int checkfortheFinalResults = fileSystem->unlink(checkforOverallNode, find_mainSym);
        if (checkfortheFinalResults < 0) {
            switch (checkfortheFinalResults) {//what is the overall change that is needed
// In order for the code to work
//we can see that this is true
                case -EINVALIDINODE:
                    cerr << "ERROR " << find_mainSym << endl;
                    throw ClientError::notFound();
                case -EDIRNOTEMPTY:
                    cerr << "ERROR" << find_mainSym << endl;
                    throw ClientError::conflict();
                case -EINVALIDNAME:
                    cerr << "ERROR " << find_mainSym << endl;
                    throw ClientError::badRequest();
                default:
                    cerr << "ERROR " << find_mainSym << endl;
                    throw ClientError::badRequest();
            }
        }//what is the overall change that is needed
// In order for the code to work
//we can see that this is true

        response->setStatus(200);
        response->setBody("Deleted");
//what is the overall change that is needed
// In order for the code to work
//we can see that this is true
    } catch (const ClientError &e) {
        cerr << "ERROR " << e.what() << endl;
        throw e;//what is the overall change that is needed
// In order for the code to work
//we can see that this is true
    } catch (...) {
        cerr << "ERROR" << endl;
        throw ClientError::badRequest();
    }
}



