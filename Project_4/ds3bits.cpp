#include <iostream>
#include <string>
#include <algorithm>
#include <cstring>

#include "LocalFileSystem.h"
#include "Disk.h"
#include "ufs.h"

using namespace std;


int main(int argc, char *argv[]) {
  if (argc != 2) {
        cout << "Usage: " << argv[0] << " diskImageFile" << endl;
    return 1;
  }


  // int main(int argc, char *argv[]) {
  // if (argc != 2) {
  //       cout << "Usage: " << argv[0] << " diskImageFile" << endl;
  //   return 1;
  // }
//here we use the localsystem to find the block size
  super_t super;
  LocalFileSystem filechecking = LocalFileSystem(new Disk(argv[1], UFS_BLOCK_SIZE));
  filechecking.readSuperBlock(&super);
//Now we have too set the 2 variables for each 
  int checkforIncode = super.inode_bitmap_len * UFS_BLOCK_SIZE;
  int checkfordata = super.data_bitmap_len * UFS_BLOCK_SIZE;
//This character has a Bitmap that requires for a seperation between the 2
  unsigned char inodeBitmap[checkforIncode];
  unsigned char dataBitmap[checkfordata];
//This character has a Bitmap that requires for a seperation between the 2

  filechecking.readInodeBitmap(&super, inodeBitmap);
  filechecking.readDataBitmap(&super, dataBitmap);
//We can see a big change in between the 2 
  cout << "Super" << endl;
  cout << "inode_region_addr " << super.inode_region_addr << endl;
  cout << "data_region_addr " << super.data_region_addr << endl;
  cout <<  endl;

  cout << "Inode bitmap" << endl;
  for (int i = 0; i < checkforIncode; ++i) {
    cout << (unsigned int) inodeBitmap[i] << " ";
  }

//  cout << "finding the bitmap" << endl;
//   for (int i = 0; i < checkforIncode; ++i) {
//     cout << (unsigned int) inodeBitmap[i] << " ";
//   }

  cout << endl;
  cout << endl;

  cout << "Data bitmap" << endl;
  for (int i = 0; i < checkfordata; ++i) {
    cout << (unsigned int) dataBitmap[i] << " ";
  }


  cout << endl;


  return 0;

}