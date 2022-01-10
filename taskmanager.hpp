#include <unistd.h>
#include <pthread.h>

#include "context.hpp"
#include "sort.hpp"

using namespace std;

class TaskManager {
private:
  static const char FIRST_CHAR = 'a';
  static const int TOTAL_CHAR = 26; // a to z
  inline static int counter = 0;

public:
  static void *localSort(void *data) {
    int thread_id = counter++;
    SortContext *context = (struct SortContext*)data;

    /* Calculate calulation window */
    vector<int> &buckets_index = *(context->buckets_index);
    int start_idx = (thread_id ==  0) ? 0 : buckets_index[thread_id-1]+1;
    int last_idx = buckets_index[thread_id];

    Sort::quickSort(*(context->data), context->sorting_column, start_idx, last_idx);

    endThread(thread_id, context);
    pthread_exit(NULL);
  }

  static void swapBucket(BucketContext *context) {
    vector<vector<char>> &data = *(context->data);
    vector<int> &buckets_index = *(context->buckets_index);
    int column = context->sorting_column;
    int characters_size = TOTAL_CHAR/(context->total_threads - 1);
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
