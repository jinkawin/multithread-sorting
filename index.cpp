#include <iostream>
#include <cstdlib>
#include <pthread.h>
#include <thread>
#include <vector>

#include "task-manager.hpp"
#include "context.hpp"

using namespace std;

int main () {
  vector<vector<char> > data { {'1', 'H', 'P'}, {'A', 'Y', '6'}, {'F', '2', 'K'}, {'7', '8', 'L'}, {'R', 'I', 'N'}, {'X', 'U', '9'}};

  int threadsNumber = 3;

  pthread_t threads[threadsNumber];

  for(int i = 0; i < threadsNumber; i++ ) {
    Context context = {
      &data,
      threadsNumber
    };

    int rc = pthread_create(&threads[i], NULL, TaskManager::distribute, (void *)&context);

    if (rc) {
      cout << "Error:unable to create thread," << rc << endl;
      exit(-1);
    }
  }
  pthread_exit(NULL);
}