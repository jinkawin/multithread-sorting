#include <unistd.h>
#include <pthread.h>

#include "context.hpp"
#include "sort.hpp"

using namespace std;

class TaskManager {
private:
  inline static int counter = 0;

public:
  static void *local_sort(void *data) {
    int thread_id = counter++;
    Context *context = (struct Context*)data;

    /* Calculate calulation window */
    int calculation_size = (context->data->size()+1)/context->threads_number;
    int start_index = thread_id * calculation_size;
    int last_index = ((thread_id + 1) * calculation_size)-1;

    /* Delaying for debugging */
    unsigned int microsecond = 500000;
    usleep((thread_id+1) * microsecond);

    /* Debug message */
    cout << "Thread ID: " << thread_id << ", ";
    cout << "calculation_size: " << calculation_size << ", ";
    cout << "start_index: " << start_index << ", ";
    cout << "last_index: " << last_index << ", " << endl;

    Sort::quick_sort(*(context->data), 2, start_index, last_index);

    //Discounting running threads
    pthread_mutex_lock(&(context->running_mutex));
    context->running_threads--;
    pthread_mutex_unlock(&(context->running_mutex));

    pthread_exit(NULL);
  }
};
