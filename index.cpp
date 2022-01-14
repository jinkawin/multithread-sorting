#include <pthread.h>
#include <thread>
#include <vector>

#include "filemanager.hpp"
#include "taskmanager.hpp"
#include "context.hpp"
#include "config.hpp"

using namespace std;

int main() {
  // Thread initialisation
  volatile uint8_t running_threads = 0;
  unsigned int total_threads = thread::hardware_concurrency();
  pthread_mutex_t running_mutex = PTHREAD_MUTEX_INITIALIZER;

  // Data Initialisationd
  vector<int> buckets_index;
  vector<vector<char>> data(Config::ALLOC_ROW_SIZE, vector<char>(Config::ALLOC_COL_SIZE));
  FileManager::read(Config::FILE_IN, data);

  // Find last position of the first column (by finging the first comma)
  int last_index;
  int sampling_index = 0;
  for(double i = 0; i < data[sampling_index].size(); i++) {
    if(data[sampling_index][i] == ',') {
      last_index = i-1;
      break;
    }
  }

  // Sorting
  for(int i = last_index; i >= Config::START_INDEX; i--) {
    BucketContext bucketContext = {
      &data,
      &buckets_index,
      total_threads,
      i
    };
    TaskManager::swapBucket(&bucketContext);

    SortContext sortContext = {
      &data,
      &buckets_index,
      running_mutex,
      running_threads,
      total_threads,
      i
    };
    TaskManager::localSort(&sortContext);
  }

  FileManager::write(Config::FILE_OUT, data);

  pthread_exit(NULL);

  return 0;
}
