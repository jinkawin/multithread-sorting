#include <unistd.h>
#include "context.hpp"
using namespace std;

class TaskManager {
private:
  inline static int counter = 0;

public:
  static void *distribute(void *data) {
    int threadId = counter++;
    Context *context = (struct Context*)data;

    unsigned int microsecond = 500000;
    usleep((threadId+1) * microsecond);//sleeps for 3 second

    int calculationSize = (context->data->size()+1)/context->threadsNumber;
    int startIndex = threadId * calculationSize;
    int lastIndex = ((threadId + 1) * calculationSize)-1;

    cout << "Thread ID: " << threadId << ", ";
    cout << "calculationSize: " << calculationSize << ", ";
    cout << "startIndex: " << startIndex << ", ";
    cout << "lastIndex: " << lastIndex << ", " << endl;

    pthread_exit(NULL);
  }
};
