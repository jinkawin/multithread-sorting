#ifndef CONTEXT_HPP
#define CONTEXT_HPP

#include <vector>
#include <pthread.h>

using namespace std;

struct SortContext {
  vector<vector<char>> *data;
  vector<int64_t> *buckets_index; //store the last array's index of each bucket
  pthread_mutex_t &running_mutex;
  volatile uint8_t &running_threads;
  unsigned int total_threads;
  int sorting_column;
};

struct BucketContext {
  vector<vector<char>> *data;
  vector<int64_t> *buckets_index; //store the last array's index of each bucket
  unsigned int total_threads;
  int sorting_column;
};

#endif