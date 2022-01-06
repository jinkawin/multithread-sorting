#include <unistd.h>
#include <pthread.h>

#include "context.hpp"
#include "sort.hpp"

using namespace std;

class TaskManager {
private:
  static const char FIRST_CHAR = '0';
  static const int TOTAL_CHAR = 75;
  inline static int counter = 0;

public:
  static void *localSort(void *data) {
    int thread_id = counter++;
    SortContext *context = (struct SortContext*)data;

    /* Calculate calulation window */
    int calculation_size = (context->data->size()+1)/context->total_threads;
    int start_idx = thread_id * calculation_size;
    int last_idx = ((thread_id + 1) * calculation_size)-1;

    Sort::quickSort(*(context->data), context->sorting_column, start_idx, last_idx);

    endThread(thread_id, context);
    pthread_exit(NULL);
  }

  // static void *swapBucket(void *data) {
  //   int thread_id = counter++;
  //   SortContext *context = (struct SortContext*)data;

  //   /* Calculate calulation window */
  //   int calculation_size = (context->data->size()+1)/context->total_threads;
  //   int start_idx = thread_id * calculation_size;
  //   int last_idx = ((thread_id + 1) * calculation_size)-1;

  //   int charactor_size = TOTAL_CHAR/context->total_threads;
  //   int start_char_idx = thread_id * charactor_size;
  //   int end_char_idx = ((thread_id + 1) * charactor_size)-1;

  //   endThread(thread_id, context);
  //   pthread_exit(NULL);
  // }

  static void swapBucket(BucketContext *context) {
    vector<vector<char>> &data = *(context->data);
    vector<int> &buckets_index = *(context->buckets_index);
    int column = context->sorting_column;
    int characters_size = TOTAL_CHAR/context->total_threads;
    int runner = 0;

    for(int i = 0; i < context->total_threads; i++) {
      int start_char = FIRST_CHAR + (i * characters_size);
      int end_char = FIRST_CHAR + (((i+1) * characters_size)-1);

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
