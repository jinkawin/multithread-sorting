#include <iostream>
#include <cstdlib>
#include <pthread.h>
#include <thread>
#include <vector>

#include "task-manager.hpp"
#include "context.hpp"

using namespace std;

int main() {
  int running_threads = 0;
  int threads_number = 3;
  pthread_mutex_t running_mutex = PTHREAD_MUTEX_INITIALIZER;
  pthread_t threads[threads_number];

  vector<vector<char>> data {{'1', 'H', 'P'}, {'A', 'Y', '6'}, {'F', '2', 'K'}, {'7', '8', 'L'}, {'R', 'I', 'N'}, {'X', 'U', '9'}};

  // Local sorting (Multithread)
  for(int i = 0; i < threads_number; i++ ) {
    Context context = {
      &data,
      running_threads,
      running_mutex,
      threads_number
    };

    // Assign task to threads
    int rc = pthread_create(&threads[i], NULL, TaskManager::local_sort, (void *)&context);

    // Counting running threads
    pthread_mutex_lock(&running_mutex);
    running_threads++;
    pthread_mutex_unlock(&running_mutex);

    // If thread didn't work
    if (rc) {
      cout << "Error:unable to create thread," << rc << endl;
      exit(-1);
    }
  }

  while(running_threads > 0){
    sleep(1);
  }

  cout << "All threads are finished!" << endl;
  Sort::print_vector_2d(data);

  pthread_exit(NULL);
}