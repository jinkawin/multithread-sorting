#include <vector>
#include <pthread.h>

using namespace std;

#ifndef CONTEXT_HPP
#define CONTEXT_HPP

struct Context{
  vector<vector<char>> *data;
  int &running_threads;
  pthread_mutex_t &running_mutex;
  int threads_number;
};

#endif