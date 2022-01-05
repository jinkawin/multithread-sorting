#include <vector>
#include <pthread.h>

using namespace std;

#ifndef CONTEXT_HPP
#define CONTEXT_HPP

struct Context{
  vector<vector<char>> *data;
  pthread_mutex_t &running_mutex;
  int &running_threads;
  int total_threads;
  int sorting_column;
};

#endif