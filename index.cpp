#include <pthread.h>
#include <thread>
#include <vector>

#include "filemanager.hpp"
#include "taskmanager.hpp"
#include "context.hpp"
#include "util.hpp"

using namespace std;

int main() {
  // Thread initialisation
  volatile uint8_t running_threads = 0;
  unsigned int total_threads = thread::hardware_concurrency();
  pthread_mutex_t running_mutex = PTHREAD_MUTEX_INITIALIZER;

  // Data Initialisation
  vector<int> buckets_index;
  vector<vector<char>> data;
  FileManager::read("test1.txt", data);

  // A number of cores cannot exceed a number of data's row
  total_threads = (total_threads < data.size()) ? total_threads : data.size();

  // Initial Bucket index
  uint64_t bucket_size = data.size() / total_threads;
  for(uint64_t i = bucket_size-1; i < data.size(); i = i+bucket_size) {
    buckets_index.push_back(i);
  }

  // Sorting
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

  Util::printVector(buckets_index);
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

  FileManager::write("out.txt", data);
  cout << "finished" << endl;

  pthread_exit(NULL);

  return 0;
}
