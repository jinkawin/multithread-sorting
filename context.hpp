#include <vector>

using namespace std;

#ifndef CONTEXT_HPP
#define CONTEXT_HPP

struct Context{
  vector<vector<char> > *data;
  int threadsNumber;
};

#endif