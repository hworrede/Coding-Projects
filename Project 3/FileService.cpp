//Hagos Worrede
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>

#include <iostream>
#include <map>
#include <string>

#include "FileService.h"

using namespace std;

FileService::FileService(string basedir) : HttpService("/") {
  while (endswith(basedir, "/")) {
    basedir = basedir.substr(0, basedir.length() - 1);
  }
//This checks for the folloiwng codes that make it correct to find the way

  if (basedir.length() == 0) {
    cout << "invalid basedir" << endl;
    exit(1);
  }
  //overall this is what makes it invalid 
  this->m_basedir = basedir;
}

FileService::~FileService(){
//overall we can see the services that make it correct 
}

bool FileService::endswith(string str, string suffix) {
  size_t pos = str.rfind(suffix);
  return pos == (str.length() - suffix.length());
}
//check for for the file services 

void FileService::get(HTTPRequest *request, HTTPResponse *response) {

  string finding_nextWay = request->getPath();
//double check for the mistakes made 
  if (finding_nextWay.find("..") != string::npos) {
        response->setStatus(403); 
        return;
  }//overall we can check that there is eventually more than one that is quite important

//  if (finding_nextWay.find("..") != string::npos) {
//         response->setStatus(403); 
//         return;
//   } 

  string path = this->m_basedir + finding_nextWay;
  string fileContents = this->readFile(path);
  if (fileContents.size() == 0) {
    response->setStatus(403);
    return;
  } //double check for the mistakes made 

  
  else {
    if (this->endswith(path, ".css")) {
      response->setContentType("text/css");
    } else if (this->endswith(path, ".js")) {
      response->setContentType("text/javascript");
    }
    response->setBody(fileContents);
  }


  // if (this->endswith(path, ".css")) {
  //     response->setContentType("text/css");
  //   } else if (this->endswith(path, ".js")) {
  //     response->setContentType("text/javascript");
  //   }
  //   response->setBody(fileContents);
  // }
}

string FileService::readFile(string path) {
  int fd = open(path.c_str(), O_RDONLY);
  if (fd < 0) {
    return "";
  }//double check for the mistakes made 


  string result;
  int ret;
  char buffer[4096];
  while ((ret = read(fd, buffer, sizeof(buffer))) > 0) {
    result.append(buffer, ret);
  }//double check for the mistakes made 


  close(fd);
  
  return result;
}//double check for the mistakes made 


void FileService::head(HTTPRequest *request, HTTPResponse *response) {
  // HEAD is the same as get but with no body
  this->get(request, response);
  response->setBody("");
}//double check for the mistakes made 

