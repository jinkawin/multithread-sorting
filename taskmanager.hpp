#include <unistd.h>
#include <pthread.h>
#include <thread>

#include "context.hpp"
#include "sort.hpp"

using namespace std;

class TaskManager {
private:
  static const char FIRST_CHAR = 'a';
  static const uint8_t TOTAL_CHAR = 26; // a to z
  inline static uint8_t counter = 0;

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
      sleep(1);
    }
  }

  static void swapBucket(BucketContext *context) {
    vector<vector<char>> &data = *(context->data);
    vector<int> &buckets_index = *(context->buckets_index);

    int column = context->sorting_column;
    uint8_t characters_size = TOTAL_CHAR/(context->total_threads - 1);
    int runner = 0;

    for(int i = 0; i < context->total_threads; i++) {
      int start_char = (i == 0) ? '0' : FIRST_CHAR + ((i - 1) * characters_size);
      int end_char = (i == 0) ? '9' : (FIRST_CHAR + ((i * characters_size)) - 1);

      for(int row = runner; row < data.size(); row++) {
        if(data[row][column] >= start_char && data[row][column] <= end_char) {
          swap(data[row], data[runner]);
          runner++;
        }
      }

      buckets_index.push_back(runner - 1); // minus 1 for changing position to index
    }
  }

private:
  static void *sort(void *data) {
    int thread_id = counter++;
    SortContext *context = (struct SortContext*)data;

    /* Calculate calulation window */
    vector<int> &buckets_index = *(context->buckets_index);
    int start_idx = (thread_id ==  0) ? 0 : buckets_index[thread_id-1]+1;
    int last_idx = buckets_index[thread_id];

    Sort::quickSort(*(context->data), context->sorting_column, start_idx, last_idx);

    // Post-process
    TaskManager::endThread(thread_id, context);
    pthread_exit(NULL);
  }

  static void endThread(int thread_id, SortContext *context) {
    // Discounting threads
    pthread_mutex_lock(&(context->running_mutex));
    context->running_threads--;
    pthread_mutex_unlock(&(context->running_mutex));

    // Reset counter
    if(thread_id == (context->total_threads - 1)) {
      counter = 0;
    }
  }
};
