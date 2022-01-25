#include <unistd.h>
#include <pthread.h>
#include <thread>
#include <chrono>

#include "context.hpp"
#include "sort.hpp"
#include "columnsort.hpp"

using namespace std;

class TaskManager {
public:
  inline static uint8_t counter = 0;

private:
  static const char FIRST_CHAR = 'a';
  static const uint16_t TOTAL_CHAR = 26; // a to z

public:
  static void localSort(SortContext *context) {
    pthread_t threads[context->total_threads];

    for(int i = 0; i < context->total_threads; i++ ) {
      // Assign task to threads
      int rc = pthread_create(&threads[i], NULL, TaskManager::sort, (void *)context);

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

    // Wait all threads
    while(context->running_threads > 0){
      this_thread::sleep_for(chrono::milliseconds(10));
    }
  }

  static void swapBucket(BucketContext *context) {
    vector<vector<char>> &data = *(context->data);
    vector<int64_t> &buckets_index = *(context->buckets_index);

    buckets_index.clear();

    int column = context->sorting_column;
    int characters_size = TOTAL_CHAR/(context->total_threads - 1);
    int64_t runner = 0;

    for(auto i = 0; i < context->total_threads; i++) {
      int start_char = (i == 0) ? '0' : FIRST_CHAR + ((i - 1) * characters_size);
      int end_char = (i == 0) ? '9' : (FIRST_CHAR + ((i * characters_size)) - 1);

      for(int64_t row = runner; row < data.size(); row++) {
        if(data[row][column] >= start_char && data[row][column] <= end_char) {
          swap(data[row], data[runner]);
          runner++;
        }
      }

      int64_t index = runner == 0 ? 0 : runner - 1; // minus 1 for changing position to index
      buckets_index.push_back(index);
    }
  }

private:
  static void *sort(void *data) {
    int thread_id = counter++;
    SortContext *context = (struct SortContext*)data;

    unsigned int microsecond = 500000;
    usleep((thread_id+1) * microsecond);

    /* Calculate calulation window */
    vector<int64_t> &buckets_index = *(context->buckets_index);
    int64_t start_idx = 0;
    if(thread_id !=  0) {
      const int64_t previous_index = buckets_index[thread_id-1];
      start_idx = (previous_index == 0) ? previous_index : previous_index+1;
    }
    int64_t last_idx = buckets_index[thread_id];

    ColumnSort::column = context->sorting_column;
    ColumnSort::columnSort(*(context->data), start_idx, last_idx);

    // Post-process
    TaskManager::endThread(thread_id, context);
    pthread_exit(NULL);
  }

  static void endThread(int thread_id, SortContext *context) {
    // Discounting threads
    pthread_mutex_lock(&(context->running_mutex));
    context->running_threads--;
    pthread_mutex_unlock(&(context->running_mutex));
  }
};
