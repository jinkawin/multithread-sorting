#include <pthread.h>
#include <thread>
#include <vector>

#include "taskmanager.hpp"
#include "context.hpp"
#include "util.hpp"

using namespace std;

void localSort(SortContext *context) {
  pthread_t threads[context->total_threads];

  for(int i = 0; i < context->total_threads; i++ ) {
    // Assign task to threads
    int rc = pthread_create(&threads[i], NULL, TaskManager::localSort, (void *)context);

    // Counting running threads
    pthread_mutex_lock(&(context->running_mutex));
    context->running_threads++;
    pthread_mutex_unlock(&(context->running_mutex));

    // If thread didn't work
    if (rc) {
      cout << "Error:unable to create thread," << rc << endl;
      exit(-1);
    }
  }

  while(context->running_threads > 0){
    sleep(1);
  }
}

int main() {
  int total_threads = 3;
  int sorting_column = 2;
  int running_threads = 0;
  pthread_mutex_t running_mutex = PTHREAD_MUTEX_INITIALIZER;

  vector<vector<char>> data {{'a', 's', 'c'}, {'6', 'h', 'p'}, {'f', '3', 'x'}, {'n', 'r', '1'}, {'u', '9', 'j'}, {'t', 'i', '7'}};
  vector<int> buckets_index;

  int bucket_size = data.size() / total_threads;

  // Initial Bucket index
  for(int i = bucket_size-1; i < data.size(); i = i+bucket_size) {
    buckets_index.push_back(i);
  }

  SortContext sortContext = {
    &data,
    &buckets_index,
    running_mutex,
    running_threads,
    total_threads,
    sorting_column
  };
  localSort(&sortContext);

  BucketContext bucketContext = {
    &data,
    &buckets_index,
    total_threads,
    sorting_column
  };
  TaskManager::swapBucket(&bucketContext);

  cout << "All threads are finished!" << endl;
  Util::printVector2d(data);

  pthread_exit(NULL);

  return 0;
}
