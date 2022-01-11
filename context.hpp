#ifndef CONTEXT_HPP
#define CONTEXT_HPP

#include <vector>
#include <pthread.h>

using namespace std;

struct SortContext {
  vector<vector<char>> *data;
  vector<int> *buckets_index; //store the last array's index of each bucket
  pthread_mutex_t &running_mutex;
  volatile uint8_t &running_threads;
  uint8_t total_threads;
  int sorting_column;
};

struct BucketContext {
  vector<vector<char>> *data;
  vector<int> *buckets_index; //store the last array's index of each bucket
  uint8_t total_threads;
  int sorting_column;
};

#endif