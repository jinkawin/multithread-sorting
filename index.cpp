#include <pthread.h>
#include <thread>
#include <vector>

#include "filemanager.hpp"
#include "taskmanager.hpp"
#include "context.hpp"
#include "util.hpp"

using namespace std;
using chrono::high_resolution_clock;
using chrono::duration_cast;
using chrono::duration;
using chrono::milliseconds;

int main() {
  // Thread initialisation
  volatile uint8_t running_threads = 0;
  uint8_t total_threads = 3;
  pthread_mutex_t running_mutex = PTHREAD_MUTEX_INITIALIZER;

  // Data Initialisation
  vector<int> buckets_index;
  vector<vector<char>> data;
  FileManager::read("test.txt", data);

  // Initial Bucket index
  uint64_t bucket_size = data.size() / total_threads;
  for(uint64_t i = bucket_size-1; i < data.size(); i = i+bucket_size) {
    buckets_index.push_back(i);
  }

  for(int i = data[0].size()-1; i >= 0; i--) {
    SortContext sortContext = {
      &data,
      &buckets_index,
      running_mutex,
      running_threads,
      total_threads,
      i
    };
    TaskManager::localSort(&sortContext);

    BucketContext bucketContext = {
      &data,
      &buckets_index,
      total_threads,
      i
    };
    TaskManager::swapBucket(&bucketContext);
  }

  // Post-process
  SortContext sortContext = {
    &data,
    &buckets_index,
    running_mutex,
    running_threads,
    total_threads,
    0
  };
  TaskManager::localSort(&sortContext);
  cout << "All threads are finished!" << endl;
  Util::printVector2d(data);

  pthread_exit(NULL);

  return 0;
}
