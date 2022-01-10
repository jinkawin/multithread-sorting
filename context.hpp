#include <vector>
#include <pthread.h>

using namespace std;

#ifndef CONTEXT_HPP
#define CONTEXT_HPP

struct SortContext {
  vector<vector<char>> *data;
  vector<int> *buckets_index; //store the last array's index of each bucket
  pthread_mutex_t &running_mutex;
  int &running_threads;
  int total_threads;
  int sorting_column;
};

struct BucketContext {
  vector<vector<char>> *data;
  vector<int> *buckets_index; //store the last array's index of each bucket
  int total_threads;
  int sorting_column;
};

#endif