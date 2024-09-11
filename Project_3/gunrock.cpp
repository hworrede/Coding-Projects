//Hagos Worrede
#include <stdlib.h>
#include <unistd.h>
#include <assert.h>
#include <signal.h>
#include <fcntl.h>

#include <iostream>
#include <memory>
#include <string>
#include <vector>
#include <sstream>
#include <deque>
#include <queue>

#include "HTTPRequest.h"
#include "HTTPResponse.h"
#include "HttpService.h"
#include "HttpUtils.h"
#include "FileService.h"
#include "MySocket.h"
#include "MyServerSocket.h"
#include "dthread.h"

using namespace std;

int PORT = 8080;
int THREAD_POOL_SIZE = 1;
int BUFFER_SIZE = 1;
string BASEDIR = "static";
string SCHEDALG = "FIFO";
string LOGFILE = "/dev/null";

vector<HttpService *> services;

pthread_mutex_t bufferMutex = PTHREAD_MUTEX_INITIALIZER;  
// The above would need to check for the buffers of all intializers 
pthread_cond_t bufferRequestMade = PTHREAD_COND_INITIALIZER;  
// This is a condition that check the order for the conditioner variable 
pthread_cond_t bufferNotFull = PTHREAD_COND_INITIALIZER;  
 // This is checking for the buffer if it is full 
queue<MySocket *> connectionBuffer; 
// The buffer would make sure that there is changed fo connection 


HttpService *find_service(HTTPRequest *request) {
   // find a service that is registered for this path prefix
  for (unsigned int idx = 0; idx < services.size(); idx++) {
    if (request->getPath().find(services[idx]->pathPrefix()) == 0) {
      return services[idx];
    }
  }

  return NULL;
}


void invoke_service_method(HttpService *service, HTTPRequest *request, HTTPResponse *response) {
  stringstream payload;

  // invoke the service if we found one
  if (service == NULL) {
    // not found status
    response->setStatus(404);
  } else if (request->isHead()) {
    service->head(request, response);
  } else if (request->isGet()) {
    service->get(request, response);
  } else {
    // The server doesn't know about this method
    response->setStatus(501);
  }
}

void handle_request(MySocket *client) {
  HTTPRequest *request = new HTTPRequest(client, PORT);
  HTTPResponse *response = new HTTPResponse();
  stringstream payload;
  
  // read in the request
  bool readResult = false;
  try {
    payload << "client: " << (void *) client;
    sync_print("read_request_enter", payload.str());
    readResult = request->readRequest();
    sync_print("read_request_return", payload.str());
  } catch (...) {
    // swallow it
  }    
      //double to check for more corrections that will make a difference
  if (!readResult) {
    // there was a problem reading in the request, bail
    delete response;
    delete request;
    sync_print("read_request_error", payload.str());
    return;
  }
  //double to check for more corrections that will make a difference
  
  HttpService *service = find_service(request);
  invoke_service_method(service, request, response);

  // send data back to the client and clean up
  payload.str(""); payload.clear();
  payload << " RESPONSE " << response->getStatus() << " client: " << (void *) client;
  sync_print("write_response", payload.str());
  cout << payload.str() << endl;
  client->write(response->response());
      //double to check for more corrections that will make a difference

  delete response;
  delete request;
  //double to check for more corrections that will make a difference
  payload.str(""); payload.clear();
  payload << " client: " << (void *) client;
  sync_print("close_connection", payload.str());
  client->close();
  delete client;
}  //double to check for more corrections that will make a difference

void* workerThread(void* arg) {
    while (true) {

        dthread_mutex_lock(&bufferMutex);
        MySocket* check_eachclient;
//finally we find the buffer 
        while (connectionBuffer.empty()) {
            dthread_cond_wait(&bufferRequestMade, &bufferMutex);  
        }
        
        // while (connectionBuffer.empty()) {
        //     dthread_cond_wait(&bufferRequestMade, &bufferMutex);  
        // }
//check for the following of all the requests that get made first 
        check_eachclient = connectionBuffer.front();
        connectionBuffer.pop();

// while (connectionBuffer.empty()) {
        //     dthread_cond_wait(&bufferRequestMade, &bufferMutex);  
        // }
        dthread_cond_signal(&bufferNotFull);  
        // Find the main signal buffer in order to check if works for the rest
        dthread_mutex_unlock(&bufferMutex);
//make sure it would be able to see the requests 
        // dthread_cond_signal(&bufferNotFull); 
        handle_request(check_eachclient);


    }


    return NULL;

}


int main(int argc, char *argv[]) {

  signal(SIGPIPE, SIG_IGN);
  int option;

  while ((option = getopt(argc, argv, "d:p:t:b:s:l:")) != -1) {
    switch (option) {
    case 'd':
      BASEDIR = string(optarg);
      break;
    case 'p':
      PORT = atoi(optarg);
      break;
    case 't':
      THREAD_POOL_SIZE = atoi(optarg);
      break;
    case 'b':
      BUFFER_SIZE = atoi(optarg);
      break;
    case 's':
      SCHEDALG = string(optarg);
      break;
    case 'l':
      LOGFILE = string(optarg);
      break;
    default:
      cerr<< "usage: " << argv[0] << " [-p port] [-t threads] [-b buffers]" << endl;
      exit(1);
    }
  }

  set_log_file(LOGFILE);

  sync_print("init", "");
  MyServerSocket *server = new MyServerSocket(PORT);
  MySocket *client;


//  sync_print("init", "");
//   MyServerSocket *server = new MyServerSocket(PORT);
//   MySocket *client;
  services.push_back(new FileService(BASEDIR));
//  sync_print("init", "");
//   MyServerSocket *server = new MyServerSocket(PORT);
//   MySocket *client;
  pthread_t* threads = new pthread_t[THREAD_POOL_SIZE];

  //we check for the options above for a comparison in order to find the correct order





  for (int i = 0; i < THREAD_POOL_SIZE; ++i) {
      dthread_create(&threads[i], NULL, workerThread, NULL);
  }
  //had to change fron pthread to dthread 

  // for (int i = 0; i < THREAD_POOL_SIZE; ++i) {
  //       pthread_create(&threads[i], nullptr, workerThread, nullptr);
  //   }

  while(true) {

    sync_print("waiting_to_accept", "");
    client = server->accept();
    sync_print("client_accepted", "");
    

    //  sync_print("waiting_to_accept", "");
    // client = server->accept();
    // sync_print("client_accepted", "");
    dthread_mutex_lock(&bufferMutex);
//check for the buffer that brings the correct mutex
    while (connectionBuffer.size() >= static_cast<std::queue<MySocket*>::size_type>(BUFFER_SIZE)) {
      dthread_cond_wait(&bufferNotFull, &bufferMutex); 
       // finally we find that there is a request for a signal that is made by main
    }
    
    connectionBuffer.push(client);
    dthread_cond_signal(&bufferRequestMade);
    dthread_mutex_unlock(&bufferMutex);
//find the next requests that get made for each
    //  connectionBuffer.push(client);
    // dthread_cond_signal(&bufferRequestMade);
    // dthread_mutex_unlock(&bufferMutex);
  }
}