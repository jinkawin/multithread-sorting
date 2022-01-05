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
  static void *local_sort(void *data) {
    int thread_id = counter++;
    Context *context = (struct Context*)data;

    /* Calculate calulation window */
    int calculation_size = (context->data->size()+1)/context->total_threads;
    int start_idx = thread_id * calculation_size;
    int last_idx = ((thread_id + 1) * calculation_size)-1;

    Sort::quick_sort(*(context->data), context->sorting_column, start_idx, last_idx);

    end_thread(thread_id, context);
    pthread_exit(NULL);
  }

  static void *swap_bucket(void *data) {
    int thread_id = counter++;
    Context *context = (struct Context*)data;

    /* Calculate calulation window */
    int calculation_size = (context->data->size()+1)/context->total_threads;
    int start_idx = thread_id * calculation_size;
    int last_idx = ((thread_id + 1) * calculation_size)-1;

    int charactor_size = TOTAL_CHAR/context->total_threads;
    int start_char_idx = thread_id * charactor_size;
    int end_char_idx = ((thread_id + 1) * charactor_size)-1;

    end_thread(thread_id, context);
    pthread_exit(NULL);
  }

private:
  static void end_thread(int thread_id, Context *context) {
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
